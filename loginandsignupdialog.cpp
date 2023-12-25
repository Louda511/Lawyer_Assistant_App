#include "loginandsignupdialog.h"
#include "ui_loginandsignupdialog.h"
#include "authenticationpageapi.h"


loginAndSignUpDialog::loginAndSignUpDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::loginAndSignUpDialog)
{

    ui->setupUi(this);
    //adjustSize();
    /*
    loginPage = new login(this);
    adjustSize();
    */
   // ui->stackedWidget->show();
    //adjustSize();
     //ui->loginPage->sizeHint();
   // ui->stackedWidget->resize(250,170);
    ui->passwordLineEditLogIn->setEchoMode(QLineEdit::Password);
    ui->passwordLineEditSignUp->setEchoMode(QLineEdit::Password);
    ui->confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);
    setWindowTitle("Sign In");

}

loginAndSignUpDialog::~loginAndSignUpDialog()
{
    delete ui;
  //  delete loginPage;
}


void loginAndSignUpDialog::on_loginButton_clicked()
{
    if(ui->stackedWidget->currentIndex() == 0)
    {
        authenticationPageApi::performLogin(ui->emailLineEditLogIn->text(),ui->passwordLineEditLogIn->text());
        authenticationPageApi::getJuniorsData();
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(0);
        /*
        ui->stackedWidget->resize(250,170);
        resize(300,200);
        */
    }
    setWindowTitle("Sign In");
    //adjustSize();

}


void loginAndSignUpDialog::on_signUpButton_clicked()
{

    if(ui->stackedWidget->currentIndex() == 1)
    {

        QString name = ui->firstNameLineEdit->text()+" "+ui->lastNameLineEdit->text();
        QString email = ui->emailTextEditSignUp->text();
        QString password = ui->passwordLineEditSignUp->text();
        QString jobTitle = ui->jobTitleLineEdit->text();
        QString type = ui->comboBox->currentText().toLower();
        QString supEmail;

        if(ui->comboBox->currentIndex() == 0)
            supEmail = ui->supervisorLineEdit->text();
        else
            supEmail = email;

        // Debugging output
        qDebug() << "Name:" << name;
        qDebug() << "Email:" << email;
        qDebug() << "Password:" << password;
        qDebug() << "Job Title:" << jobTitle;
        qDebug() << "Type:" << type;
        qDebug() << "Supervisor Email:" << supEmail;

        authenticationPageApi::performSignUp(name,email,password,jobTitle,type,supEmail);

        user *u = user::getInstance();
        u->setName(name);
        u->setEmail(email);
        u->setPassword(password);
        u->setJobTitle(jobTitle);
        u->setType(type);

        toDosBoardWindow::getInstance()->show();
        //loginAndSignUpDialog::getInstance()->close();
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(1);

        /*
        ui->stackedWidget->resize(250,440);
        resize(300,500);
        */
    }
    setWindowTitle("Sign Up");

    //adjustSize();

}


void loginAndSignUpDialog::on_comboBox_currentIndexChanged(int index)
{
    if(ui->comboBox->currentIndex() == 0)
    {
        ui->supervisorLabel->setVisible(true);
        ui->supervisorLineEdit->setVisible(true);
    }
    else
    {
        ui->supervisorLabel->setVisible(false);
        ui->supervisorLineEdit->setVisible(false);
    }
}

loginAndSignUpDialog* loginAndSignUpDialog::instance = nullptr;

// Function to get the instance of the singleton class
loginAndSignUpDialog* loginAndSignUpDialog::getInstance() {
    // Create the instance if it doesn't exist yet
    if (instance == nullptr) {
        instance = new loginAndSignUpDialog();
    }
    return instance;
}
