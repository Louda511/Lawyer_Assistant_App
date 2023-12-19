#ifndef AUTHENTICATIONPAGEAPI_H
#define AUTHENTICATIONPAGEAPI_H

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QEventLoop>
#include <QDebug>


class authenticationPageApi : public QObject {
    Q_OBJECT

public:
    // Static function to perform a login POST request
    static void performLogin(const QString &email, const QString &password);


private slots:
    // Static slot to handle the reply when the login request is finished
    static void onLoginFinished(QNetworkReply *reply);

private:
    // Private member to hold the network manager
    static QNetworkAccessManager manager;
};


#endif // AUTHENTICATIONPAGEAPI_H
