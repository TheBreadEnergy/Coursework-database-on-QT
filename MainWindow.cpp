#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    this->setMinimumSize(700,500);
    this->setWindowTitle("Файлы");
    data = new database();

    menuBar = new QMenuBar;
    menu = new QMenu("Файл");
    menu->addAction("Новый",this,SLOT(new_database()));
    menu->addAction("Открыть",this,SLOT(open_from_file()));
    menu->addAction("Сохранить",this,SLOT(save_to_file()));
    menu->addSeparator();
    menu->addAction("Слияние",this,SLOT(merger()));
    menu_2 = new QMenu("Справка");
    menu_2->addAction("Инструкция",this,SLOT(instructions_show()));
    menu_2->addSeparator();
    menu_2->addAction("О программе",this,SLOT(info_show()));
    menuBar->addMenu(menu);
    menuBar->addSeparator();
    menuBar->addMenu(menu_2);

    tool_bar = new QToolBar;
    tool_bar->setMovable(false);

    status_bar = new QStatusBar;

    add = new QPushButton("Добавить");
    change = new QPushButton("Изменить");
    remove = new QPushButton("Удалить");
    search_line = new QLineEdit;

    label_search = new QLabel("Поиск:");
    label_count = new QLabel;
    search_label = new QLabel;
    status_label = new QLabel;

    table = new QTableWidget(0,4);
    table->setHorizontalHeaderLabels(QStringList()<<"Название"<<"Размер"<<"Тип"<<"Дата создания");
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tool_bar->addWidget(add);
    tool_bar->addWidget(change);
    tool_bar->addWidget(remove);
    tool_bar->addSeparator();
    tool_bar->addWidget(label_search);
    tool_bar->addWidget(search_line);

    status_bar->addWidget(status_label);
    status_bar->addWidget(label_count);
    status_bar->addWidget(search_label);

    this->setCentralWidget(table);
    this->setMenuBar(menuBar);
    this->addToolBar(tool_bar);
    this->setStatusBar(status_bar);

    show_database();

    connect(add,SIGNAL(clicked(bool)),this,SLOT(add_click()));
    connect(add,SIGNAL(clicked(bool)),this,SLOT(show_database()));
    connect(remove,SIGNAL(clicked(bool)),this,SLOT(remove_click()));
    connect(remove,SIGNAL(clicked(bool)),this,SLOT(show_database()));
    connect(change,SIGNAL(clicked(bool)),this,SLOT(change_click()));
    connect(change,SIGNAL(clicked(bool)),this,SLOT(show_database()));

    connect(search_line,SIGNAL(textChanged(QString)),this,SLOT(search(QString)));
}

void MainWindow::add_click()
{
    AddDialogWindow log(nullptr);
    log.setModal(true);
    log.show();

        if(log.exec()==QDialog::Accepted)
        {
            database::file new_file;
            new_file.name = log.get_name();
            new_file.size = log.get_size();
            new_file.type = log.get_type();
            new_file.date = log.get_date();
            data->addNew(new_file);
            data->status=false;
        }
}

void MainWindow::show_database()
{
    table->setRowCount(data->count);
    for(int row=0; row!=data->count; ++row){
        for(int column=0; column!=4; ++column) {
            QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(data->print(row)));
            table->setItem(row, column, newItem);
        }
    }
    label_count->setText(QString("Записей: %0").arg(data->count));
    if(data->status == true)
        status_label->setText("БД сохранена.");
        else
            status_label->setText("БД не сохранена!");
}

void MainWindow::remove_click()
{
    int count = table->currentIndex().row();
    if(count>=0)
    {
        data->remove(count);
        search_label->setText("");
        data->status=false;
    }
    else
        QMessageBox::warning(nullptr, "warning", "Выберите строку для удаления!");
}

void MainWindow::change_click()
{
    int count = table->currentIndex().row();
    if(count>=0)
    {
        ChangeDialogWindow log;
        log.setModal(true);
        log.set_name(data->get_name(count));
        log.set_size(data->get_size(count));
        log.set_type(data->get_type(count));
        log.set_date(data->get_date(count));
            if(log.exec()==QDialog::Accepted)
            {
                data->change(count,log.get_name(),log.get_size(),log.get_type(),log.get_date());
                search_label->setText("");
                 data->status=false;
            }
    }
    else
        QMessageBox::warning(nullptr, "warning", "Выберите строку для изменения!");
}

void MainWindow::search(QString search)
{
    if(search=="")
    {
        for(int i = 0; i<data->count;i++)
        {
            table->showRow(i);
        }
        search_label->setText("");
    }
    else
    {
        int bbb =0;
        for(int i = 0; i<data->count; i++)
        {
            if(search == data->get_name(i))
            {
                table->showRow(i);
                bbb++;
            }

            else table->hideRow(i);
        }
        search_label->setText(QString("Совпадений: %0").arg(bbb));
    }
}

