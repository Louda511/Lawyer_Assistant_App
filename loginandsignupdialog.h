#ifndef LOGINANDSIGNUPDIALOG_H
#define LOGINANDSIGNUPDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class loginAndSignUpDialog; }
QT_END_NAMESPACE

class loginAndSignUpDialog : public QDialog
{
    Q_OBJECT

public:
    loginAndSignUpDialog(QWidget *parent = nullptr);
    ~loginAndSignUpDialog();
    static loginAndSignUpDialog* getInstance();

private slots:
    void on_loginButton_clicked();

    void on_signUpButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::loginAndSignUpDialog *ui;
    static loginAndSignUpDialog* instance;
};
#endif // LOGINANDSIGNUPDIALOG_H
