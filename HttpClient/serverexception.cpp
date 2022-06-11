#include "serverexception.h"

ServerException::ServerException(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("网络异常");
    this->setFixedSize(350,150);
    this->setWindowFlags( Qt::Tool | Qt::WindowStaysOnTopHint);
    displayServerExceptionInterface();
}

void ServerException::displayServerExceptionInterface()
{
    m_networkExceptionText = new QLabel(this);
    m_networkExceptionText->setText("网络异常提示！");
    m_networkExceptionText->setGeometry(10,10,330,60);
    m_networkExceptionText->setAlignment(Qt::AlignHCenter);
    m_networkExceptionText->setStyleSheet("font-family: 'Microsoft YaHei';font-size: 30px;font-style: italic;font-weight: bold;color: #BDC8E2;font: bold italic 18px 'Microsoft YaHei';");
    m_pleaseTryAgainText = new QLabel(this);
    m_pleaseTryAgainText->setText("请检查网络或服务器未开启");
    m_pleaseTryAgainText->setGeometry(10,80,330,60);
    m_pleaseTryAgainText->setAlignment(Qt::AlignHCenter);
    m_pleaseTryAgainText->setStyleSheet("font-family: 'Microsoft YaHei';font-size: 30px;font-weight: bold;color: red;font: bold italic 18px 'Microsoft YaHei';");
}

ServerException::~ServerException()
{

}
