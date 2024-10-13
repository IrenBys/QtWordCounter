#include "WordCounterThread.h"
#include <QFile>
#include <QRegularExpression>

WordCounterThread::WordCounterThread(QObject *parent)
    : QThread(parent), m_cancel(false), progress_state(0.0) {}

WordCounterThread::~WordCounterThread() {
    stop();
    wait();
}

void WordCounterThread::setFilePath(const QString &filePath) {
    m_filePath = filePath;
}

void WordCounterThread::stop() {
    QMutexLocker locker(&m_mutex);
    m_cancel = true;
}

void WordCounterThread::run() {
    m_wordCount.clear();
    progress_state = 0;
    QMutexLocker locker(&m_mutex);
    m_cancel = false; // Сброс флага отмены
    locker.unlock();
    emit processingStarted();
    qDebug() << "Обработка начата: " << m_filePath;

    QFile f(m_filePath);
    if (!f.open(QIODevice::ReadOnly)) {
        qWarning() << "Не удалось открыть файл:" << m_filePath;
        emit processingFinished();
        return;
    }

    qint64 totalSize = f.size();
    qint64 processedSize = 0;
    qint64 bufferSize = 4096; // Размер буфера для чтения (4 КБ)
    QByteArray buffer;
    QTextStream textStream(&f);
    static QRegularExpression reg_exp("[^a-zA-Zа-яА-ЯёЁ]+");


    while (!textStream.atEnd()) {
        QMutexLocker locker(&m_mutex);
        if (m_cancel) {
            qDebug() << "Обработка отменена.";
            emit processingCancelled();
            progress_state = 0;            
            emit processingProgress(progress_state);
            break;
        }
        locker.unlock();

        // Читаем порцию данных из файла
        buffer = f.read(bufferSize);
        processedSize += buffer.size();

        // Обрабатываем считанный блок текста
        QString chunk = QString::fromUtf8(buffer);
        QStringList lines = chunk.split('\n');

        for (QString &line : lines) {
            const auto words = line.split(reg_exp, Qt::SkipEmptyParts);
            for (const QString &word : words) {
                m_wordCount[word.toLower().remove(reg_exp)] += 1;
                QThread::msleep(100);
            }
        }

        wordHighestResult(m_wordCount);

        // Обновление прогресса
        progress_state = static_cast<double>(processedSize) / totalSize * 100.0;
        emit processingProgress(progress_state);

        qDebug() << "processedSize" << processedSize;
        qDebug() << "totalSize_run" << totalSize;
        qDebug() << "progress_state_run" << progress_state;

    }

    //emit processingProgress(100);
    emit processingFinished();
    qDebug() << "Обработка завершена.";
    printHighestResult(m_vecWordCount, 15);
    f.close();

}

void WordCounterThread::wordHighestResult(const QMap<QString, int> &countedWords) {
    std::copy(countedWords.keyValueBegin(), countedWords.keyValueEnd(),
              std::back_inserter<QList<pair>>(m_vecWordCount));
    std::sort(m_vecWordCount.begin(), m_vecWordCount.end(),
              [](const pair &l, const pair &r) { return l.second > r.second; });
}

void WordCounterThread::printHighestResult(const QList<pair> vec, qsizetype nResults)
{
    qDebug() << ("Most occurring words are:");
    for (qsizetype i = 0; i < qMin(vec.size(), nResults); ++i) {
        qDebug() << vec[i].first << " : " << vec[i].second;

    }
}

