#include "httpserver.h"

HttpServer::HttpServer(QObject *parent) : QObject(parent)
{
    m_httpServer = new QTcpServer(this);
    m_httpServer->setMaxPendingConnections(1024);
    connect(m_httpServer,&QTcpServer::newConnection,this,&HttpServer::newConnection);
    m_Database = new Database();
}

bool HttpServer::administrators(QString serverAccount,QString administratorPassword)
{
    if (m_Database->isAccountExist(serverAccount))
    {
        m_administratorAccountNumber = serverAccount;
        m_administratorPassword = administratorPassword;
        return true;
    }
    return false;
}

void HttpServer::turnOnTheServer(const QHostAddress &address, const quint16 &port,QString serverAccount,QString serverPassword)
{
    if (nullptr == m_httpServer)
    {
        m_httpServer = new QTcpServer(this);
        m_httpServer->setMaxPendingConnections(1024);
        connect(m_httpServer,&QTcpServer::newConnection,this,&HttpServer::newConnection);
    }
    m_httpServer->listen(address,port);
    m_serverAccount = serverAccount;
    m_serverPassword = serverPassword;
}

void HttpServer::shutDownTheServer()
{
    if (nullptr != m_httpServer)
    {
        delete m_httpServer;
        m_httpServer = nullptr;
    }
}

void HttpServer::newConnection()
{
    QTcpSocket *m_socket = m_httpServer->nextPendingConnection();
    QObject::connect(m_socket,&QTcpSocket::readyRead,this,&HttpServer::readyRead);
}

void HttpServer::readyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if(socket)
    {
        QByteArray request = socket->readAll();
        QStringList list = QString(request).split("User-Agent: Mozilla/5.0\r\n\r\n");

        if (list.size() > 1)
        {
            QJsonDocument doc = QJsonDocument::fromJson(list[1].toUtf8());
            QJsonObject jsonData = doc.object();
            if (jsonData["serverAccount"].toString() == m_serverAccount && jsonData["serverPassword"].toString() == m_serverPassword)
            {
                m_data = parseData(list[1]);
            }
        }
        else
        {
            QJsonDocument doc = QJsonDocument::fromJson(QString(request).toUtf8());
            QJsonObject jsonData = doc.object();
            if (jsonData["serverAccount"].toString() == m_serverAccount && jsonData["serverPassword"].toString() == m_serverPassword)
            {
                m_data = parseData(request);
            }
        }
        sendHttpData(m_data,socket);
    }
}

QByteArray HttpServer::parseData(QString request)
{
    qDebug() << "接收：" << request;
    QJsonDocument doc = QJsonDocument::fromJson(QString(request).toUtf8());
    QJsonObject jsonData = doc.object();

    if (jsonData["accessDatabaseStatus"].toString() == "Login")
    {
        if (jsonData["accountNumber"].toString() == m_administratorAccountNumber && jsonData["password"].toString() == m_administratorPassword)
        {
            return "admin";
        }
        QByteArray data = m_Database->queryAllUserInformation(jsonData["accountNumber"].toString(),jsonData["password"].toString());
        return data;
    }
    else if (jsonData["accessDatabaseStatus"].toString() == "Register")
    {
        QByteArray data = m_Database->addUserInformation(jsonData["registeredAccount"].toString(),jsonData["registrationPassword"].toString(),jsonData["registerPhoneNumber"].toString());
        return data;
    }
    else if (jsonData["accessDatabaseStatus"].toString() == "ModifyInformation")
    {
        QByteArray data = m_Database->modifyInformation(jsonData["modifyAccount"].toString(),jsonData["modifyNickname"].toString(),jsonData["modifyMailbox"].toString(),jsonData["modifyPhoneNumber"].toString(),jsonData["modifyDepartmentName"].toString());
        return data;
    }
    else if (jsonData["accessDatabaseStatus"].toString() == "QueryDepartment")
    {
        QByteArray data = m_Database->queryDepartment();
        return data;
    }
    else if (jsonData["accessDatabaseStatus"].toString() == "QueryMembers")
    {
        QByteArray data = m_Database->queryDepartmentMembers(jsonData["QueryMembers"].toString());
        return data;
    }
    else if (jsonData["accessDatabaseStatus"].toString() == "AddDepartment")
    {
        QByteArray data = m_Database->addDepartment(jsonData["AddDepartment"].toString());
        return data;
    }
    else if (jsonData["accessDatabaseStatus"].toString() == "DeleteMember")
    {
        QByteArray data = m_Database->deleteMember(jsonData["DeleteMember"].toString().toInt());
        return data;
    }
    return nullptr;
}

void HttpServer::sendHttpData(QByteArray response,QTcpSocket *socket)
{
    if (nullptr != response)
    {
        QString http = "HTTP/1.1 200 OK\r\n";
        http += "Server: nginx\r\n";
        http += "Content-Type: text/html;charset=utf-8\r\n";
        http += "Connection: keep-alive\r\n";
        http += QString("Content-Length: %1\r\n\r\n").arg(QString::number(response.size()));

        socket->write(http.toUtf8());
        socket->write(response);
        socket->flush();
        socket->waitForBytesWritten(http.size() + response.size());
        socket->close();
    }
}

HttpServer::~HttpServer()
{
    if (nullptr != m_httpServer)
    {
        delete m_httpServer;
        m_httpServer = nullptr;
    }
}
