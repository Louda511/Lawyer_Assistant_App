#include "authenticationpageapi.h"

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
    reply->deleteLater();
}

// Static slot to handle the reply when the request is finished
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
