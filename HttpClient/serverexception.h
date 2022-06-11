#ifndef SERVEREXCEPTION_H
#define SERVEREXCEPTION_H

#include <QWidget>
#include <QLabel>
#include <QApplication>

class ServerException : public QWidget
{
    Q_OBJECT
public:
    ServerException(QWidget *parent = nullptr);
    ~ServerException();

public:

    // 显示服务器异常界面
    void displayServerExceptionInterface();

private:
    QLabel *m_networkExceptionText;
    QLabel *m_pleaseTryAgainText;
};

#endif // SERVEREXCEPTION_H
