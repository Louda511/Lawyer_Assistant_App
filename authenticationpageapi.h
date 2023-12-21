#ifndef AUTHENTICATIONPAGEAPI_H
#define AUTHENTICATIONPAGEAPI_H

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QEventLoop>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include "user.h"
#include "toDo.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>



class authenticationPageApi : public QObject {
    Q_OBJECT

public:


    // Static function to perform a login POST request
    static void performLogin(const QString &email, const QString &password);

    // Static function to perform a sign-up (register) POST request
    static void performSignUp(const QString &name, const QString &email,
                              const QString &password, const QString &jobTitle,
                              const QString &type, const QString &supEmail);


private slots:
    // Static slot to handle the reply when the request is finished
    static void onRequestFinished(QNetworkReply *reply);

private:
    // Private member to hold the network manager
    static QNetworkAccessManager manager;
};

#endif // AUTHENTICATIONPAGEAPI_H
