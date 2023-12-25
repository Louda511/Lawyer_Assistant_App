#include "boardwindowapi.h"
#include "todosboardwindow.h"


boardWindowApi* boardWindowApi::instance = nullptr;

boardWindowApi* boardWindowApi::getInstance() {
    // Create the instance if it doesn't exist yet
    if (instance == nullptr) {
        instance = new boardWindowApi();
    }
    return instance;
}

boardWindowApi::boardWindowApi(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
}

void boardWindowApi::postToDo(const QString &title, const QString &description, const QString &deadline, int juniorId)
{
    QUrl url("https://lawyerassistant.up.railway.app/create");

    QJsonObject data;
    data["title"] = title;
    data["description"] = description;
    data["deadline"] = deadline;
    data["junior_id"] = juniorId;

    QByteArray jsonData = QJsonDocument(data).toJson();

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    connect(manager, &QNetworkAccessManager::finished, this, &boardWindowApi::handleReply);

    manager->post(request, jsonData);
}

void boardWindowApi::handleReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        qDebug() << "Response Body:" << responseData;
    } else {
        qDebug() << "Error:" << reply->errorString();
        qDebug() << "Server Response:" << reply->readAll();

    }

    reply->deleteLater();
}




boardWindowApi::~boardWindowApi()
{
    disconnect(manager, &QNetworkAccessManager::finished, this, &boardWindowApi::handleReply);
    // Other cleanup code if needed
}

