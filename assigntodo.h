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

class assignToDo : public QDialog
{
    Q_OBJECT
public:

    //getters
    static assignToDo* getInstance();

signals:


private slots:
    void updateDate();


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
