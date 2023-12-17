#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qpushbutton.h"
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QMessageBox>
#include <QScrollBar>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonNewChat_clicked();

    void onGetNetworkReply(QNetworkReply *reply);
    // void onButtonClickedThread();
    void on_pushButtonSendReq_clicked();
    void onNetworkReply(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    std::vector<QPushButton*> buttonsThread;
};
#endif // MAINWINDOW_H
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qpushbutton.h"
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QMessageBox>
#include <QScrollBar>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonNewChat_clicked();

    void onGetNetworkReply(QNetworkReply *reply);
    // void onButtonClickedThread();
    void on_pushButtonSendReq_clicked();
    void onNetworkReply(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    std::vector<QPushButton*> buttonsThread;
};
#endif // MAINWINDOW_H