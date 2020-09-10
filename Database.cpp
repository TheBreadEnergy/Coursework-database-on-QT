#include "Database.h"

database::database()
{
    count=0;
    status=false;
    a=0;
}

void database::addNew(file file2)
{
    data<<file2;
    count++;
}

void database::change(int number, QString name, int size, QString type, QString date)
{
    file new_file;
    new_file.name = name;
    new_file.size = size;
    new_file.type = type;
    new_file.date = date;
    data[number]=new_file;
}


QString database::print(int i)
{
    if(a==4)
        a=0;
    file new_file;
    new_file = data[i];
    QString text;
    if(a==0)text=new_file.name;
    if(a==1)text.setNum(new_file.size);
    if(a==2)text=new_file.type;
    if(a==3)text=new_file.date;
    a++;
    return text;
}

void database::remove(int i)
{
    data.removeAt(i);
    count--;
}

void database::clear()
{
    data.clear();
    count=0;
}

QString database::get_name(int i)
{
    return data[i].name;
}

int database::get_size(int i)
{
    return data[i].size;

}

QString database::get_type(int i)
{
    return data[i].type;
}

QString database::get_date(int i)
{
    return data[i].date;
}

database::~database()
{
}
