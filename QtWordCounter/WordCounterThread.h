#ifndef WORDCOUNTERTHREAD_H
#define WORDCOUNTERTHREAD_H

#include <QThread>
#include <QString>
#include <QDebug>


// Класс WordCounterThread наследует QThread и выполняет чтение и обработку файла в фоновом потоке.
class WordCounterThread : public QThread {
    Q_OBJECT

public:
    // Конструктор принимает путь к файлу и передает его в поток.
    explicit WordCounterThread(const QString& filePath, QObject* parent = nullptr);

    // Переопределение метода run(), который выполняется при запуске потока.
    void run() override;

signals:
    // Сигнал processingFinished() будет испущен, когда обработка завершится.
    void processingFinished();

private:
    // Путь к файлу, который нужно обработать.
    QString m_filePath;
};


#endif // WORDCOUNTERTHREAD_H
