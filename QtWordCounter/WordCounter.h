// WordCounter.h
#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <QObject>
#include <QDebug>
#include <QVariant>
#include "WordCounterThread.h"

// Класс WordCounter предоставляет интерфейс для взаимодействия с QML и управляет потоком обработки файла.
class WordCounter : public QObject {
    Q_OBJECT
    Q_PROPERTY(double getProgress READ getProgress NOTIFY processingProgress)
    Q_PROPERTY(QVariantList getWordHighestResult READ getWordHighestResult NOTIFY processingWordCount)

public:
    explicit WordCounter(QObject* parent = nullptr);
    ~WordCounter();
    double getProgress() const;
    QVariantList getWordHighestResult() const;


signals:
    void processingStarted();
    void processingProgress();
    void processingFinished();
    void processingCancelled();
    void processingWordCount();

public slots:
    void openFile(const QString& filePath);
    void startProcessing();
    void cancelProcessing();
    void printList();

private:
    QString m_filePath;
    WordCounterThread* m_workerThread;
    double progress_state;
    QVariantList m_listWordCount;
};

#endif // WORDCOUNTER_H

