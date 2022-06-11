#include "httpclient.h"

HttpClient::HttpClient()
{
    m_manager = new QNetworkAccessManager(this);
    m_request = new QNetworkRequest();
    m_serverAccount = nullptr;
    m_serverPassword = nullptr;
    m_serverIP = "http://127.0.0.1";
}

QByteArray HttpClient::query(QJsonObject jsonContent)
{
    QByteArray queryErrorResult;
    queryErrorResult.clear();
    QByteArray postData;
    jsonContent.insert("serverAccount",m_serverAccount);
    jsonContent.insert("serverPassword",m_serverPassword);
    qDebug() << "发送: " << jsonContent;
    postData.append(QJsonDocument(jsonContent).toJson());
    m_request->setUrl(QUrl(m_serverIP));
    m_request->setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));

    m_reply = m_manager->post(*m_request, postData);

    QEventLoop eventLoop;
    connect(m_reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    QByteArray responseByte = m_reply->readAll();
    qDebug() << "读取：" << QString(responseByte);
    m_reply->deleteLater();
    m_reply = nullptr;

    return responseByte;
}

HttpClient::~HttpClient()
{

}
