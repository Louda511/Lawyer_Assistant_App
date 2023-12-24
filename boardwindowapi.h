#ifndef BOARDWINDOWAPI_H
#define BOARDWINDOWAPI_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QObject>
#include <todo.h>
#include <todocomponent.h>
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class boardWindowApi : public QObject
{
    Q_OBJECT
public:
    boardWindowApi(QObject *parent = nullptr);
    ~boardWindowApi();
    static boardWindowApi* getInstance();
    void postToDo(const QString &title, const QString &description, const QString &deadline, int juniorId);



private slots:
    void handleReply(QNetworkReply *reply);


private:
    static boardWindowApi *instance;
    QNetworkAccessManager *manager;



};

#endif // BOARDWINDOWAPI_H
