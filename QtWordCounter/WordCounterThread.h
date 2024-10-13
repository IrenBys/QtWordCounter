#ifndef WORDCOUNTERTHREAD_H
#define WORDCOUNTERTHREAD_H

#include <QThread>
#include <QMutex>
#include <QDebug>
#include <QString>

using pair = QPair<QString, int>;

class WordCounterThread : public QThread {
    Q_OBJECT

public:
    explicit WordCounterThread(QObject *parent = nullptr);
    ~WordCounterThread();

    void setFilePath(const QString &filePath);
    void stop();
    void wordHighestResult(const QMap<QString, int> &countedWords);
    void printHighestResult(const QList<pair> vec, qsizetype nResults);

protected:
    // Основной метод, выполняющийся при старте потока.
    void run() override;

signals:
    void processingStarted();
    void processingProgress(double progress);
    void processingFinished();
    void processingCancelled();

private:
    QString m_filePath;
    bool m_cancel;
    QMutex m_mutex;
    double progress_state;
    QMap<QString, int> m_wordCount;
    QList<pair> m_vecWordCount;
};

#endif // WORDCOUNTERTHREAD_H
