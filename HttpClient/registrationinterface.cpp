#include "registrationinterface.h"

RegistrationInterface::RegistrationInterface(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("用户注册");
    this->setFixedSize(866,486);
    displayRegistrationInterface();
}

void RegistrationInterface::displayRegistrationInterface()
{
    m_HttpClient = new HttpClient();
    m_ServerException = new ServerException();

    m_loginLeftBackgroundPicture = new QPushButton(this);
    m_loginLeftBackgroundPicture->setGeometry(0,0,593,486);
    m_loginLeftBackgroundPicture->setStyleSheet("image:url(:/image/LoginBackgroundPicture.png)");
    m_loginRightBackgroundPicture = new QPushButton(this);
    m_loginRightBackgroundPicture->setGeometry(590,0,276,486);
    m_loginRightBackgroundPicture->setStyleSheet("background-color: Goldenrod");
    m_loginRightBackgroundPicture->setEnabled(false);
    //    m_loginRightBackgroundPicture->setDisabled(true);


    QRegExp userName = QRegExp("^[A-Za-z0-9]+$");
    m_userNameValidator = new QRegExpValidator(userName);
    m_registeredAccountText = new QLineEdit(this);
    m_registeredAccountText->setGeometry(630,180,195,30);
    m_registeredAccountText->setPlaceholderText("请输入注册账号");
    m_registeredAccountText->setValidator(m_userNameValidator);
    m_registeredAccountText->setMaxLength(10);
    m_registeredAccountText->setStyleSheet("QLineEdit{border: 1px solid gray;border-radius: 4px;padding: 0 8px;background: white;selection-background-color: darkgray; }QListView{background-color: white;background-image: url(draft.png);background-attachment: fixed;}QLineEdit[echoMode='2']{lineedit-password-character: 9679;}QLineEdit:read-only{background: lightblue;}");

    QRegExp password = QRegExp("^[A-Za-z0-9]+$");
    m_passwordValidator = new QRegExpValidator(password);
    m_registrationPasswordText = new QLineEdit(this);
    m_registrationPasswordText->setGeometry(630,220,195,30);
    m_registrationPasswordText->setPlaceholderText("请输入注册密码");
    m_registrationPasswordText->setValidator(m_passwordValidator);
    m_registrationPasswordText->setEchoMode(QLineEdit::Password);
    m_registrationPasswordText->setMaxLength(16);
    m_registrationPasswordText->setStyleSheet("QLineEdit{border: 1px solid gray;border-radius: 4px;padding: 0 8px;background: white;selection-background-color: darkgray; }QListView{background-color: white;background-image: url(draft.png);background-attachment: fixed;}QLineEdit[echoMode='2']{lineedit-password-character: 9679;}QLineEdit:read-only{background: lightblue;}");

//    m_registerDepartment = new QComboBox(this);
//    m_registerDepartment->setGeometry(630,220,195,30);

    QRegExp phone = QRegExp("^1([358][0-9]|4[579]|66|7[0135678]|9[89])[0-9]{8}$");
    m_phoneValidator = new QRegExpValidator(phone);
    m_registerPhoneText = new QLineEdit(this);
    m_registerPhoneText->setGeometry(630,260,195,30);
    m_registerPhoneText->setPlaceholderText("请输入注册手机号");
    m_registerPhoneText->setValidator(m_phoneValidator);
    m_registerPhoneText->setMaxLength(11);
    m_registerPhoneText->setStyleSheet("QLineEdit{border: 1px solid gray;border-radius: 4px;padding: 0 8px;background: white;selection-background-color: darkgray; }QListView{background-color: white;background-image: url(draft.png);background-attachment: fixed;}QLineEdit[echoMode='2']{lineedit-password-character: 9679;}QLineEdit:read-only{background: lightblue;}");

    m_errorPrompt = new QLabel(this);
    m_errorPrompt->setGeometry(630,340,195,30);
    m_errorPrompt->setStyleSheet("color:red;");

    m_signInButton = new QPushButton(this);
    m_signInButton->setText("注  册");
    m_signInButton->setGeometry(629,366,197,36);
    m_signInButton->setStyleSheet("QPushButton{font: 10pt '微软雅黑';color: #2f3640;background-color: #f5f6fa;border-color: #2f3640;border-radius: 15px;border-style: solid;border-width: 2px;padding: 5px;}QPushButton::hover{color: #FFFFFF;background-color: #718093;border-color: #2f3640;}QPushButton::pressed,QPushButton::checked{color: #FFFFFF;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);}QPushButton::disabled{color: #7B68EE;background-color: #dcdde1;border-color: #dcdde1;}");
    connect(m_signInButton,&QPushButton::clicked,this,&RegistrationInterface::signInButtonClicked);

    m_returnButton = new QPushButton(this);
    m_returnButton->setText("返  回");
    m_returnButton->setGeometry(629,412,197,36);
    m_returnButton->setStyleSheet("QPushButton{font: 10pt '微软雅黑';color: #2f3640;background-color: #f5f6fa;border-color: #2f3640;border-radius: 15px;border-style: solid;border-width: 2px;padding: 5px;}QPushButton::hover{color: #FFFFFF;background-color: #718093;border-color: #2f3640;}QPushButton::pressed,QPushButton::checked{color: #FFFFFF;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);}QPushButton::disabled{color: #7B68EE;background-color: #dcdde1;border-color: #dcdde1;}");
    connect(m_returnButton,&QPushButton::clicked,this,&RegistrationInterface::returnButtonClicked);
}

