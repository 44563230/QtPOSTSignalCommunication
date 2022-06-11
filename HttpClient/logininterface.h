#ifndef LOGININTERFACE_H
#define LOGININTERFACE_H

#include <QWidget>
#include <QObject>
#include <QPushButton>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCheckBox>
#include <QSettings>
#include <QTimer>
#include "httpclient.h"
#include "serverexception.h"

class LoginInterface : public QWidget
{
    Q_OBJECT
public:
    LoginInterface(QWidget *parent = nullptr);
    ~LoginInterface();

public:

    void setUserNameText(QString userName);

signals:

    // 切换注册界面
    void SwitchRegistration();

    // 切换主界面
    void SwitchInformation(QString data);

private slots:

    // 记住密码
    bool rememberThePassword(int state);

    // 自动登录
    bool autoLogSlots(int state);

    // 自动登录状态
    void autoLoginStatus();

    // 登录
    void loginButtonClicked();

    // 注册界面
    void registrationInterfaceClicked();

private:

    // 显示界面
    void displayLoginInterface();

    // 读取本地登录信息
    void readAccount();

    // 保存登录信息
    void saveLoginInformation();

private:
    HttpClient *m_HttpClient;
    ServerException *m_ServerException;
private:
    QPushButton *m_loginLeftBackgroundPicture;
    QPushButton *m_loginRightBackgroundPicture;

    QLineEdit *m_accountNumberText;
    QLineEdit *m_passwordText;
    QCheckBox *m_isRememberThePassword;
    QCheckBox *m_isAutomaticLogon;

    QLabel *m_errorPrompt;

    QPushButton *m_loginButton;
    QPushButton *m_registrationButton;

    QRegExpValidator *m_userNameValidator;
    QRegExpValidator *m_passwordValidator;
private:
    QString m_clientData;
    QJsonDocument m_doc;
    QJsonObject m_jsonData;
};

#endif // LOGININTERFACE_H
