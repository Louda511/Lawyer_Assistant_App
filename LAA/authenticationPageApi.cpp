#include "authenticationpageapi.h"
#include "todosboardwindow.h"
#include "user.h"
#include "loginandsignupdialog.h"
#include <QMessageBox>

// Define the static member outside the class
QNetworkAccessManager authenticationPageApi::manager;

// Static function to perform a login POST request
void authenticationPageApi::performLogin(const QString &email, const QString &password) {
    // URL of the login endpoint
    QUrl loginUrl("https://lawyerassistant.up.railway.app/login");

    // Create a request
    QNetworkRequest request(loginUrl);

    // Set the content type for the request
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setAttribute(QNetworkRequest::User, "login");


    // Prepare the data to be sent
    QUrlQuery postData;
    postData.addQueryItem("email", email);
    postData.addQueryItem("password", password);

    // Convert the data to QByteArray
    QByteArray postDataBytes = postData.toString(QUrl::FullyEncoded).toUtf8();

    // Perform the POST request
    QNetworkReply *reply = authenticationPageApi::manager.post(request, postDataBytes);

    // Connect the finished signal to the static slot handling the reply
    QEventLoop loop;
    auto onFinished = [&]() {
        authenticationPageApi::onRequestFinished(reply);
        loop.quit();
    };

    QObject::connect(reply, &QNetworkReply::finished, onFinished);

    // Synchronously wait for the reply to finish
    loop.exec();

    // Cleanup
    reply->setProperty("requestType", "login");
    reply->deleteLater();
}

// Static function to perform a sign-up (register) POST request
void authenticationPageApi::performSignUp(const QString &name, const QString &email,
                                          const QString &password, const QString &jobTitle,
                                          const QString &type, const QString &supEmail) {
    // URL of the sign-up (register) endpoint
    QUrl signUpUrl("https://lawyerassistant.up.railway.app/register");

    // Create a request
    QNetworkRequest request(signUpUrl);

    // Set the content type for the request
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setAttribute(QNetworkRequest::User, "login");


    // Prepare the data to be sent
    QJsonObject postData;
    postData["name"] = name;
    postData["email"] = email;
    postData["password"] = password;
    postData["job_title"] = jobTitle;
    postData["type"] = type;
    postData["sup_email"] = supEmail;

    // Convert the data to QByteArray
    QJsonDocument jsonDocument(postData);
    QByteArray postDataBytes = jsonDocument.toJson();

    // Perform the POST request
    QNetworkReply *reply = authenticationPageApi::manager.post(request, postDataBytes);

    // Connect the finished signal to the static slot handling the reply
    QEventLoop loop;

    auto onFinished = [&]() {
        authenticationPageApi::onRequestFinished(reply);
        loop.quit();
    };

    QObject::connect(reply, &QNetworkReply::finished, onFinished);

    // Synchronously wait for the reply to finish
    loop.exec();

    // Cleanup
    reply->setProperty("requestType", "signup");
    //reply->deleteLater();
}

// Static slot to handle the reply when the request is finished
/*
void authenticationPageApi::onRequestFinished(QNetworkReply *reply) {
    // Check for errors
    if (reply->error() == QNetworkReply::NoError) {
        // Request was successful
        qDebug() << "Connection established successfully!";
        qDebug() << "Response:" << reply->readAll();
    } else {
        // Handle error
        qDebug() << "Error:" << reply->errorString();
    }

    // Clean up
    reply->deleteLater();

}
*/
// Static slot to handle the reply when the request is finished
void authenticationPageApi::onRequestFinished(QNetworkReply *reply) {
    // Check for errors
    if (reply->error() == QNetworkReply::NoError) {
        // Request was successful
        QByteArray responseData = reply->readAll();
        qDebug() << "Connection established successfully!";
        qDebug() << "Response:" << responseData;

        // Retrieve information from the request object
        QString requestType = reply->request().attribute(QNetworkRequest::User).toString();


        // Determine if the reply is from performLogin or performSignUp
        if (requestType == "login") {
            // This is the response from performLogin
            qDebug() << "Response from performLogin";
            /*
            QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
            QJsonObject responseData = jsonResponse.object();
            emit (authenticationPageApi::readResponseData(responseData));
            */
            parseResponse(responseData);

        } else if (requestType == "signup") {
            // This is the response from performSignUp
            qDebug() << "Response from performSignUp";
            toDosBoardWindow::getInstance()->show();
            loginAndSignUpDialog::getInstance()->close();

        }
        else if(requestType == "getJuniorsData")
        {
            parseJuniorsData(responseData);
        }
        else {
            // Handle other cases or errors
            qDebug() << "Unknown response";
        }
    } else {
        // Handle error
        qDebug() << "Error:" << reply->errorString();
    }

    // Clean up
    //reply->deleteLater();
}

void authenticationPageApi::parseResponse(const QByteArray &responseData) {
    // Parse the JSON response
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObject = jsonResponse.object();

    // Extract relevant information
    QString user_type = user::getInstance()->getType();
    QString word = jsonObject.value("word").toString();
    bool success;

    success = (word == "supervisor logged in successfully" || word == "logged in successfully");

    if (success) {
        QJsonObject userObject = jsonObject.value("user").toObject();
        parseUser(userObject);
        //close the login page and open todos page
        loginAndSignUpDialog *w = loginAndSignUpDialog::getInstance();
        w->close();

        // Check if "todos" is an array
        if (jsonObject.value("todos").isArray()) {
            QJsonArray todosArray = jsonObject.value("todos").toArray();
            parseTodos(todosArray);
        }
        else
        {
            toDosBoardWindow::getInstance()->show();
            QMessageBox::information(nullptr, "Information", "No ToDo's Found");
        }

    }
    else {
        qDebug() << "Login unsuccessful. Word: " << word;
        QMessageBox::critical(nullptr, "Error", word, QMessageBox::Ok);
    }
}

