#include "mainwindow.h"
#include "qtextbrowser.h"
#include "ui_mainwindow.h"
// thread_k6SV1GuiIIRXojo6cM5Wi7pF
int count=0,c=0;
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

    while(c<count)
    {
        db_connection.open();
        QSqlDatabase::database().transaction();
        QSqlQuery queryview(db_connection);
        QString stringValue = QString::number(c);
        // QString stringValue = QString::number(count);

        queryview.prepare("select substr(Request,1, 20) from (select Request from (select Request,min(ID) from Chats where Thread_id='"+stringValue+"'));");

        queryview.exec();
        QSqlDatabase::database().commit();

        QString threadName;
        while(queryview.next())
        {
            threadName= queryview.value(0).toString();
        }



        QPushButton *button = new QPushButton(threadName);
        buttonsThread.push_back(button);
        connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClickedThread);
        ui->scrollAreaThreadsWidgetContents1->addWidget(button);
        c++;
    }

    db_connection.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonNewChat_clicked()
{
    while (QLayoutItem* item = ui->scrollAreaChatsLayout->takeAt(0)) {
        QWidget* widget = item->widget();
        if (widget) {
            ui->scrollAreaChatsLayout->removeWidget(widget);
            delete widget;
        }
        delete item;
    }

    if(newThreadId == ""){
        // Create a QNetworkAccessManager
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);

        // Create a QNetworkRequest with the URL of your server
        QNetworkRequest request(QUrl("https://lawyerassistant.up.railway.app/new"));  // Replace with your server URL

        // Connect to the finished signal to handle the reply
        connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::onGetNetworkReply);

        // Send the GET request
        manager->get(request);
    }
}

// Slot to handle the GET network reply
void MainWindow::onGetNetworkReply(QNetworkReply *reply) {
    // Check for errors
    if (reply->error() != QNetworkReply::NoError) {
        // Handle the error, show a message in status bar for example
         statusBar()->showMessage("Try again, Failed to send GET request: " + reply->errorString(), 5000); // Show for 5 seconds

    } else {
        // Read the server's response as a string
        newThreadId = QString::fromUtf8(reply->readAll());
        curThreadId = newThreadId;
        // Process the response data
        qDebug() << "GET request successful!";
        qDebug() << "Response data:" << newThreadId;

        // Perform actions with the response data, e.g., display it or use it in your application
    }

    // Clean up the reply object
    reply->deleteLater();
}



void MainWindow::on_pushButtonSendReq_clicked()
{
    // curThreadId ="thread_k6SV1GuiIIRXojo6cM5Wi7pF";
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
        statusBar()->showMessage("Try again, Failed to send POST request: " + reply->errorString(), 5000);
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
        if (curThreadId==newThreadId) {
            newThreadId = "";
            QString threadName = requestString.left(20);
            QPushButton *button = new QPushButton(threadName);
            buttonsThread.push_back(button);
            int lastIndex = buttonsThread.size() - 1;
            connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClickedThread);
            ui->scrollAreaThreadsWidgetContents1->addWidget(button);
            db_connection = QSqlDatabase::addDatabase("QSQLITE");
            db_connection.setDatabaseName(QCoreApplication::applicationDirPath()+"/Local.db");

            db_connection.open();
            Conversation newConv(curThreadId,"lawyer1",lastIndex,db_connection);
            db_connection.close();
        }
        db_connection = QSqlDatabase::addDatabase("QSQLITE");
        db_connection.setDatabaseName(QCoreApplication::applicationDirPath()+"/Local.db");

        db_connection.open();
        Chat newChat(requestString,responseString,QString::number(buttonsThread.size() - 1),db_connection);
        db_connection.close();
    }

    // Clean up the reply object
    reply->deleteLater();
}
void MainWindow::onButtonClickedThread(){
    while (QLayoutItem* item = ui->scrollAreaChatsLayout->takeAt(0)) {
        QWidget* widget = item->widget();
        if (widget) {
            ui->scrollAreaChatsLayout->removeWidget(widget);
            delete widget;
        }
        delete item;
    }
    // Determine which button triggered the signal
    QPushButton *senderButton = qobject_cast<QPushButton *>(sender());
    if (senderButton) {
        // Get the index of the clicked button in the array
        int buttonIndex = -1;
        for (int i = 0; i < buttonsThread.size(); ++i) {
            if (buttonsThread[i] == senderButton) {
                buttonIndex = i;
                break;
            }
        }

        if (buttonIndex != -1) {
            // Get the text of the clicked button
            QString buttonText = senderButton->text();
            qDebug() << "Button clicked:" << buttonText << " at index:" << buttonIndex;
            db_connection = QSqlDatabase::addDatabase("QSQLITE");
            db_connection.setDatabaseName(QCoreApplication::applicationDirPath()+"/Local.db");

            if (db_connection.open()) {
                QSqlQuery query;
                query.prepare("SELECT id FROM thread WHERE Qt_thread_id = :qtThreadId");
                query.bindValue(":qtThreadId", buttonIndex);
                if (query.exec()) {
                    while (query.next()) {
                        // Retrieve the id from the result
                        curThreadId = query.value("id").toString();
                        qDebug() << "ThreadId from dbbbbb: " << curThreadId;
                    }
                } else {
                    // Handle query execution error
                    qDebug() << "Error executing query: " << query.lastError().text();
                }

                query.prepare("SELECT * FROM chats WHERE thread_id = :threadId");
                query.bindValue(":threadId", buttonIndex);

                if (query.exec()) {
                    while (query.next()) {
                        // Extract chat data from the query result
                        QString chatId = query.value("id").toString();
                        QString request = query.value("request").toString();
                        QString response = query.value("response").toString();
                        QString conversationId = query.value("thread_Id").toString();
                        QTextBrowser *responseTextBrowser = new QTextBrowser(this);
                        responseTextBrowser->setPlainText(response);

                        // Create a new text browser to display the request
                        QTextBrowser *reqTextBrowser = new QTextBrowser(this);
                        reqTextBrowser->setPlainText(request);

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

                    }
                } else {
                    // Handle query execution error
                    qDebug() << "Error executing query: " << query.lastError().text();
                }

                // Close the database connection
                db_connection.close();
            } else {
                // Handle database connection error
                qDebug() << "Error opening database: " << db_connection.lastError().text();
            }

            // Add your custom code for button clicks here
            // For example, change the color of the clicked button
            // senderButton->setStyleSheet("background-color: green;");

        }
    }

}
