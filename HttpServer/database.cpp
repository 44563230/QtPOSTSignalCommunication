#include "database.h"

Database::Database(QObject *parent) : QObject(parent)
{
    QSqlDatabase db;
    databaseConnection(db);
    db.close();
}

QByteArray Database::queryDepartment()
{
    m_serverData.clear();
    QJsonObject m_jsonData;
    QSqlDatabase db;
    QSqlQuery query = databaseConnection(db);
    query.exec(QString("SELECT u_departmentid,u_departmentname FROM userdepartment"));
    while(query.next())
    {
        m_jsonData.insert("Departmentid",query.value("u_departmentid").toString());
        m_jsonData.insert("Departname",query.value("u_departmentname").toString());
        m_serverData.append(QJsonDocument(m_jsonData).toJson());
    }
    db.close();
    if ( m_jsonData["Departmentid"].toString() != nullptr)
    {
        return m_serverData;
    }
    return "0";
}

bool Database::isAccountExist(QString accountNumber)
{
    QSqlDatabase db;
    QSqlQuery query = databaseConnection(db);
    query.exec(QString("SELECT u_accountNumber,u_password FROM useraccount WHERE u_accountNumber = '%1'").replace("%1",accountNumber));
    if (query.next())
    {
        db.close();
        return false;
    }
    db.close();
    return true;
}

QByteArray Database::queryAllUserInformation(QString accountNumber,QString password)
{
    m_serverData.clear();
    QJsonObject m_jsonData;
    QSqlDatabase db;
    QSqlQuery query = databaseConnection(db);
    query.exec(QString("SELECT i.u_name,i.u_accountNumber,i.u_phonenumber,u_mail,d.u_departmentname FROM userinformation i,userdepartment d,useraccount c WHERE i.u_guid = c.u_guid AND i.u_departmentid = d.u_departmentid AND c.u_accountNumber = '%1' AND c.u_password = '%2'").replace("%1",accountNumber).replace("%2",password));
    while(query.next())
    {
        m_jsonData.insert("Nickname",query.value("u_name").toString());
        m_jsonData.insert("Account",query.value("u_accountNumber").toString());
        m_jsonData.insert("Phonenumber",query.value("u_phonenumber").toString());
        m_jsonData.insert("Mail",query.value("u_mail").toString());
        m_jsonData.insert("Departmentname",query.value("u_departmentname").toString());
        m_serverData.append(QJsonDocument(m_jsonData).toJson());
        if ( m_jsonData["Account"].toString() != nullptr )
        {
            db.close();
            return m_serverData;
        }
    }
    db.close();
    return "0";
}

QByteArray Database::addUserInformation(QString accountNumber,QString password,QString phoneNumber)
{
    QString id = QUuid::createUuid().toString();
    if (isAccountExist(accountNumber))
    {
        QSqlDatabase db;
        QSqlQuery query = databaseConnection(db);
        query.exec(QString("INSERT INTO useraccount (u_guid,u_accountNumber,u_password) VALUES ('%1','%2','%3')").replace("%1",id).replace("%2",accountNumber).replace("%3",password));
        query.exec(QString("INSERT INTO userinformation (u_guid,u_accountNumber,u_phonenumber,u_departmentid) VALUES ('%1','%2','%3',%4)").replace("%1",id).replace("%2",accountNumber).replace("%3",phoneNumber).replace("%4",QString::number(0)));
        db.close();
        return "1";
    }
    return "0";
}

QByteArray Database::modifyInformation(QString accountNumber,QString name,QString mail,QString phoneNumber,QString departmentName)
{
    QSqlDatabase db;
    QSqlQuery query = databaseConnection(db);
    query.exec(QString("UPDATE userinformation SET u_name = '%1' , u_mail = '%2' , u_phonenumber = '%3' , u_departmentId = (SELECT u_departmentId FROM userdepartment WHERE u_departmentname = '%4') WHERE u_accountNumber = '%5'").replace("%1",name).replace("%2",mail).replace("%3",phoneNumber).replace("%4",departmentName).replace("%5",accountNumber));
    db.close();
    return "1";
}