void authenticationPageApi::parseUser(const QJsonObject &userObject) {
    qDebug() << "Parsing user data...";
    // Extract and print user information
    int id = userObject.value("id").toInt();
    QString name = userObject.value("name").toString();
    QString password = userObject.value("password").toString();
    QString jobTitle = userObject.value("job_title").toString();
    QString type = userObject.value("type").toString();
    QString email = userObject.value("email").toString();
    int supId = userObject.value("sup_id").toInt();

    user::getInstance()->setId(id);
    user::getInstance()->setName(name);
    user::getInstance()->setPassword(password);
    user::getInstance()->setJobTitle(jobTitle);
    user::getInstance()->setType(type);
    user::getInstance()->setEmail(email);
    user::getInstance()->setSupervisorId(supId);

    qDebug() << "User ID: " << id;
    qDebug() << "Name: " << name;
    qDebug() << "Password: " << password;
    qDebug() << "Job Title: " << jobTitle;
    qDebug() << "Type: " << type;
    qDebug() << "Email: " << email;
    qDebug() << "Supervisor ID: " << supId;
}

void authenticationPageApi::parseTodos(const QJsonArray &todosArray) {
    qDebug() << "Parsing todos...";
    // Iterate through the todos array and print each todo
    for (const auto &todoValue : todosArray) {
        QJsonObject todoObject = todoValue.toObject();
        int todoId = todoObject.value("id").toInt();
        QString title = todoObject.value("title").toString();
        QString description = todoObject.value("description").toString();
        QString deadline = todoObject.value("deadline").toString();
        int toDoAuthorId = todoObject.value("l_id").toInt();
        bool done = todoObject.value("done").toBool();
        QString name = todoObject.value("name").toString();

        toDo *td = new toDo(todoId, title, description, deadline,toDoAuthorId,done,name);
        user::getInstance()->appendToDo(td);

        qDebug() << "Todo ID: " << todoId;
        qDebug() << "Title: " << title;
        qDebug() << "Description: " << description;
        qDebug() << "Deadline: " << deadline;
        qDebug() << "Location ID: " << toDoAuthorId;
        qDebug() << "done: " << done;
        qDebug() << "name: " << name;
        //qDebug() << "Names: " << names.join(", ");
    }

    QList<toDoComponent *> toDoComponentsList;


    user *currentUser = user::getInstance();
    toDosBoardWindow *mainWindow = toDosBoardWindow::getInstance();

    QList<toDo*> todos = currentUser->getToDos();

    // Iterate through the todos
    qDebug() << "User's Todos:";
    for (const toDo* todo : todos) { // Use a pointer here
        qDebug() << "u_Todo ID:" << todo->getId(); // Dereference the pointer to access members
        qDebug() << "u_Title:" << todo->getTitle();
        qDebug() << "u_Description:" << todo->getDescription();
        qDebug() << "u_Deadline:" << todo->getDeadline();
        // Add more fields as needed
        qDebug() << "------------------------";
    }
    for (auto todo : todos)
    {

        toDoComponent *component1 = new toDoComponent(todo);
        toDoComponentsList << component1;


    }
    mainWindow->addToDoComponents(toDoComponentsList);
    mainWindow->show();


}

void authenticationPageApi::getJuniorsData()
{
    QUrl juniorsUrl("https://lawyerassistant.up.railway.app/juniors");

    // Create a request
    QNetworkRequest request(juniorsUrl);
    request.setAttribute(QNetworkRequest::User, "getJuniorsData");

    // Perform the GET request
    QNetworkReply *reply = manager.get(request);
    reply->setProperty("requestType", "getJuniorsData");

    // Create an event loop to wait for the reply to finish
    QEventLoop loop;
    auto onFinished = [&]() {
        authenticationPageApi::onRequestFinished(reply);
        loop.quit();
    };

    QObject::connect(reply, &QNetworkReply::finished, onFinished);
    loop.exec();

    // Check for errors

}

void authenticationPageApi::parseJuniorsData(const QByteArray &responseData)
{
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray userArray = jsonObject["user"].toArray();
    QList<user*> juniorsList;

    for (const auto &userValue : userArray)
    {


        QJsonObject userObject = userValue.toObject();

        // Create a new user instance


        int id = userObject["id"].toInt();
        QString name = userObject["name"].toString();
        QString password = userObject["password"].toString();
        QString jobTitle = userObject["job_title"].toString();
        QString type = userObject["type"].toString();
        QString email = userObject["email"].toString();
        int supervisorId = userObject["sup_id"].toInt();

        user* newJunior = new user(id,name, password, jobTitle, type, email, supervisorId);
        juniorsList.append(newJunior);

        user::getInstance()->setJuniors(juniorsList);
    }

    // Iterate through the juniors list and print information
    qDebug() << "Iterating through juniors list:";
    for (user* junior : juniorsList) {
        qDebug() << "ID: " << junior->getId();
        qDebug() << "Name: " << junior->getName();
        qDebug() << "Job Title: " << junior->getJobTitle();
        qDebug() << "Email: " << junior->getEmail();
        qDebug() << "-------------------------";
    }
}

// Static slot to handle the reply when the request is finished

