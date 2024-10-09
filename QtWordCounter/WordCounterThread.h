#ifndef WORDCOUNTERTHREAD_H
#define WORDCOUNTERTHREAD_H

#include <QThread>
#include <QMutex>
#include <QDebug>
#include <QString>

// Класс WordCounterThread наследует QThread и выполняет обработку файла в фоновом режиме.
class WordCounterThread : public QThread {
    Q_OBJECT

public:
    explicit WordCounterThread(QObject *parent = nullptr);
    ~WordCounterThread();

    // Устанавливаем путь к файлу для обработки.
    void setFilePath(const QString &filePath);

    // Метод для остановки выполнения потока.
    void stop();

protected:
    // Основной метод, выполняющийся при старте потока.
    void run() override;

signals:
    void processingStarted();    // Сигнал начала обработки.
    void processingProgress(int progress); // Сигнал прогресса обработки (0-100).
    void processingFinished();   // Сигнал завершения обработки.
    void processingCancelled();  // Сигнал отмены обработки.

private:
    QString m_filePath;          // Путь к файлу.
    bool m_cancel;               // Флаг для управления остановкой потока.
    QMutex m_mutex;              // Мьютекс для защиты доступа к m_cancel.
    int progress_state;
};

#endif // WORDCOUNTERTHREAD_H
