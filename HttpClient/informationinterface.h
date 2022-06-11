#ifndef INFORMATIONINTERFACE_H
#define INFORMATIONINTERFACE_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStandardItem>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDesktopWidget>
#include <QPainter>
#include <QMouseEvent>
#include "httpclient.h"
#include "serverexception.h"

class InformationInterface : public QWidget
{
    Q_OBJECT
public:
    InformationInterface(QWidget *parent = nullptr);
    ~InformationInterface();

public:
    void loginInformation(QString data);

signals:

    // 切换登录界面
    void SwitchLoginInterface(QString data);

private slots:

    // 退出登录
    void logOutButtonClicked();

    // 个人信息
    void personalCenterClicked();

    // 编辑个人信息
    void editInformationClicked();

    // 提交修改信息
    void submitModificationInformation();

    // 分组查询
    void groupQueryClicked();

    // 确认查询小组
    void confirmationQueryTeamClicked();

    // 添加小组
    void addGroupClicked();

    // 删除小组成员
    void deleteMemberClicked();

protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:

    // 显示注册界面
    void displayInformationInterface();

private:
    HttpClient *m_HttpClient;
    ServerException *m_ServerException;
private:
    QPoint m_dragPosition;
    QDesktopWidget *m_desktop;

    QLabel *m_currentStateText;
    QPushButton *m_closeButton;
    QPushButton *m_narrowButton;

    QPushButton *m_personalCenterButton;
    QPushButton *m_groupQueryButton;
    //    QPushButton *m_modifyInformationButton;
    QPushButton *m_logOutButton;

    QWidget *m_personalCenterWidget;
    QLabel *m_accountNicknameTipsText;
    QLabel *m_accountNicknameText;
    QLabel *m_accountNumberTipsText;
    QLabel *m_accountNumberText;
    QLabel *m_mailTipsText;
    QLabel *m_mailText;
    QLabel *m_telephoneNumberTipsText;
    QLabel *m_telephoneNumberText;
    QLabel *m_departmentTipsText;
    QLabel *m_departmentText;
    QPushButton *m_editInformationButton;

    QWidget *m_editInformationWidget;
    QLineEdit *m_modifyAccountNicknameText;
    QLabel *m_editAccountNumberText;
    QLineEdit *m_modifyAccountMailboxText;
    QRegExpValidator *m_phoneValidator;
    QLineEdit *m_modifyAccountMobileNumberText;
    QComboBox *m_modifyAccountDepartment;
    QLabel *m_modifyErrorPrompt;
    QPushButton *m_returnPersonalInformationButton;
    QPushButton *m_submitModificationInformationButton;

    QWidget *m_groupInterfaceWidget;
    QTableWidget *m_groupInterface;
    QTableWidgetItem *m_headerItem;
    QLabel *m_selectDepartmentPrompt;
    QComboBox *m_department;
    QPushButton *m_groupConfirmationQueryButton;
    QLineEdit *m_createGroupInputText;
    QPushButton *m_addGroupButton;
    QLabel *m_groupErrorPrompt;
    QPushButton *m_deleteMemberButton;

    QTableWidget *m_modifyPersonalInformation;
private:
    QStringList m_groupInterfaceHeaderText;
    QString m_loginInformationData;

    QString m_clientData;
    QJsonDocument m_doc;
    bool m_isAdministrator;

    bool m_bPressFlag;
};

#endif // INFORMATIONINTERFACE_H
