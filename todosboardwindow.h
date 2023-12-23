#ifndef TODOSBOARDWINDOW_H
#define TODOSBOARDWINDOW_H
#include "todocomponent.h"
#include "assigntodo.h"

#include <QMainWindow>

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

public slots:
    void onAddToDoButtonClicked();


private:
    explicit toDosBoardWindow(QWidget *parent = nullptr);

    QGridLayout *mainGridLayout;
    QLabel *title;
    QPushButton *addToDoPushButton;
    QGridLayout *toDosGridLayout;
    static toDosBoardWindow *instance;




};

#endif // TODOSBOARDWINDOW_H
