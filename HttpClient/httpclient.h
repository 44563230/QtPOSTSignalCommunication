#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTextBrowser>
#include <QEventLoop>
#include <QJsonObject>
#include <QJsonDocument>

class HttpClient : public QObject
{
    Q_OBJECT

public:
    HttpClient();
    ~HttpClient();

public:

    // 发送POST请求并接收数据
    QByteArray query(QJsonObject jsonContent);

private:
    QNetworkAccessManager *m_manager;
    QNetworkReply *m_reply;
    QNetworkRequest *m_request;
private:
    QString m_serverAccount;
    QString m_serverPassword;
    QString m_serverIP;
};
#endif // HTTPCLIENT_H
