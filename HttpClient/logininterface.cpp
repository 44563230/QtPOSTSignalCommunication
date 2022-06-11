#include "logininterface.h"

LoginInterface::LoginInterface(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("用户登录");
    this->setFixedSize(866,486);
    displayLoginInterface();
    readAccount();
}
void LoginInterface::displayLoginInterface()
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
    m_accountNumberText = new QLineEdit(this);
    m_accountNumberText->setGeometry(630,228,195,30);
    m_accountNumberText->setPlaceholderText("请输入账号");
    m_accountNumberText->setValidator(m_userNameValidator);
    m_accountNumberText->setMaxLength(10);
    m_accountNumberText->setStyleSheet("QLineEdit{border: 1px solid gray;border-radius: 4px;padding: 0 8px;background: white;selection-background-color: darkgray; }QListView{background-color: white;background-image: url(draft.png);background-attachment: fixed;}QLineEdit[echoMode='2']{lineedit-password-character: 9679;}QLineEdit:read-only{background: lightblue;}");

    QRegExp password = QRegExp("^[A-Za-z0-9]+$");
    m_passwordValidator = new QRegExpValidator(password);
    m_passwordText = new QLineEdit(this);
    m_passwordText->setGeometry(630,268,195,30);
    m_passwordText->setPlaceholderText("请输入密码");
    m_passwordText->setValidator(m_passwordValidator);
    m_passwordText->setEchoMode(QLineEdit::Password);
    m_passwordText->setMaxLength(16);
    m_passwordText->setStyleSheet("QLineEdit{border: 1px solid gray;border-radius: 4px;padding: 0 8px;background: white;selection-background-color: darkgray; }QListView{background-color: white;background-image: url(draft.png);background-attachment: fixed;}QLineEdit[echoMode='2']{lineedit-password-character: 9679;}QLineEdit:read-only{background: lightblue;}");

    m_isRememberThePassword = new QCheckBox(this);
    m_isRememberThePassword->setGeometry(630,308,195,30);
    m_isRememberThePassword->setText("记住密码");
    m_isRememberThePassword->setStyleSheet("");
    connect(m_isRememberThePassword,&QCheckBox::stateChanged,this,&LoginInterface::rememberThePassword);

    m_isAutomaticLogon = new QCheckBox(this);
    m_isAutomaticLogon->setGeometry(755,308,195,30);
    m_isAutomaticLogon->setText("自动登录");
    connect(m_isAutomaticLogon,&QCheckBox::stateChanged,this,&LoginInterface::autoLogSlots);

    m_errorPrompt = new QLabel(this);
    m_errorPrompt->setGeometry(630,340,195,30);
    m_errorPrompt->setStyleSheet("color:red;");

    m_loginButton = new QPushButton(this);
    m_loginButton->setText("登  录");
    m_loginButton->setGeometry(629,366,197,36);
    m_loginButton->setStyleSheet("QPushButton{font: 10pt '微软雅黑';color: #2f3640;background-color: #f5f6fa;border-color: #2f3640;border-radius: 15px;border-style: solid;border-width: 2px;padding: 5px;}QPushButton::hover{color: #FFFFFF;background-color: #718093;border-color: #2f3640;}QPushButton::pressed,QPushButton::checked{color: #FFFFFF;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);}QPushButton::disabled{color: #7B68EE;background-color: #dcdde1;border-color: #dcdde1;}");
    connect(m_loginButton,&QPushButton::clicked,this,&LoginInterface::loginButtonClicked);

    m_registrationButton = new QPushButton(this);
    m_registrationButton->setText("注  册");
    m_registrationButton->setGeometry(629,412,197,36);
    m_registrationButton->setStyleSheet("QPushButton{font: 10pt '微软雅黑';color: #2f3640;background-color: #f5f6fa;border-color: #2f3640;border-radius: 15px;border-style: solid;border-width: 2px;padding: 5px;}QPushButton::hover{color: #FFFFFF;background-color: #718093;border-color: #2f3640;}QPushButton::pressed,QPushButton::checked{color: #FFFFFF;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);}QPushButton::disabled{color: #7B68EE;background-color: #dcdde1;border-color: #dcdde1;}");
    connect(m_registrationButton,&QPushButton::clicked,this,&LoginInterface::registrationInterfaceClicked);
}

void LoginInterface::setUserNameText(QString userName)
{
    if (userName != nullptr)
    {
        if (!m_isRememberThePassword->isChecked())
        {
            m_accountNumberText->setText(userName);
            m_passwordText->setText(nullptr);
        }
    }
}

