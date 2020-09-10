#include "AddDialogWindow.h"

AddDialogWindow::AddDialogWindow(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Добавление");
    name_label = new QLabel("Имя файла");
    name_line = new QLineEdit();
    name_hbox = new QHBoxLayout();
    name_hbox->addWidget(name_label);
    name_hbox->addWidget(name_line);

    type_label = new QLabel("Тип файла");
    type_line = new QLineEdit();
    type_hbox = new QHBoxLayout();
    type_hbox->addWidget(type_label);
    type_hbox->addWidget(type_line);

    size_label = new QLabel("Размер фала");
    size_line = new QLineEdit();
    size_line->setValidator(new QIntValidator(0,100000000,this));
    size_label_back = new QLabel("КБ");
    size_hbox = new QHBoxLayout();
    size_hbox->addWidget(size_label);
    size_hbox->addWidget(size_line);
    size_hbox->addWidget(size_label_back);

    date_label = new QLabel("Дата создания");
    date_line = new QLineEdit();
    date_hbox = new QHBoxLayout();
    date_hbox->addWidget(date_label);
    date_hbox->addWidget(date_line);

    add_button = new QPushButton("Добавить");

    vbox = new QVBoxLayout();
    vbox->addLayout(name_hbox);
    vbox->addLayout(size_hbox);
    vbox->addLayout(type_hbox);
    vbox->addLayout(date_hbox);
    vbox->addWidget(add_button);

    this->setLayout(vbox);
    connect(add_button,SIGNAL(clicked(bool)),this,SLOT(accept()));
}

QString AddDialogWindow::get_name()
{
    return name_line->text();
}

int AddDialogWindow::get_size()
{
    return size_line->text().toInt();
}

QString AddDialogWindow::get_type()
{
    return type_line->text();
}

QString AddDialogWindow::get_date()
{
    return date_line->text();
}

//...........................................................................
void AddDialogWindow::set_name(QString name)
{
    name_line->setText(name);
}

void AddDialogWindow::set_size(int size)
{
    size_line->setText(QString().setNum(size));
}

void AddDialogWindow::set_type (QString type)
{
    type_line->setText(type);
}

void AddDialogWindow::set_date(QString date)
{
    date_line->setText(date);
}

AddDialogWindow::~AddDialogWindow()
{
}
