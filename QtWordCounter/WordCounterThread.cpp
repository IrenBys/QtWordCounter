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
    QTextStream textStream(&f);

    qint64 totalSize = f.size();
    qint64 processedSize = 0;
    qint64 bufferSize = 4096; // Размер буфера для чтения (4 КБ)
    QByteArray buffer;    
    static QRegularExpression reg_exp("[^a-zA-Zа-яА-ЯёЁ]+");


    while (!textStream.atEnd()) {
        QMutexLocker locker(&m_mutex);
        if (m_cancel) {
            qDebug() << "Обработка отменена.";
            emit processingCancelled();

            progress_state = 0;            
            emit processingProgress(progress_state);

            m_vecWordCount.clear();
            emit processingWordCount(m_vecWordCount);
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
        emit processingWordCount(m_vecWordCount);

        progress_state = static_cast<double>(processedSize) / totalSize * 100.0;
        emit processingProgress(progress_state);        


        qDebug() << "processedSize" << processedSize;
        qDebug() << "totalSize_run" << totalSize;
        qDebug() << "progress_state_run" << progress_state;
        qDebug() << "m_vecWordCount.size" << m_vecWordCount.size();

    }

    emit processingFinished();
    qDebug() << "Обработка завершена.";
    printHighestResult();
    f.close();

}

void WordCounterThread::wordHighestResult(const QMap<QString, int> &countedWords) {

    // Копируем данные в список
    std::copy(countedWords.keyValueBegin(), countedWords.keyValueEnd(),
              std::back_inserter<QList<pair>>(m_vecWordCount));

    // Сортируем по количеству вхождений
    std::sort(m_vecWordCount.begin(), m_vecWordCount.end(),
              [](const pair &l, const pair &r) { return l.second > r.second; });

    // Оставляем только 15 самых популярных
    if (m_vecWordCount.size() > 15) {
        m_vecWordCount.erase(m_vecWordCount.begin() + 15, m_vecWordCount.end());
    }
}

void WordCounterThread::printHighestResult()
{
    qDebug() << ("Most occurring words are:");
    for (qsizetype i = 0; i < m_vecWordCount.size(); ++i) {
        qDebug() << m_vecWordCount[i].first << " : " << m_vecWordCount[i].second;
    }
}

