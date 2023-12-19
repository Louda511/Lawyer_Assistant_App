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
    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        authenticationPageApi::onLoginFinished(reply);
        loop.quit();
    });

    // Synchronously wait for the reply to finish
    loop.exec();

    // Cleanup
    reply->deleteLater();
}

// Static slot to handle the reply when the login request is finished
void authenticationPageApi::onLoginFinished(QNetworkReply *reply) {
    // Check for errors
    if (reply->error() == QNetworkReply::NoError) {
        // Request was successful
        qDebug() << "Connection established successfully!";
        qDebug() << "Response:" << reply->readChannelCount();
    } else {
        // Handle error
        qDebug() << "Error:" << reply->errorString();
    }
}