void MainWindow::info_show()
{
    QDialog info;
    info.setModal(true);
    info.setWindowTitle("О программе");
    QPushButton OK("OK");
    QLabel about("Курсовая работа по дисциплине ООП на тему:\n"
                 "Базы данных 'Файл'\n\n"
                 "Выполнил:\n"
                 "Александр Чугуненко - 2018 год\n");
    QVBoxLayout box;
    box.addWidget(&about);
    box.addWidget(&OK);
    info.setLayout(&box);
    info.show();
    connect(&OK,SIGNAL(clicked(bool)),&info,SLOT(accept()));
    if(info.exec()==QDialog::Accepted)
        {
            info.close();
        }
}

void MainWindow::instructions_show()
{
    QDialog instruction;
    instruction.setWindowTitle("Инструкция");
    instruction.setModal(true);
    QPushButton OK("OK");
    QLabel about("\nСмотрите техническую документацию\n");
    QVBoxLayout box;
    box.addWidget(&about);
    box.addWidget(&OK);
    instruction.setLayout(&box);
    instruction.show();
    connect(&OK,SIGNAL(clicked(bool)),&instruction,SLOT(accept()));
    if(instruction.exec()==QDialog::Accepted)
        {
            instruction.close();
        }
}

void MainWindow::save_to_file()
{
    if(data->count!=0&&data->status==false)
    {
        QFile outFile;
        QString filename = QFileDialog::getSaveFileName(nullptr, "Сохранить", "", "*.txt");
        if(filename.isEmpty())
            return;
        if(!filename.endsWith(".txt"))
            filename+=".txt";
        outFile.setFileName(filename);
        if(!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        QTextStream streamOut(&outFile);
        streamOut.setCodec(QTextCodec::codecForName("UTF-8"));
        for (int i=0;i<data->count;i++)
        {
            for (int j=0;j<4;j++)streamOut<<data->print(i)<<"|";
            streamOut<<"\r\n";
        }
        outFile.close();
        data->status=true;
        show_database();
    }
    else QMessageBox::warning(nullptr,"Warning","База данных пуста или уже сохранена!",QMessageBox::Yes);
}

void MainWindow::open_from_file()
{
    if(data->status==true||data->count==0)
    {
        clear_database();
        data->status=true;
        open_file();
    }
    else
    {
        int answer=QMessageBox::warning(nullptr,"Warning","База данных не сохранена!"
                                                    "\nYes для сохранения текущей и открытия новой"
                                                    "\nNo для открытия новой без сохранения текущей"
                                                    "\nCancel для возврата"
                                                    ,QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(answer==QMessageBox::Yes)
        {
            save_to_file();
            clear_database();
            data->status=true;
            open_file();
        }
        else if(answer==QMessageBox::No)
        {
            clear_database();
            data->status=true;
            open_file();
        }
    }
}

void MainWindow::open_file()
{
    QFile inFile;
    QString filename = QFileDialog::getOpenFileName(this, "Открыть", "", "*.txt");
    if(filename.isEmpty())
        return;
    inFile.setFileName(filename);
    if(!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QStringList dataList;
    QString fileData;
    while(!inFile.atEnd())
    {
        fileData = QString(inFile.readLine());
        dataList=fileData.split("|");
        database::file new_file;
        new_file.name=dataList[0];
        new_file.size=dataList[1].toInt();
        new_file.type=dataList[2];
        new_file.date=dataList[3];
        data->addNew(new_file);
    }
    show_database();
    inFile.close();
}

void MainWindow::merger()
{
    if(data->count!=0)
    {
        data->status=false;
        open_file();
    }
        else
            QMessageBox::warning(nullptr,"Warning", "Слияние не может быть произведенно,\nтак как текущая БД пуста!",QMessageBox::Yes);
}

void MainWindow::new_database()
{
    if(data->status==true||data->count==0)
    {
        data->status=false;
        clear_database();
    }
        else
        {
            int answer=QMessageBox::warning(nullptr,"Warning","Yes для сохранения текущей БД в файл "
                                                        "и создания новой.\nNo для очистки текущей БД без сохранения"
                                                        " и создания новой\nCancel для возврата",
                                                        QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
            if(answer==QMessageBox::Yes)
            {
                save_to_file();
                data->status=false;
                clear_database();
            }
                else
                    if(answer==QMessageBox::No)
                        clear_database();
        }
}

void MainWindow::clear_database()
{
    data->clear();
    show_database();
}

MainWindow::~MainWindow()
{

}