QByteArray Database::queryDepartmentMembers(QString departmentName)
{
    m_serverData.clear();
    QJsonObject m_jsonData;
    QSqlDatabase db;
    QSqlQuery query = databaseConnection(db);
    if (nullptr != departmentName)
    {
        query.exec(QString("SELECT i.u_accountNumber,i.u_name,i.u_phonenumber,i.u_mail,d.u_departmentname FROM userinformation i,userdepartment d WHERE i.u_departmentId = d.u_departmentid AND d.u_departmentname = '%1' ORDER BY i.u_accountNumber").replace("%1",departmentName));
    }
    else
    {
        query.exec(QString("SELECT i.u_accountNumber,i.u_name,i.u_phonenumber,i.u_mail,d.u_departmentname FROM userinformation i,userdepartment d WHERE i.u_departmentId = d.u_departmentid ORDER BY i.u_accountNumber"));
    }
    while(query.next())
    {
        m_jsonData.insert("accountNumber",query.value("u_accountNumber").toString());
        m_jsonData.insert("name",query.value("u_name").toString());
        m_jsonData.insert("phonenumber",query.value("u_phonenumber").toString());
        m_jsonData.insert("mail",query.value("u_mail").toString());
        m_jsonData.insert("departmentName",query.value("u_departmentname").toString());
        m_serverData.append(QJsonDocument(m_jsonData).toJson());
    }
    db.close();
    if ( m_jsonData["accountNumber"].toString() != nullptr)
    {
        return m_serverData;
    }
    return "0";
}

QByteArray Database::addDepartment(QString departmentName)
{
    QSqlDatabase db;
    QSqlQuery query = databaseConnection(db);
    query.exec(QString("SELECT u_departmentid FROM userdepartment WHERE u_departmentname = '%1'").replace("%1",departmentName));
    if (query.next())
    {
        db.close();
        return "0";
    }
    query.exec(QString("INSERT INTO userdepartment (u_departmentname) VALUES ('%1')").replace("%1",departmentName));
    db.close();
    return "1";
}

QByteArray Database::deleteMember(int accountNumber)
{
    QSqlDatabase db;
    QSqlQuery query = databaseConnection(db);
    query.exec(QString("DELETE FROM userinformation WHERE u_accountNumber = %1").replace("%1",QString::number(accountNumber)));
    query.exec(QString("DELETE FROM useraccount WHERE u_accountNumber = %1").replace("%1",QString::number(accountNumber)));
    return "1";
}

QSqlQuery Database::databaseConnection(QSqlDatabase db)
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }

    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("wegameuser");
    db.setUserName("root");
    db.setPassword("root");
    QFileInfo fi("database.db");
    QSqlQuery query(db);

    if (!fi.isDir())
    {
        db.setDatabaseName("database.db");
        if(db.open() == false)
        {
            qDebug() << db.lastError().text(); //打印失败原因
            qDebug() << "连接失败";
        }
        else
        {
            query.exec("CREATE TABLE 'userinformation' ('u_guid' text NOT NULL,'u_accountNumber' TEXT NOT NULL,'u_name' TEXT,'u_phonenumber' INTEGER(11) NOT NULL,'u_mail' TEXT,'u_departmentId' INTEGER NOT NULL,CONSTRAINT 'fk_information_guid' FOREIGN KEY ('u_guid') REFERENCES 'useraccount' ('u_guid') ON DELETE NO ACTION ON UPDATE NO ACTION,CONSTRAINT 'fk_information_departmentId' FOREIGN KEY ('u_departmentId') REFERENCES 'userdepartment' ('u_departmentid') ON DELETE NO ACTION ON UPDATE NO ACTION)");
            query.exec("CREATE TABLE 'useraccount' ('u_guid' TEXT NOT NULL,'u_accountNumber' TEXT NOT NULL,'u_password' TEXT(32) NOT NULL,PRIMARY KEY ('u_guid'))");
            query.exec("CREATE TABLE 'userdepartment' ('u_departmentid' INTEGER NOT NULL,'u_departmentname' TEXT,PRIMARY KEY ('u_departmentid'))");
            //            query.exec("CREATE TABLE 'userinformation' ('u_guid' text NOT NULL,'u_accountNumber' INTEGER(15) NOT NULL,'u_name' TEXT NOT NULL,'u_phonenumber' integer NOT NULL,'u_mail' TEXT NOT NULL,'u_departmentId' INTEGER,CONSTRAINT 'fk_information_guid' FOREIGN KEY ('u_guid') REFERENCES 'useraccount' ('u_guid') ON DELETE NO ACTION ON UPDATE NO ACTION,CONSTRAINT 'fk_information_departmentId' FOREIGN KEY ('u_departmentId') REFERENCES 'userdepartment' ('u_departmentid') ON DELETE NO ACTION ON UPDATE NO ACTION)");
            query.exec("INSERT INTO 'userdepartment' VALUES (0, '无小组')");
        }
    }

    return query;
}

Database::~Database()
{

}
