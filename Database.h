#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QList>

class database {

public:
    int count;
    bool status;
    struct file
    {
        QString name;        //Название файла
        int size;       //Размер файла
        QString type;        //Тип файла
        QString date;       //Дата создания
    };
    database();
    void addNew(file file2);
    void change(int number, QString name, int size, QString type, QString date);
    void remove(int i);
    void clear();
    QString print(int i);
    QString get_name(int i);
    int get_size(int i);
    QString get_type(int i);
    QString get_date(int i);
    ~database();
    QList<file> data;
private:
    int a;

};



#endif // DATABASE_H
