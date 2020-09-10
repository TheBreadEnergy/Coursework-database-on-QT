#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QValidator>

class AddDialogWindow : public QDialog
{
    Q_OBJECT

protected:
    QLineEdit *name_line;
    QLineEdit *size_line;
    QLineEdit *type_line;
    QLineEdit *date_line;
    QLabel *name_label;
    QLabel *size_label;
    QLabel *type_label;
    QLabel *date_label;
    QLabel *size_label_back;
    QPushButton *add_button;
    QHBoxLayout *name_hbox;
    QHBoxLayout *size_hbox;
    QHBoxLayout *type_hbox;
    QHBoxLayout *date_hbox;
    QVBoxLayout *vbox;

public:
    AddDialogWindow(QWidget *parent);
    QString get_name();
    int get_size();
    QString get_type();
    QString get_date();
    void set_name(QString name);
    void set_size(int size);
    void set_type(QString type);
    void set_date(QString date);
    ~AddDialogWindow();
};

#endif // DIALOG_H
