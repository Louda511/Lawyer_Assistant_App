#ifndef TODOSBOARDWINDOW_H
#define TODOSBOARDWINDOW_H
#include "todocomponent.h"

#include <QMainWindow>

class toDosBoardWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit toDosBoardWindow(QWidget *parent = nullptr);
    //~toDosBoardWindow(); // Destructor declaration

    void addToDoComponents(const QList<toDoComponent *> &toDoComponents);

    void addSingleToDoComponent(toDoComponent *td);

    //getters

    QGridLayout* getToDosGridLayout() const;
    static toDosBoardWindow *getInstance();
    QGridLayout* getToDosGridLayout();



private:
    QGridLayout *mainGridLayout;
    QLabel *title;
    QPushButton *addToDoPushButton;
    QGridLayout *toDosGridLayout;
    static toDosBoardWindow *instance;


signals:

};

#endif // TODOSBOARDWINDOW_H
