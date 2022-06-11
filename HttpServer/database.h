#ifndef WEGAMEDATABASE_H
#define WEGAMEDATABASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileInfo>
#include <QDir>
#include <QUuid>
#include <QDebug>
class Database : public QObject
{
    Q_OBJECT
public:
    Database(QObject *parent = nullptr);
    ~Database();

public:

    // 查询部门
    QByteArray queryDepartment();
    // 账号是否存在
    bool isAccountExist(QString accountNumber);
    // 按账号密码查询信息
    QByteArray queryAllUserInformation(QString accountNumber,QString password);
    // 添加用户信息
    QByteArray addUserInformation(QString accountNumber,QString password,QString phoneNumber);
    // 修改个人信息
    QByteArray modifyInformation(QString accountNumber,QString name,QString mail,QString phoneNumber,QString departmentName);
    // 查询部门成员
    QByteArray queryDepartmentMembers(QString departmentName);
    // 添加部门
    QByteArray addDepartment(QString departmentName);
    // 删除成员
    QByteArray deleteMember(int accountNumber);

private:

    // 数据库连接
    QSqlQuery databaseConnection(QSqlDatabase db);

private:
    QSqlQuery *m_query;
private:
    QByteArray m_serverData;
    QJsonDocument m_doc;
};

#endif // WEGAMEDATABASE_H
