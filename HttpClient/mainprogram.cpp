#include "mainprogram.h"

MainProgram::MainProgram(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("用户登录");
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(866,486);
    openInterface();
}

void MainProgram::openInterface()
{
    m_desktop = QApplication::desktop();

    m_LoginInterface = new LoginInterface(this);
    m_LoginInterface->setVisible(true);
    connect(m_LoginInterface,&LoginInterface::SwitchRegistration,this,&MainProgram::switchRegistration);
    connect(m_LoginInterface,&LoginInterface::SwitchInformation,this,&MainProgram::switchInformation);

    m_RegistrationInterface = new RegistrationInterface(this);
    m_RegistrationInterface->setVisible(false);
    connect(m_RegistrationInterface,&RegistrationInterface::SwitchLoginInterface,this,&MainProgram::switchLogin);

    m_InformationInterface = new InformationInterface();
    m_InformationInterface->setVisible(false);
    connect(m_InformationInterface,&InformationInterface::SwitchLoginInterface,this,&MainProgram::switchLogin);

    m_currentStateText = new QLabel(this);
    m_currentStateText->setGeometry(0,0,866,60);

    m_closeButton = new QPushButton(this);
    m_closeButton->setGeometry(816,10,40,40);
    m_closeButton->setStyleSheet("border-image:url(:/image/close.png)");
    connect(m_closeButton,&QPushButton::clicked,this,&QWidget::close);

    m_narrowButton = new QPushButton(this);
    m_narrowButton->setGeometry(766,10,40,40);
    m_narrowButton->setStyleSheet("border-image:url(:/image/minimized.png)");
    connect(m_narrowButton,&QPushButton::clicked,this,&QWidget::showMinimized);

}
void MainProgram::switchRegistration()
{
    this->setVisible(true);
    this->setWindowTitle("用户注册");
    this->showNormal();
    m_LoginInterface->setVisible(false);
    m_InformationInterface->setVisible(false);
    m_RegistrationInterface->setVisible(true);
}

void MainProgram::switchLogin(QString data)
{
    move((m_desktop->width()-this->width())/2,(m_desktop->height()-this->height())/2);
    this->setVisible(true);
    this->showNormal();
    this->setWindowTitle("用户登录");
    m_RegistrationInterface->setVisible(false);
    m_InformationInterface->setVisible(false);
    m_LoginInterface->setVisible(true);
    m_LoginInterface->setUserNameText(data);
}

void MainProgram::switchInformation(QString data)
{
    this->setVisible(false);
    m_LoginInterface->setVisible(false);
    m_RegistrationInterface->setVisible(false);
    m_InformationInterface->setVisible(true);
    m_InformationInterface->showNormal();
    m_InformationInterface->loginInformation(data);
}

void MainProgram::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setPen(QColor("red"));
    p.drawRect(0, 0, width() - 3, height() - 3);
}

void MainProgram::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
    {
         m_dragPosition = event->globalPos() - frameGeometry().topLeft();
         event->accept();
    }
}

void MainProgram::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons() == Qt::LeftButton)
    {
         move(event->globalPos() - m_dragPosition);
         event->accept();
    }
}

MainProgram::~MainProgram()
{

}
