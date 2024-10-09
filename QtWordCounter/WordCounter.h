// WordCounter.h
#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <QObject>
#include <QDebug>
#include "WordCounterThread.h"

// Класс WordCounter предоставляет интерфейс для взаимодействия с QML и управляет потоком обработки файла.
class WordCounter : public QObject {
    Q_OBJECT

public:
    explicit WordCounter(QObject* parent = nullptr);
    ~WordCounter();
    int progress() const;

signals:
    void processingStarted();
    void processingProgress(int progress);
    void processingFinished();
    void processingCancelled();
    void fileSelected(const QString &filePath);

public slots:
    void openFile(const QString& filePath);
    void startProcessing();
    void cancelProcessing();

private:
    // Путь к выбранному файлу.
    QString m_filePath;

    // Указатель на объект потока.
    WordCounterThread* m_workerThread;

    int progress_state;
};

#endif // WORDCOUNTER_H

