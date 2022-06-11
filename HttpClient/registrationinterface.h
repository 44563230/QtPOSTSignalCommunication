#ifndef REGISTRATIONINTERFACE_H
#define REGISTRATIONINTERFACE_H

#include <QWidget>
#include <QObject>
#include <QPushButton>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QComboBox>
#include "httpclient.h"
#include "serverexception.h"

class RegistrationInterface : public QWidget
{
    Q_OBJECT
public:

    RegistrationInterface(QWidget *parent = nullptr);
    ~RegistrationInterface();

signals:

    // 切换登录界面
    void SwitchLoginInterface(QString data);

private slots:

    // 注册按钮
    void signInButtonClicked();
    // 返回按钮事件
    void returnButtonClicked();

private:

    // 显示注册界面
    void displayRegistrationInterface();

private:
    HttpClient *m_HttpClient;
    ServerException *m_ServerException;
private:
    QPushButton *m_registrationButton;
    QPushButton *m_loginLeftBackgroundPicture;
    QPushButton *m_loginRightBackgroundPicture;

    QLineEdit *m_registeredAccountText;
    QLineEdit *m_registrationPasswordText;
    QLineEdit *m_registerPhoneText;

    QLabel *m_errorPrompt;

    QPushButton *m_signInButton;
    QPushButton *m_returnButton;

    QRegExpValidator *m_userNameValidator;
    QRegExpValidator *m_passwordValidator;
    QRegExpValidator *m_phoneValidator;
private:
    QString m_clientData;
    QJsonDocument m_doc;
};

#endif // REGISTRATIONINTERFACE_H
