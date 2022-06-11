#ifndef SERVERCONFIGURATION_H
#define SERVERCONFIGURATION_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "httpserver.h"

class ServerConfiguration : public QWidget
{
    Q_OBJECT
public:
    ServerConfiguration(QWidget *parent = nullptr);
    ~ServerConfiguration();
public:
    void displayConfigurationInterface();
private slots:
    void setAdministratorAccountClicked();
    void closeAdministratorAccountClicked();
    void turnOnTheServerClicked();
    void shutDownTheServerClicked();
private:
    HttpServer *m_httpServer;
private:
    QLineEdit *m_administratorAccountNumberText;
    QLineEdit *m_administratorPasswordText;
    QPushButton *m_setAdministratorAccountButton;
    QPushButton *m_closeAdministratorAccountButton;
    QPushButton *m_turnOnTheServerButton;
    QPushButton *m_shutDownTheServerButton;
};

#endif // SERVERCONFIGURATION_H
