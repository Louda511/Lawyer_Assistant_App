#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qpushbutton.h"
#include <QMainWindow>

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


    // void onButtonClickedThread();
private:
    Ui::MainWindow *ui;
    std::vector<QPushButton*> buttonsThread;
};
#endif // MAINWINDOW_H
