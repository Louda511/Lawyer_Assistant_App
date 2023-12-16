#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonNewChat_clicked()
{
    QString threadName = "Threaaad!!!";
    QPushButton *button = new QPushButton(threadName);
    buttonsThread.push_back(button);
    // connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClickedThread);
    ui->scrollAreaThreadsWidgetContents1->addWidget(button);
}




