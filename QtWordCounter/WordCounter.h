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
    // Конструктор создает объект класса и инициализирует указатель потока как nullptr.
    explicit WordCounter(QObject* parent = nullptr);

    // Деструктор освобождает ресурсы, если поток был запущен.
    ~WordCounter();

    // Метод openFile() вызывается из QML для открытия диалога выбора файла.
    Q_INVOKABLE void openFile(const QString &filePath);

    // Метод startProcessing() вызывается из QML для запуска процесса чтения и обработки файла.
    Q_INVOKABLE void startProcessing();

private slots:
    // Слот onProcessingFinished() вызывается при завершении обработки файла.
    void onProcessingFinished();

private:
    // Путь к выбранному файлу.
    QString m_filePath;

    // Указатель на объект потока.
    WordCounterThread* m_thread;
};

#endif // WORDCOUNTER_H

