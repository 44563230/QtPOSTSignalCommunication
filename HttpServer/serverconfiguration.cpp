#include "serverconfiguration.h"

ServerConfiguration::ServerConfiguration(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(300,350);
    this->setWindowTitle("服务器配置");
    displayConfigurationInterface();
    ServerConfiguration::turnOnTheServerClicked();
}

void ServerConfiguration::displayConfigurationInterface()
{
    m_httpServer = new HttpServer();

    m_administratorAccountNumberText = new QLineEdit(this);
    m_administratorAccountNumberText->setGeometry(50,150,200,30);
    m_administratorAccountNumberText->setPlaceholderText("请输入管理员账号");
    m_administratorAccountNumberText->setText("admin");
    m_administratorAccountNumberText->setStyleSheet("QLineEdit{border: 1px solid gray;border-radius: 4px;padding: 0 8px;background: white;selection-background-color: darkgray; }QListView{background-color: white;background-image: url(draft.png);background-attachment: fixed;}QLineEdit[echoMode='2']{lineedit-password-character: 9679;}QLineEdit:read-only{background: lightblue;}");

    m_administratorPasswordText = new QLineEdit(this);
    m_administratorPasswordText->setGeometry(50,200,200,30);
    m_administratorPasswordText->setPlaceholderText("请输入管理员密码");
    m_administratorPasswordText->setStyleSheet("QLineEdit{border: 1px solid gray;border-radius: 4px;padding: 0 8px;background: white;selection-background-color: darkgray; }QListView{background-color: white;background-image: url(draft.png);background-attachment: fixed;}QLineEdit[echoMode='2']{lineedit-password-character: 9679;}QLineEdit:read-only{background: lightblue;}");

    m_setAdministratorAccountButton = new QPushButton(this);
    m_setAdministratorAccountButton->setText("设置管理员");
    m_setAdministratorAccountButton->setGeometry(50,250,200,30);
    m_setAdministratorAccountButton->setStyleSheet("QPushButton{font: 10pt '微软雅黑';color: #2f3640;background-color: #f5f6fa;border-color: #2f3640;border-radius: 15px;border-style: solid;border-width: 2px;padding: 5px;}QPushButton::hover{color: #FFFFFF;background-color: #718093;border-color: #2f3640;}QPushButton::pressed,QPushButton::checked{color: #FFFFFF;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);}QPushButton::disabled{color: #7B68EE;background-color: #dcdde1;border-color: #dcdde1;}");
    connect(m_setAdministratorAccountButton,&QPushButton::clicked,this,&ServerConfiguration::setAdministratorAccountClicked);

    m_closeAdministratorAccountButton = new QPushButton(this);
    m_closeAdministratorAccountButton->setText("关闭管理员");
    m_closeAdministratorAccountButton->setGeometry(50,250,200,30);
    m_closeAdministratorAccountButton->setStyleSheet("QPushButton{font: 10pt '微软雅黑';color: #2f3640;background-color: #f5f6fa;border-color: #2f3640;border-radius: 15px;border-style: solid;border-width: 2px;padding: 5px;}QPushButton::hover{color: #FFFFFF;background-color: #718093;border-color: #2f3640;}QPushButton::pressed,QPushButton::checked{color: #FFFFFF;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);}QPushButton::disabled{color: #7B68EE;background-color: #dcdde1;border-color: #dcdde1;}");
    connect(m_closeAdministratorAccountButton,&QPushButton::clicked,this,&ServerConfiguration::closeAdministratorAccountClicked);
    m_closeAdministratorAccountButton->setVisible(false);

    m_turnOnTheServerButton = new QPushButton(this);
    m_turnOnTheServerButton->setText("开启服务器");
    m_turnOnTheServerButton->setGeometry(50,300,200,30);
    m_turnOnTheServerButton->setStyleSheet("QPushButton{font: 10pt '微软雅黑';color: #2f3640;background-color: #f5f6fa;border-color: #2f3640;border-radius: 15px;border-style: solid;border-width: 2px;padding: 5px;}QPushButton::hover{color: #FFFFFF;background-color: #718093;border-color: #2f3640;}QPushButton::pressed,QPushButton::checked{color: #FFFFFF;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);}QPushButton::disabled{color: #7B68EE;background-color: #dcdde1;border-color: #dcdde1;}");
    connect(m_turnOnTheServerButton,&QPushButton::clicked,this,&ServerConfiguration::turnOnTheServerClicked);

    m_shutDownTheServerButton = new QPushButton(this);
    m_shutDownTheServerButton->setText("关闭服务器");
    m_shutDownTheServerButton->setGeometry(50,300,200,30);
    m_shutDownTheServerButton->setStyleSheet("QPushButton{font: 10pt '微软雅黑';color: #2f3640;background-color: #f5f6fa;border-color: #2f3640;border-radius: 15px;border-style: solid;border-width: 2px;padding: 5px;}QPushButton::hover{color: #FFFFFF;background-color: #718093;border-color: #2f3640;}QPushButton::pressed,QPushButton::checked{color: #FFFFFF;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);}QPushButton::disabled{color: #7B68EE;background-color: #dcdde1;border-color: #dcdde1;}");
    connect(m_shutDownTheServerButton,&QPushButton::clicked,this,&ServerConfiguration::shutDownTheServerClicked);
    m_shutDownTheServerButton->setVisible(false);
}

void ServerConfiguration::setAdministratorAccountClicked()
{
    QByteArray ba_md5 = QCryptographicHash::hash(m_administratorPasswordText->text().toLocal8Bit(),QCryptographicHash::Md5);
    if (m_httpServer->administrators(m_administratorAccountNumberText->text(),QString(ba_md5.toHex().toUpper())))
    {
        m_administratorPasswordText->setEnabled(false);
        m_administratorAccountNumberText->setEnabled(false);
        m_setAdministratorAccountButton->setVisible(false);
        m_closeAdministratorAccountButton->setVisible(true);
    }
}

void ServerConfiguration::closeAdministratorAccountClicked()
{
    m_httpServer->administrators(nullptr,nullptr);
    m_administratorPasswordText->setEnabled(true);
    m_administratorAccountNumberText->setEnabled(true);
    m_setAdministratorAccountButton->setVisible(true);
    m_closeAdministratorAccountButton->setVisible(false);
}

void ServerConfiguration::turnOnTheServerClicked()
{
    m_httpServer->turnOnTheServer();

    m_shutDownTheServerButton->setVisible(true);
    m_turnOnTheServerButton->setVisible(false);
}

void ServerConfiguration::shutDownTheServerClicked()
{
    m_httpServer->shutDownTheServer();

    m_shutDownTheServerButton->setVisible(false);
    m_turnOnTheServerButton->setVisible(true);
}

ServerConfiguration::~ServerConfiguration()
{

}
