#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QtNetwork>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include "database.h"

class HttpServer : public QObject
{
    Q_OBJECT

public:

    explicit HttpServer(QObject *parent = nullptr);
    ~HttpServer();

public:

    // 运行服务器
    void turnOnTheServer(const QHostAddress &address = QHostAddress::Any,const quint16 &port = 80,QString serverAccount = nullptr,QString serverPassword = nullptr);
    // 管理员账号密码
    bool administrators(QString serverAccount,QString administratorPassword);
    // 关闭服务器
    void shutDownTheServer();

private slots:

    void newConnection();
    void readyRead();

private:
    // 解析数据
    QByteArray parseData(QString request);
    // 发送Http数据
    void sendHttpData(QByteArray data,QTcpSocket *socket);

private:
    QTcpServer *m_httpServer;
    Database *m_Database;
private:
    QByteArray m_data;
    QString m_serverAccount;
    QString m_serverPassword;

    QString m_administratorAccountNumber;
    QString m_administratorPassword;
};

#endif // MAINWINDOW_H