void LoginInterface::loginButtonClicked()
{
    m_errorPrompt->setText(nullptr);
    if (nullptr != m_accountNumberText->text())
    {
        if (nullptr != m_passwordText->text())
        {
            m_loginButton->setEnabled(false);
            m_jsonData.insert("accessDatabaseStatus","Login");
            m_jsonData.insert("accountNumber",m_accountNumberText->text());
            QByteArray ba_md5 = QCryptographicHash::hash(m_passwordText->text().toLocal8Bit(),QCryptographicHash::Md5);
            m_jsonData.insert("password",QString(ba_md5.toHex().toUpper()));
            m_clientData = m_HttpClient->query(m_jsonData);

            if (nullptr == m_clientData)
            {
                m_ServerException->setVisible(true);
            }
            else if("0" == m_clientData)
            {
                m_ServerException->setVisible(false);
                m_errorPrompt->setText("账号或密码错误！");
            }
            else
            {
                saveLoginInformation();
                m_ServerException->setVisible(false);
                emit SwitchInformation(m_clientData);
            }
            m_loginButton->setEnabled(true);
            m_registrationButton->setEnabled(true);
        }
        else
        {
            m_errorPrompt->setText("密码不允许为空！");
        }
    }
    else
    {
        m_errorPrompt->setText("账号不允许为空！");
    }
}

void LoginInterface::readAccount()
{
    QString path = "./user.ini";
    QSettings *config = new QSettings(path, QSettings::IniFormat);

    QString uidsec = config->value(QString("config/") + "uid").toString();
    QByteArray uidb64 = QByteArray::fromBase64(uidsec.toLocal8Bit());
    QString uid = QString::fromLocal8Bit(uidb64);

    QString pwdsec = config->value(QString("config/") + "pwd").toString();
    QByteArray pwdb64 = QByteArray::fromBase64(pwdsec.toLocal8Bit());
    QString pwd = QString::fromLocal8Bit(pwdb64);

    if (uid != nullptr && pwd != nullptr)
    {
        m_accountNumberText->setText(uid);
        m_passwordText->setText(pwd);
        m_isRememberThePassword->setChecked(true);
    }
    else
    {
        m_accountNumberText->setText(uid);
        m_isRememberThePassword->setChecked(false);
    }
    if (config->value(QString("config/") + "automaticLogon").toString() == "true")
    {
        m_isRememberThePassword->setChecked(true);
        m_isAutomaticLogon->setChecked(true);
        m_registrationButton->setEnabled(false);
        m_loginButton->setEnabled(false);
        QTimer::singleShot(3000,this, SLOT(autoLoginStatus()));
    }
}

void LoginInterface::autoLoginStatus()
{
    if (m_isAutomaticLogon->isChecked())
    {
        loginButtonClicked();
    }
    m_loginButton->setEnabled(true);
    m_registrationButton->setEnabled(true);
}

void LoginInterface::saveLoginInformation()
{
    if (m_isAutomaticLogon->isChecked())
    {
        QString path = "./user.ini";
        QSettings *config = new QSettings(path, QSettings::IniFormat);

        QString uidsec = m_accountNumberText->text();
        QByteArray uidb64 = uidsec.toLocal8Bit().toBase64();
        QString uid = QString::fromLocal8Bit(uidb64);

        QString pwdsec = m_passwordText->text();
        QByteArray pwdb64 = pwdsec.toLocal8Bit().toBase64();
        QString pwd = QString::fromLocal8Bit(pwdb64);

        config->beginGroup("config");
        config->setValue("uid", uid);
        config->setValue("pwd", pwd);
        config->setValue("automaticLogon",true);
        config->endGroup();
    }
    else if (m_isRememberThePassword->isChecked())
    {
        QString path = "./user.ini";
        QSettings *config = new QSettings(path, QSettings::IniFormat);

        QString uidsec = m_accountNumberText->text();
        QByteArray uidb64 = uidsec.toLocal8Bit().toBase64();
        QString uid = QString::fromLocal8Bit(uidb64);

        QString pwdsec = m_passwordText->text();
        QByteArray pwdb64 = pwdsec.toLocal8Bit().toBase64();
        QString pwd = QString::fromLocal8Bit(pwdb64);

        config->beginGroup("config");
        config->setValue("uid", uid);
        config->setValue("pwd", pwd);
        config->setValue("automaticLogon",false);
        config->endGroup();
    }
    else
    {
        QString path = "./user.ini";
        QSettings *config = new QSettings(path, QSettings::IniFormat);

        QString uidsec = m_accountNumberText->text();
        QByteArray uidb64 = uidsec.toLocal8Bit().toBase64();
        QString uid = QString::fromLocal8Bit(uidb64);

        config->beginGroup("config");
        config->setValue("uid", uid);
        QString pwd = nullptr;
        config->setValue("pwd", pwd);
        config->setValue("automaticLogon",false);
        config->endGroup();
    }
}

bool LoginInterface::rememberThePassword(int state)
{
    if (state != Qt::Checked)
    {
        m_isAutomaticLogon->setChecked(false);
        return false;
    }
    return true;
}

bool LoginInterface::autoLogSlots(int state)
{
    if (state != Qt::Checked)
    {
        return false;
    }
    m_isRememberThePassword->setChecked(true);
    return true;
}

void LoginInterface::registrationInterfaceClicked()
{
    if (!m_isRememberThePassword->isChecked())
    {
        m_passwordText->setText(nullptr);
    }
    m_errorPrompt->setText(nullptr);
    emit SwitchRegistration();
}

LoginInterface::~LoginInterface()
{

}