void RegistrationInterface::signInButtonClicked()
{
    m_errorPrompt->setText(nullptr);
    switch (m_registeredAccountText->text() != nullptr && m_registrationPasswordText->text() != nullptr && m_registerPhoneText->text() != nullptr && m_registerPhoneText->text().length() == 11)
    {
    case false:
        if (m_registeredAccountText->text() == nullptr)
        {
            m_errorPrompt->setText("账号不允许为空！");
            break;
        }
        if (m_registrationPasswordText->text() == nullptr)
        {
            m_errorPrompt->setText("密码不允许为空！");
            break;
        }
        if (m_registerPhoneText->text() == nullptr)
        {
            m_errorPrompt->setText("手机号不允许为空！");
            break;
        }
        if (m_registerPhoneText->text().size() != 11)
        {
            m_errorPrompt->setText("China手机号长度错误！");
            break;
        }
        break;
    case true:
        m_signInButton->setEnabled(false);
        QJsonObject m_jsonData;
        m_jsonData.insert("accessDatabaseStatus","Register");
        m_jsonData.insert("registeredAccount",m_registeredAccountText->text());
        QByteArray ba_md5 = QCryptographicHash::hash(m_registrationPasswordText->text().toLocal8Bit(),QCryptographicHash::Md5);
        m_jsonData.insert("registrationPassword",QString(ba_md5.toHex().toUpper()));
        m_jsonData.insert("registerPhoneNumber",m_registerPhoneText->text());
        m_clientData = m_HttpClient->query(m_jsonData);

        if (nullptr == m_clientData)
        {
            m_ServerException->setVisible(true);
        }
        else if (m_clientData.contains("1",Qt::CaseSensitive))
        {
            m_errorPrompt->setText("注册成功！");
            m_ServerException->setVisible(false);

            m_registrationPasswordText->setText(nullptr);
            m_registerPhoneText->setText(nullptr);
            m_errorPrompt->setText(nullptr);
            emit SwitchLoginInterface(m_registeredAccountText->text());
            m_registeredAccountText->setText(nullptr);
        }
        else if (m_clientData.contains("0",Qt::CaseSensitive))
        {
            m_errorPrompt->setText("账号已存在！");
            m_ServerException->setVisible(false);
        }
        else
        {
            m_errorPrompt->setText("未知错误！");
            m_ServerException->setVisible(false);
        }
        m_signInButton->setEnabled(true);
        break;
    }
}

void RegistrationInterface::returnButtonClicked()
{
    m_registeredAccountText->setText(nullptr);
    m_registrationPasswordText->setText(nullptr);
    m_registerPhoneText->setText(nullptr);
    m_errorPrompt->setText(nullptr);
    emit SwitchLoginInterface(nullptr);
}

RegistrationInterface::~RegistrationInterface()
{

}
