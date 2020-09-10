#include "ChangeDialogWindow.h"

ChangeDialogWindow::ChangeDialogWindow() : AddDialogWindow(nullptr)
{
    this->setWindowTitle("Изменение");
    add_button->setText("Изменить");
    connect(add_button,SIGNAL(clicked(bool)),this,SLOT(accept()));
}

ChangeDialogWindow::~ChangeDialogWindow()
{
}
