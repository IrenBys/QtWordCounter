// WordCounter.cpp
#include "WordCounter.h"
#include <QDebug>
#include <QFile>
#include <QTimer>


WordCounter::WordCounter(QObject *parent) : QObject(parent), progress_state(0.0) {

    m_workerThread = new WordCounterThread(this);

    connect(m_workerThread, &WordCounterThread::processingStarted, this, &WordCounter::processingStarted);

    connect(m_workerThread, &WordCounterThread::processingWordCount, this, [&](const QList<pair>& list) {
                    m_listWordCount.clear();
                    for (const auto& pair : list) {
                        QVariantMap map;
                        map["word"] = pair.first;
                        map["count"] = pair.second;
                        m_listWordCount.append(map);
                    }
                    emit processingWordCount();
                   });


    connect(m_workerThread, &WordCounterThread::processingProgress, this, [&](double progress) {
        progress_state = progress;
        emit processingProgress();
    });

    connect(m_workerThread, &WordCounterThread::processingFinished, this, &WordCounter::processingFinished);

    connect(m_workerThread, &WordCounterThread::processingCancelled, this, &WordCounter::processingCancelled);
}

WordCounter::~WordCounter() {
    m_workerThread->stop();
    m_workerThread->wait();
}

void WordCounter::openFile(const QString &filePath) {
    QFile file(filePath);
    if (!filePath.isEmpty()) {
        m_filePath = filePath;
        m_workerThread->setFilePath(filePath);
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

    m_workerThread->start();

}

void WordCounter::cancelProcessing() {
    qDebug() << "Отмена обработки.";
    m_workerThread->stop();
}

double WordCounter::getProgress() const {
    qDebug() << "progress_state:" << progress_state;
    return progress_state;
}

QVariantList WordCounter::getWordHighestResult() const {
    qDebug() << "getWordHighestResult";
    return m_listWordCount;
}

void WordCounter::printList() {

    for (const QVariant &item : m_listWordCount) {
        if (item.canConvert<QVariantMap>()) {
            QVariantMap map = item.toMap();
            for (auto it = map.constBegin(); it != map.constEnd(); ++it) {
                qDebug() << it.key() << ":" << it.value();
            }
            qDebug() << "----------------";
        }
    }
}





