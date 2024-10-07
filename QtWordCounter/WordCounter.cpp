#include "WordCounter.h"
#include <QDebug>

void WordCounter::openFile(const QString &filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        qDebug() << "File" << filePath << "is open.";
        file.close();  // Закрываем файл после использования
    } else {
        qDebug() << "Failed to open file:" << filePath << "Error:" << file.errorString();
    }
}
