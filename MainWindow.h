#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QMenuBar>
#include <QDebug>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QTextCodec>
#include <QHeaderView>
#include <QMessageBox>
#include "Database.h"
#include "AddDialogWindow.h"
#include "ChangeDialogWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QLabel *label_search;
    QLabel *label_count;
    QPushButton *add;
    QPushButton *change;
    QPushButton *remove;
    QLineEdit *search_line;
    QLabel *search_label;
    QLabel *status_label;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QToolBar *tool_bar;
    QStatusBar *status_bar;
    QTableWidget *table;
    database *data;

public:
    MainWindow(QWidget *parent);
    ~MainWindow();
    void clear_database();
    void open_file();

public slots:
    void add_click();
    void show_database();
    void remove_click();
    void change_click();
    void search(QString search);
    void save_to_file();
    void open_from_file();
    void new_database();
    void merger();
    void info_show();
    void instructions_show();
};

#endif // MAINWINDOW_H
