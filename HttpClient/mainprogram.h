#ifndef MAINPROGRAM_H
#define MAINPROGRAM_H

#include <QObject>
#include <QDesktopWidget>
#include "logininterface.h"
#include "registrationinterface.h"
#include "informationinterface.h"

class MainProgram : public QWidget
{
    Q_OBJECT
public:
    MainProgram(QWidget *parent = nullptr);
    ~MainProgram();

public:

    // 主程序
    void openInterface();

public slots:
    // 切换注册界面
    void switchRegistration();
    // 切换登录界面
    void switchLogin(QString data);
    // 切换主界面
    void switchInformation(QString data);
protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private:
    LoginInterface *m_LoginInterface;
    RegistrationInterface *m_RegistrationInterface;
    InformationInterface *m_InformationInterface;
private:
    QPoint m_dragPosition;
    QDesktopWidget *m_desktop;

    QLabel *m_currentStateText;

    QPushButton *m_closeButton;
    QPushButton *m_narrowButton;
};

#endif // MAINPROGRAM_H
