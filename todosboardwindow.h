#ifndef TODOSBOARDWINDOW_H
#define TODOSBOARDWINDOW_H
#include "todocomponent.h"

#include <QMainWindow>

class toDosBoardWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit toDosBoardWindow(QWidget *parent = nullptr);

private:
    QGridLayout *mainGridLayout;
    QLabel *title;
    QPushButton *addToDoPushButton;
    QGridLayout *toDosGridLayout;

signals:

};

#endif // TODOSBOARDWINDOW_H
