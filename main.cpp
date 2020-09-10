#include "MainWindow.h"
#include <QApplication>
#include <QtDebug>
#include <QDebug>
#include <QFileDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow *window = new MainWindow(nullptr);
    window->show();

    QFile styleSheetFile;

    styleSheetFile.setFileName(":/style/style.css");
    styleSheetFile.open(QFile::ReadOnly);
    QString qssString = styleSheetFile.readAll();
    a.setStyleSheet(qssString);
        if(styleSheetFile.exists())
            qDebug() << "[styleSheet loaded]";
    return a.exec();
}
