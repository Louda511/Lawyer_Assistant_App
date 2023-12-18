#include "mainwindow.h"
#include "qtextbrowser.h"
#include "ui_mainwindow.h"
// thread_k6SV1GuiIIRXojo6cM5Wi7pF
int count=0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db_connection = QSqlDatabase::addDatabase("QSQLITE");
    db_connection.setDatabaseName(QCoreApplication::applicationDirPath()+"/Local.db");

    db_connection.open();
    QSqlDatabase::database().transaction();
    QSqlQuery querycount(db_connection);

    querycount.prepare("select * from Thread");

    querycount.exec();
    QSqlDatabase::database().commit();

    while(querycount.next())
    {
        count++;
    }
    db_connection.close();

    while(count)
    {
        db_connection.open();
        QSqlDatabase::database().transaction();
        QSqlQuery queryview(db_connection);

        QString stringValue = QString::number(count);
        queryview.prepare("select Request from (select Request,min(ID) from Chats where Thread_id='"+stringValue+"')");

        queryview.exec();
        QSqlDatabase::database().commit();

        QString threadName;
        while(queryview.next())
        {
            threadName= queryview.value(0).toString();
        }



        QPushButton *button = new QPushButton(threadName);
        buttonsThread.push_back(button);
        // connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClickedThread);
        ui->scrollAreaThreadsWidgetContents1->addWidget(button);
        count--;
    }

    db_connection.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonNewChat_clicked()
{
    QString threadName = "Threaaad!!!";
    QPushButton *button = new QPushButton(threadName);
    buttonsThread.push_back(button);
    // connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClickedThread);
    ui->scrollAreaThreadsWidgetContents1->addWidget(button);

    // Create a QNetworkAccessManager
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Create a QNetworkRequest with the URL of your server
    QNetworkRequest request(QUrl("https://lawyerassistant.up.railway.app/new"));  // Replace with your server URL

    // Connect to the finished signal to handle the reply
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::onGetNetworkReply);

    // Send the GET request
    manager->get(request);
}

// Slot to handle the GET network reply
void MainWindow::onGetNetworkReply(QNetworkReply *reply) {
    // Check for errors
    if (reply->error() != QNetworkReply::NoError) {
        // Handle the error, show a message box for example
        QMessageBox::critical(this, "Error", "Failed to send GET request: " + reply->errorString());
    } else {
        // Read the server's response as a string
        QString responseData = QString::fromUtf8(reply->readAll());

        // Process the response data
        qDebug() << "GET request successful!";
        qDebug() << "Response data:" << responseData;

        // Perform actions with the response data, e.g., display it or use it in your application
    }

    // Clean up the reply object
    reply->deleteLater();
}



void MainWindow::on_pushButtonSendReq_clicked()
{
    curThreadId ="thread_k6SV1GuiIIRXojo6cM5Wi7pF";
    // Get the content of the QTextEdit
    QString content = ui->textEditMsg->toPlainText();  // Assuming textEditMsg is a member variable in your class

    // Create a QNetworkAccessManager
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Create a QNetworkRequest with the URL of your server
    QNetworkRequest request(QUrl("https://lawyerassistant.up.railway.app/chat"));  // Replace with your server URL

    // Set the content type header for a JSON request
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Create a QUrlQuery and add your content as a parameter
    QUrlQuery postData;
    postData.addQueryItem("msg", content);
    postData.addQueryItem("threadId", curThreadId);

    // Convert the QUrlQuery to QByteArray
    QByteArray postDataByteArray = postData.toString(QUrl::FullyEncoded).toUtf8();

    // Connect to the finished signal to handle the reply
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::onNetworkReply);

    // Send the POST request
    manager->post(request, postDataByteArray);


}
void MainWindow::onNetworkReply(QNetworkReply *reply) {
    // Check for errors
    if (reply->error() != QNetworkReply::NoError) {
        // Handle the error, show a message box for example
        QMessageBox::critical(this, "Error", "Failed to send POST request: " + reply->errorString());
    } else {
        // Read the server's response
        QByteArray responseData = reply->readAll();
        QString responseString = QString::fromUtf8(responseData);
        QString requestString = ui->textEditMsg->toPlainText();
        // Create a new text browser to display the response
        QTextBrowser *responseTextBrowser = new QTextBrowser(this);
        responseTextBrowser->setPlainText(responseString);

        // Create a new text browser to display the request
        QTextBrowser *reqTextBrowser = new QTextBrowser(this);
        reqTextBrowser->setPlainText(requestString);

        // Set the size policy to Expanding for both text browsers
        responseTextBrowser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        reqTextBrowser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        // Adjust the size of the text browsers to fit their content
        responseTextBrowser->adjustSize();
        reqTextBrowser->adjustSize();
        // Add the new text browsers to the layout
        ui->scrollAreaChatsLayout->addWidget(reqTextBrowser);
        ui->scrollAreaChatsLayout->addWidget(responseTextBrowser);



        // Scroll to the bottom to show the latest response
        ui->scrollAreaChats->verticalScrollBar()->setValue(ui->scrollAreaChats->verticalScrollBar()->maximum());

        // Clear the content of the QTextEdit
        ui->textEditMsg->clear();
        db_connection = QSqlDatabase::addDatabase("QSQLITE");
        db_connection.setDatabaseName(QCoreApplication::applicationDirPath()+"/Local.db");

        db_connection.open();
        Chat newChat(requestString,responseString,curThreadId,db_connection);
        db_connection.close();
    }

    // Clean up the reply object
    reply->deleteLater();
}
