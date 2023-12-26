#ifndef TODOSBOARDWINDOW_H
#define TODOSBOARDWINDOW_H
#include <QMainWindow>
#include <QToolBar>
#include <QMenuBar>
#include "todocomponent.h"
#include "assigntodo.h"
#include "mainwindow.h"


class toDosBoardWindow : public QMainWindow
{
    Q_OBJECT
public:
    //~toDosBoardWindow(); // Destructor declaration

    void addToDoComponents(const QList<toDoComponent *> &toDoComponents);

    void addSingleToDoComponent(toDoComponent *td);

    //getters

    QGridLayout* getToDosGridLayout() const;
    static toDosBoardWindow *getInstance();
    QGridLayout* getToDosGridLayout();
    void addToDoComponents(toDoComponent *component);


public slots:
    void onAddToDoButtonClicked();
    void openChat();


private:
    explicit toDosBoardWindow(QWidget *parent = nullptr);

    QGridLayout *mainGridLayout;
    QLabel *title;
    QPushButton *addToDoPushButton;
    QGridLayout *toDosGridLayout;
    static toDosBoardWindow *instance;
    int row, column;
    QToolBar *mainToolBar;
    QPushButton *chatPage;
    QMenuBar *menuBar;


};

#endif // TODOSBOARDWINDOW_H
