// WordCounterThread.cpp
#include "WordCounterThread.h"

// Конструктор класса WordCounterThread.
// Инициализирует m_filePath значением filePath.
WordCounterThread::WordCounterThread(const QString& filePath, QObject* parent)
    : QThread(parent), m_filePath(filePath) {}

// Метод run() выполняется при запуске потока и выполняет задачи по чтению и обработке файла.
void WordCounterThread::run() {
    // Симулируем процесс чтения файла с помощью вывода сообщения в консоль.
    qDebug() << "Чтение файла: " << m_filePath;

    // Задержка в 2 секунды для симуляции времени, необходимого на чтение файла.
    QThread::sleep(2);

    // Симулируем процесс обработки файла с помощью вывода сообщения в консоль.
    qDebug() << "Обработка файла";

    // Задержка в 2 секунды для симуляции времени, необходимого на обработку данных.
    QThread::sleep(2);

    // Испускаем сигнал, чтобы уведомить об окончании обработки.
    emit processingFinished();
}


