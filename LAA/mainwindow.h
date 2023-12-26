#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "conversation.h"
#include "qpushbutton.h"
#include "chat.h"
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QMessageBox>
#include <QScrollBar>
#include "qsqldatabase.h"
#include <QtSql>
#include <QSqlDatabase>
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
    QString curThreadId="";
    QString newThreadId="";
    static MainWindow* getInstance();


private slots:
    void on_pushButtonNewChat_clicked();

    void onGetNetworkReply(QNetworkReply *reply);
    void onButtonClickedThread();
    void on_pushButtonSendReq_clicked();
    void onNetworkReply(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    std::vector<QPushButton*> buttonsThread;
    QSqlDatabase db_connection;
    static MainWindow *instance;

};
#endif // MAINWINDOW_H
