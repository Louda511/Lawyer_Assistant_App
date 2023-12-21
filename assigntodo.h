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
    explicit assignToDo(QWidget *parent = nullptr);

signals:

private slots:
    void updateDate();


private:
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
};

#endif // ASSIGNTODO_H
