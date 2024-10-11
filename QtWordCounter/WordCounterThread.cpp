#include "WordCounterThread.h"

WordCounterThread::WordCounterThread(QObject *parent)
    : QThread(parent), m_cancel(false), progress_state(0) {}

WordCounterThread::~WordCounterThread() {
    stop();
    wait(); // Ожидаем завершения потока.
}

void WordCounterThread::setFilePath(const QString &filePath) {
    m_filePath = filePath;
}

void WordCounterThread::stop() {
    // Используем мьютекс для безопасного изменения переменной m_cancel.
    QMutexLocker locker(&m_mutex);
    m_cancel = true;
}

void WordCounterThread::run() {
    progress_state = 0;
    QMutexLocker locker(&m_mutex);
    m_cancel = false; // Сброс флага отмены
    locker.unlock();
    emit processingStarted();
    qDebug() << "Обработка начата: " << m_filePath;

    for (int i = 0; i < 10; ++i) {
        QMutexLocker locker(&m_mutex);
        if (m_cancel) {
            emit processingCancelled();
            progress_state = 0;
            qDebug() << "Обработка отменена.";
            return;
        }
        locker.unlock();

        // Имитация длительной работы
        QThread::msleep(500); // Задержка 500 мс для имитации работы
        progress_state = (i + 1) * 10;
        qDebug() << ("progress_state run:") << progress_state;
        emit processingProgress(progress_state);
        qDebug() << "Обработка: шаг " << i + 1;

    }

    emit processingFinished();
    qDebug() << "Обработка завершена.";

}
