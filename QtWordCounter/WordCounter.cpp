// WordCounter.cpp
#include "WordCounter.h"

#include <QFile>
#include <QTimer>


WordCounter::WordCounter(QObject *parent) : QObject(parent), progress_state(0) {

    m_workerThread = new WordCounterThread(this);

    // Подключаем сигналы потока к сигналам этого класса для QML.
    connect(m_workerThread, &WordCounterThread::processingStarted, this, &WordCounter::processingStarted);



    connect(m_workerThread, &WordCounterThread::processingProgress, this, [&](int progress) {
        progress_state = progress;
        emit processingProgress();
    });



    connect(m_workerThread, &WordCounterThread::processingFinished, this, &WordCounter::processingFinished);
    connect(m_workerThread, &WordCounterThread::processingCancelled, this, &WordCounter::processingCancelled);
}

WordCounter::~WordCounter() {
    m_workerThread->stop();
    m_workerThread->wait(); // Ждем завершения потока.
}

void WordCounter::openFile(const QString &filePath) {
    QFile file(filePath);
    if (!filePath.isEmpty()) {
        m_filePath = filePath;
        m_workerThread->setFilePath(filePath);
        emit fileSelected(filePath); // Уведомляем о выбранном файле.
        qDebug() << "Файл выбран: " << filePath;
    } else {
        qDebug() << "Файл не выбран.";
    }
}

void WordCounter::startProcessing() {
    if (m_filePath.isEmpty()) {
        qDebug() << "Файл не выбран.";
        return;
    }

    m_workerThread->setFilePath(m_filePath);
    qDebug() << "Запуск потока обработки.";

    m_workerThread->start(); // Запуск потока.

}

void WordCounter::cancelProcessing() {
    qDebug() << "Отмена обработки.";
    m_workerThread->stop();
}

int WordCounter::progress() const {
    qDebug() << ("progress_state:") << progress_state;
    return progress_state;
}





