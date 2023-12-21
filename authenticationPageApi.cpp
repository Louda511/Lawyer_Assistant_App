#include "authenticationpageapi.h"
#include "user.h"

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
        qDebug() << "Connection established successfully!";
        qDebug() << "Response:" << reply->readAll();

        // Retrieve information from the request object
        QString requestType = reply->request().attribute(QNetworkRequest::User).toString();


        // Determine if the reply is from performLogin or performSignUp
        if (requestType == "login") {
            // This is the response from performLogin
            qDebug() << "Response from performLogin";
            //QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
            //QJsonObject responseData = jsonResponse.object();
            //emit readResponseData(responseData);

        } else if (requestType == "signup") {
            // This is the response from performSignUp
            qDebug() << "Response from performSignUp";
        } else {
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

// Static slot to handle the reply when the request is finished

