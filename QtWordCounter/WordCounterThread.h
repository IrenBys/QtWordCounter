#ifndef WORDCOUNTERTHREAD_H
#define WORDCOUNTERTHREAD_H

#include <QThread>
#include <QMutex>
#include <QDebug>
#include <QString>
#include <QList>

using pair = QPair<QString, int>;

class WordCounterThread : public QThread {
    Q_OBJECT

public:
    explicit WordCounterThread(QObject *parent = nullptr);
    ~WordCounterThread();

    void setFilePath(const QString &filePath);
    void stop();
    void wordHighestResult(const QMap<QString, int> &countedWords);
    void printHighestResult();

protected:
    // Основной метод, выполняющийся при старте потока.
    void run() override;

signals:
    void processingStarted();
    void processingProgress(double progress);
    void processingFinished();
    void processingCancelled();
    void processingWordCount(QList<pair> vecWordCount);

private:
    QString m_filePath;
    bool m_cancel;
    QMutex m_mutex;
    double progress_state;
    QMap<QString, int> m_wordCount;
    QList<pair> m_vecWordCount;
};

#endif // WORDCOUNTERTHREAD_H
