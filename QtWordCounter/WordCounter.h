#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <QObject>
#include <QFile>

class WordCounter : public QObject {
    Q_OBJECT

public:
    explicit WordCounter(QObject *parent = nullptr):QObject(parent){};

public slots:
    void openFile(const QString &filePath);  // Метод для открытия файла


private:
    QFile file;  // Переменная для хранения файла

};

#endif // WORDCOUNTER_H
