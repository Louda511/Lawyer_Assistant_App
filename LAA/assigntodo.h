#ifndef ASSIGNTODO_H
#define ASSIGNTODO_H

#include <QLineEdit>
#include <QDateEdit>
#include <QTextEdit>
#include <QLabel>
#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QComboBox>
#include <QCalendarWidget>
#include <QMessageBox>
#include <QPushButton>
#include "todo.h"
#include "todocomponent.h"
#include "todosboardwindow.h"
#include "boardwindowapi.h"
#include <QChar>

class assignToDo : public QDialog
{
    Q_OBJECT
public:

    //getters
    static assignToDo* getInstance();
    void setAsigneeComboBoxValues();


signals:


private slots:
    void updateDate();
    void onOkButtonClicked();

private:
    explicit assignToDo(QWidget *parent = nullptr);

    QLabel *titleLabel;
    QLabel *descriptionLabel;
    QLabel *deadLineLabel;
    QLabel *asigneeLabel;
    QLineEdit *titleLineEdit;
    QTextEdit *descriptionTextEdit;
    QDateEdit *deadLineDateEdit;
    QComboBox *asigneeComboBox;
    QDialogButtonBox *buttonBox;
    QCalendarWidget *calendarWidget;  // Calendar widget
    static assignToDo *instance;
};

#endif // ASSIGNTODO_H
