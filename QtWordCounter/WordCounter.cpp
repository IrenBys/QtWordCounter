// WordCounter.cpp
#include "WordCounter.h"
#include <QFile>

// Конструктор класса WordCounter.
// Инициализирует m_thread значением nullptr, что означает, что поток еще не создан.
WordCounter::WordCounter(QObject* parent)
    : QObject(parent), m_thread(nullptr) {}

// Деструктор класса WordCounter.
// Если поток был создан, он завершает его работу, ожидает завершения и удаляет объект потока.
WordCounter::~WordCounter() {
    if (m_thread) {
        m_thread->quit();  // Завершаем выполнение потока.
        m_thread->wait();  // Ожидаем завершения потока.
        delete m_thread;   // Удаляем объект потока, чтобы освободить память.
    }
}

// Метод openFile() открывает диалоговое окно для выбора текстового файла и сохраняет путь к выбранному файлу.
void WordCounter::openFile(const QString &filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        m_filePath = filePath;
        qDebug() << "File" << m_filePath << "is open.";
    } else {
        qDebug() << "Failed to open file:" << filePath << "Error:" << file.errorString();
    }
}

// Метод startProcessing() запускает новый поток для обработки файла.
void WordCounter::startProcessing() {
    // Проверяем, выбран ли файл. Если нет, выводим предупреждение и выходим из метода.
    if (m_filePath.isEmpty()) {
        qDebug() << "Файл не выбран!";
        return;
    }

    // Если поток уже был создан, завершаем его и удаляем, чтобы создать новый.
    if (m_thread) {
        m_thread->quit();  // Завершаем работу текущего потока.
        m_thread->wait();  // Ожидаем завершения потока.
        delete m_thread;   // Удаляем объект потока.
    }

    // Создаем новый объект WordCounterThread с текущим путем к файлу.
    m_thread = new WordCounterThread(m_filePath, this);

    // Подключаем сигнал завершения обработки потока к слоту onProcessingFinished().
    connect(m_thread, &WordCounterThread::processingFinished, this, &WordCounter::onProcessingFinished);

    // Запускаем выполнение потока.
    m_thread->start();
}

// Слот onProcessingFinished() вызывается, когда обработка файла завершена.
void WordCounter::onProcessingFinished() {
    // Выводим сообщение в консоль, что обработка завершена.
    qDebug() << "Обработка завершена";
}

