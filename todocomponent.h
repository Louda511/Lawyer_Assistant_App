// todocomponent.h
#ifndef TODOCOMPONENT_H
#define TODOCOMPONENT_H

#include <QWidget>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QTextBrowser>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QMainWindow>
#include "user.h"
#include "toDo.h"

class toDoComponent : public QWidget {
    Q_OBJECT
public:
    toDoComponent(QWidget *parent = nullptr);

private:
    QCheckBox *checkbox;
    QTextBrowser *description;
    QLabel *deadLine;
    QLabel *supervisor;
    QLabel *lawyer;
    QPushButton deleteToDo;


};

#endif // TODOCOMPONENT_H

