#include "informationinterface.h"

InformationInterface::InformationInterface(QWidget *parent)
    : QWidget(parent)
    ,m_isAdministrator(false)
    ,m_bPressFlag(false)
{
    displayInformationInterface();
}

void InformationInterface::displayInformationInterface()
{
//    this->setWindowTitle("用户信息");
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(800,550);
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,QBrush(QPixmap(":/image/ApusColors.png").scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    this->setPalette(palette);
    m_desktop = QApplication::desktop();

    m_HttpClient = new HttpClient();
    m_ServerException = new ServerException();

    m_currentStateText = new QLabel(this);
    m_currentStateText->setGeometry(0,0,800,60);
    m_currentStateText->setText("用 户 信 息");
    m_currentStateText->setAlignment(Qt::AlignCenter);
    m_currentStateText->setStyleSheet("QLabel{font-family: 'Microsoft YaHei';font-size: 40px;font-weight: bold;color:#ffffff;background-color:#cc99ff;}");

    m_closeButton = new QPushButton(this);
    m_closeButton->setGeometry(750,10,40,40);
    m_closeButton->setStyleSheet("border-image:url(:/image/close.png)");
    connect(m_closeButton,&QPushButton::clicked,this,&QWidget::close);

    m_narrowButton = new QPushButton(this);
    m_narrowButton->setGeometry(700,10,40,40);
    m_narrowButton->setStyleSheet("border-image:url(:/image/minimized.png)");
    connect(m_narrowButton,&QPushButton::clicked,this,&QWidget::showMinimized);

    m_personalCenterButton = new QPushButton(this);
    m_personalCenterButton->setText("个 人 中 心");
    m_personalCenterButton->setGeometry(10,100,150,70);
    connect(m_personalCenterButton,&QPushButton::clicked,this,&InformationInterface::personalCenterClicked);
    m_personalCenterButton->setStyleSheet("QPushButton{color:#ffffff;background-color:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop:0 #aa55ff, stop: 1 #1296db);border-style:outset;border-width:2px;border-color:#0055ff;border-radius:10px;font:bold 14px;font-family: Segoe UI;min-width:100px;min-height:20px;padding:4px;}QPushButton:hover{color:#ffffff;background-color:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop:0 #ff55ff, stop: 1 #1296db);border-style:outset;border-width:2px;border-color:#0055ff;border-radius:10px;font:bold 14px;font-family: Segoe UI;min-width:100px;min-height:20px;padding:4px;}QPushButton:pressed{color:#ffffff;background-color:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop:0 #ff55ff, stop: 1 #aa00ff);border-style:outset;border-width:2px;border-color:#0055ff;border-radius:10px;font:bold 14px;font-family: Segoe UI;min-width:100px;min-height:20px;padding:4px;}");
    m_personalCenterButton->setEnabled(false);

    m_personalCenterWidget = new QWidget(this);
    m_personalCenterWidget->setGeometry(170,100,620,430);
    m_accountNicknameTipsText = new QLabel(m_personalCenterWidget);
    m_accountNicknameTipsText->setText("昵称：");
    m_accountNicknameTipsText->setStyleSheet("font-family: 'Microsoft YaHei';font-size: 32px;font-weight: bold;color: #BDC8E2");
    m_accountNicknameTipsText->setGeometry(150,10,100,40);
    m_accountNicknameText = new QLabel(m_personalCenterWidget);
    m_accountNicknameText->setStyleSheet("font-family: 'Microsoft YaHei';font-size: 26px;font-weight: bold;color: #9400D3");
    m_accountNicknameText->setGeometry(250,10,100,40);
    m_accountNumberTipsText = new QLabel(m_personalCenterWidget);
    m_accountNumberTipsText->setText("账号：");
    m_accountNumberTipsText->setStyleSheet("font-family: 'Microsoft YaHei';font-size: 32px;font-weight: bold;color: #BDC8E2");
    m_accountNumberTipsText->setGeometry(150,60,100,40);
    m_accountNumberText = new QLabel(m_personalCenterWidget);
    m_accountNumberText->setStyleSheet("font-family: 'Microsoft YaHei';font-size: 26px;font-weight: bold;color: #9400D3");
    m_accountNumberText->setGeometry(250,60,100,40);
    m_mailTipsText = new QLabel(m_personalCenterWidget);
    m_mailTipsText->setText("邮箱：");
    m_mailTipsText->setStyleSheet("font-family: 'Microsoft YaHei';font-size: 32px;font-weight: bold;color: #BDC8E2");
    m_mailTipsText->setGeometry(150,110,100,40);
    m_mailText = new QLabel(m_personalCenterWidget);
    m_mailText->setStyleSheet("font-family: 'Microsoft YaHei';font-size: 26px;font-weight: bold;color: #9400D3");
    m_mailText->setGeometry(250,110,360,40);
    m_telephoneNumberTipsText = new QLabel(m_personalCenterWidget);
    m_telephoneNumberTipsText->setText("手机：");
    m_telephoneNumberTipsText->setStyleSheet("font-family: 'Microsoft YaHei';font-size: 32px;font-weight: bold;color: #BDC8E2");
    m_telephoneNumberTipsText->setGeometry(150,160,120,40);
    m_telephoneNumberText = new QLabel(m_personalCenterWidget);
    m_telephoneNumberText->setStyleSheet("font-family: 'Microsoft YaHei';font-size: 26px;font-weight: bold;color: #9400D3");
    m_telephoneNumberText->setGeometry(250,160,300,40);
    m_departmentTipsText = new QLabel(m_personalCenterWidget);
    m_departmentTipsText->setText("小组：");
    m_departmentTipsText->setStyleSheet("font-family: 'Microsoft YaHei';font-size: 32px;font-weight: bold;color: #BDC8E2");
    m_departmentTipsText->setGeometry(150,210,100,40);
    m_departmentText = new QLabel(m_personalCenterWidget);
    m_departmentText->setStyleSheet("font-family: 'Microsoft YaHei';font-size: 26px;font-weight: bold;color: #9400D3");
    m_departmentText->setGeometry(250,210,100,40);
    m_editInformationButton = new QPushButton(m_personalCenterWidget);
    m_editInformationButton->setText("编辑个人信息");
    m_editInformationButton->setGeometry(195,300,220,40);
    m_editInformationButton->setStyleSheet("QPushButton{font: 10pt '微软雅黑';color: #2f3640;background-color: #ccccff;border-color: #2f3640;border-radius: 15px;border-style: solid;border-width: 2px;padding: 5px;}QPushButton::hover{color: #FFFFFF;background-color: #718093;border-color: #2f3640;}QPushButton::pressed,QPushButton::checked{color: #FFFFFF;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);}QPushButton::disabled{color: #7B68EE;background-color: #dcdde1;border-color: #dcdde1;}");
    connect(m_editInformationButton,&QPushButton::clicked,this,&InformationInterface::editInformationClicked);

    m_editInformationWidget = new QWidget(this);
    m_editInformationWidget->setGeometry(170,100,620,430);
    m_editInformationWidget->setVisible(false);
    m_accountNicknameTipsText = new QLabel(m_editInformationWidget);
    m_accountNicknameTipsText->setText("昵称：");
    m_accountNicknameTipsText->setStyleSheet("font-family: 'Microsoft YaHei';font-size: 32px;font-weight: bold;color: #BDC8E2");
    m_accountNicknameTipsText->setGeometry(150,10,100,40);
    m_modifyAccountNicknameText = new QLineEdit(m_editInformationWidget);
    m_modifyAccountNicknameText->setGeometry(250,15,200,35);
    m_modifyAccountNicknameText->setPlaceholderText("请输入修改昵称");
    m_modifyAccountNicknameText->setMaxLength(16);
    m_modifyAccountNicknameText->setStyleSheet("QLineEdit{border: 1px solid gray;border-radius: 4px;padding: 0 8px;background: white;selection-background-color: darkgray; }QListView{background-color: white;background-image: url(draft.png);background-attachment: fixed;}QLineEdit[echoMode='2']{lineedit-password-character: 9679;}QLineEdit:read-only{background: lightblue;}");
    m_accountNumberTipsText = new QLabel(m_editInformationWidget);
    m_accountNumberTipsText->setText("账号：");
    m_accountNumberTipsText->setStyleSheet("font-family: 'Microsoft YaHei';font-size: 32px;font-weight: bold;color: #BDC8E2");
    m_accountNumberTipsText->setGeometry(150,60,100,40);
    m_editAccountNumberText = new QLabel(m_editInformationWidget);
    m_editAccountNumberText->setStyleSheet("font-family: 'Microsoft YaHei';font-size: 32px;font-weight: bold;color: #9400D3");
    m_editAccountNumberText->setGeometry(250,60,100,40);
    m_mailTipsText = new QLabel(m_editInformationWidget);
    m_mailTipsText->setText("邮箱：");
    m_mailTipsText->setStyleSheet("font-family: 'Microsoft YaHei';font-size: 32px;font-weight: bold;color: #BDC8E2");
    m_mailTipsText->setGeometry(150,110,100,40);
    m_modifyAccountMailboxText = new QLineEdit(m_editInformationWidget);
    m_modifyAccountMailboxText->setGeometry(250,115,200,35);
    m_modifyAccountMailboxText->setPlaceholderText("请输入修改邮箱");
    m_modifyAccountMailboxText->setMaxLength(18);
    m_modifyAccountMailboxText->setStyleSheet("QLineEdit{border: 1px solid gray;border-radius: 4px;padding: 0 8px;background: white;selection-background-color: darkgray; }QListView{background-color: white;background-image: url(draft.png);background-attachment: fixed;}QLineEdit[echoMode='2']{lineedit-password-character: 9679;}QLineEdit:read-only{background: lightblue;}");
    m_telephoneNumberTipsText = new QLabel(m_editInformationWidget);
    m_telephoneNumberTipsText->setText("手机：");
    m_telephoneNumberTipsText->setStyleSheet("font-family: 'Microsoft YaHei';font-size: 32px;font-weight: bold;color: #BDC8E2");
    m_telephoneNumberTipsText->setGeometry(150,160,120,40);
    QRegExp phone = QRegExp("^1([358][0-9]|4[579]|66|7[0135678]|9[89])[0-9]{8}$");
    m_phoneValidator = new QRegExpValidator(phone);
    m_modifyAccountMobileNumberText = new QLineEdit(m_editInformationWidget);
    m_modifyAccountMobileNumberText->setGeometry(250,165,200,35);
    m_modifyAccountMobileNumberText->setPlaceholderText("请输入修改手机号码");
    m_modifyAccountMobileNumberText->setValidator(m_phoneValidator);
    m_modifyAccountMobileNumberText->setMaxLength(16);
    m_modifyAccountMobileNumberText->setStyleSheet("QLineEdit{border: 1px solid gray;border-radius: 4px;padding: 0 8px;background: white;selection-background-color: darkgray; }QListView{background-color: white;background-image: url(draft.png);background-attachment: fixed;}QLineEdit[echoMode='2']{lineedit-password-character: 9679;}QLineEdit:read-only{background: lightblue;}");
    m_departmentTipsText = new QLabel(m_editInformationWidget);
    m_departmentTipsText->setText("小组：");
    m_departmentTipsText->setStyleSheet("font-family: 'Microsoft YaHei';font-size: 32px;font-weight: bold;color: #BDC8E2");
    m_departmentTipsText->setGeometry(150,210,100,40);
    m_groupQueryButton = new QPushButton(this);
    m_modifyAccountDepartment = new QComboBox(m_editInformationWidget);
    m_modifyAccountDepartment->setGeometry(250,215,200,35);
    m_modifyErrorPrompt = new QLabel(m_editInformationWidget);
    m_modifyErrorPrompt->setGeometry(250,260,200,30);
    m_modifyErrorPrompt->setStyleSheet("color:red;");
    m_returnPersonalInformationButton = new QPushButton(m_editInformationWidget);
    m_returnPersonalInformationButton->setText("返 回");
    m_returnPersonalInformationButton->setGeometry(195,300,100,40);
    m_returnPersonalInformationButton->setStyleSheet("QPushButton{font: 10pt '微软雅黑';color: #2f3640;background-color: #ccccff;border-color: #2f3640;border-radius: 15px;border-style: solid;border-width: 2px;padding: 5px;}QPushButton::hover{color: #FFFFFF;background-color: #718093;border-color: #2f3640;}QPushButton::pressed,QPushButton::checked{color: #FFFFFF;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);}QPushButton::disabled{color: #7B68EE;background-color: #dcdde1;border-color: #dcdde1;}");
    connect(m_returnPersonalInformationButton,&QPushButton::clicked,this,&InformationInterface::personalCenterClicked);
    m_submitModificationInformationButton = new QPushButton(m_editInformationWidget);
    m_submitModificationInformationButton->setText("修 改");
    m_submitModificationInformationButton->setGeometry(315,300,100,40);
    m_submitModificationInformationButton->setStyleSheet("QPushButton{font: 10pt '微软雅黑';color: #2f3640;background-color: #ccccff;border-color: #2f3640;border-radius: 15px;border-style: solid;border-width: 2px;padding: 5px;}QPushButton::hover{color: #FFFFFF;background-color: #718093;border-color: #2f3640;}QPushButton::pressed,QPushButton::checked{color: #FFFFFF;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);}QPushButton::disabled{color: #7B68EE;background-color: #dcdde1;border-color: #dcdde1;}");
    connect(m_submitModificationInformationButton,&QPushButton::clicked,this,&InformationInterface::submitModificationInformation);

    m_groupQueryButton->setText("小 组 查 询");
    m_groupQueryButton->setGeometry(10,180,150,70);
    m_groupQueryButton->setStyleSheet("QPushButton{color:#ffffff;background-color:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop:0 #aa55ff, stop: 1 #1296db);border-style:outset;border-width:2px;border-color:#0055ff;border-radius:10px;font:bold 14px;font-family: Segoe UI;min-width:100px;min-height:20px;padding:4px;}QPushButton:hover{color:#ffffff;background-color:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop:0 #ff55ff, stop: 1 #1296db);border-style:outset;border-width:2px;border-color:#0055ff;border-radius:10px;font:bold 14px;font-family: Segoe UI;min-width:100px;min-height:20px;padding:4px;}QPushButton:pressed{color:#ffffff;background-color:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop:0 #ff55ff, stop: 1 #aa00ff);border-style:outset;border-width:2px;border-color:#0055ff;border-radius:10px;font:bold 14px;font-family: Segoe UI;min-width:100px;min-height:20px;padding:4px;}");
    connect(m_groupQueryButton,&QPushButton::clicked,this,&InformationInterface::groupQueryClicked);

    m_groupInterfaceWidget = new QWidget(this);
    m_groupInterfaceWidget->setVisible(false);
    m_groupInterfaceWidget->setGeometry(170,30,620,510);
    m_groupInterface = new QTableWidget(m_groupInterfaceWidget);
    m_groupInterface->setGeometry(0,70,620,430);
    m_groupInterface->setContextMenuPolicy(Qt::CustomContextMenu);
    m_groupInterface->setStyleSheet("QTableWidget{color:#DCDCDC;background:#444444;border:1px solid #242424;alternate-background-color:#525252;gridline-color:#242424;}QTableWidget::item:selected{color:#DCDCDC;background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #484848,stop:1 #383838);}QTableWidget::item:hover{background:#5B5B5B;}QHeaderView::section{text-align:center;background:#5E5E5E;padding:3px;margin:0px;color:#DCDCDC;border:1px solid #242424;border-left-width:0;}QScrollBar:vertical{background:#484848;padding:0px;border-radius:6px;max-width:12px;}QScrollBar::handle:vertical{background:#CCCCCC;}QScrollBar::handle:hover:vertical,QScrollBar::handle:pressed:vertical{background:#A7A7A7;}QScrollBar::sub-page:vertical{background:444444;}QScrollBar::add-page:vertical{background:5B5B5B;}QScrollBar::add-line:vertical{background:none;}QScrollBar::sub-line:vertical{background:none;}");
    m_selectDepartmentPrompt = new QLabel(m_groupInterfaceWidget);
    m_selectDepartmentPrompt->setText("请选择查询小组：");
    m_selectDepartmentPrompt->setGeometry(0,35,380,30);
    m_selectDepartmentPrompt->setStyleSheet("QLabel {font-family: 'Microsoft YaHei';font-size: 20px;color: #BDC8E2;}");
    m_department = new QComboBox(m_groupInterfaceWidget);
    m_department->setGeometry(180,35,100,30);
    m_department->setStyleSheet("QComboBox {border: 1px solid gray;border-radius: 3px;padding: 1px 18px 1px 3px;color: #000;font: normal normal 15px 'Microsoft YaHei';background: #F8F8FF;}QComboBox QAbstractItemView {outline: 0px solid gray;border: 1px solid yellow;color: green;background-color: BlueViolet;selection-background-color: lightgreen;}QComboBox QAbstractItemView::item {height: 50px;}QComboBox QAbstractItemView::item:hover {color: #00FFFF;background-color: lightgreen;}QComboBox QAbstractItemView::item:selected {color: #00FFFF;background-color: LightCyan;}QComboBox QAbstractScrollArea QScrollBar:vertical {width: 10px;background-color: #d0d2d4;}QComboBox QAbstractScrollArea QScrollBar::handle:vertical {border-radius: 5px;background: rgb(160,160,160);}QComboBox QAbstractScrollArea QScrollBar::handle:vertical:hover {background: rgb(90, 91, 93);}QComboBox:editable {background: green;}QComboBox:!editable {background: GhostWhite;}QComboBox:editable:on {background: green;}QComboBox:!editable:on {background: blue;}QComboBox::drop-down:editable {background: lightblue;}QComboBox::drop-down:editable:on {background: lightgreen;}QComboBox::drop-down:!editable {background: lightblue;}QComboBox::drop-down:!editable:on {background: lightgreen;}QComboBox:on {}QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 15px;border-left-width: 1px;border-left-color: darkgray;border-left-style: solid;border-top-right-radius: 3px;border-bottom-right-radius: 3px;}QComboBox::down-arrow {width: 15px;background: transparent;padding: 0px 0px 0px 0px;image: url(:/images/combobox_arrow_down.png);}QComboBox::down-arrow:on {image: url(:/images/combobox_arrow_up.png);}");
    m_groupConfirmationQueryButton = new QPushButton(m_groupInterfaceWidget);
    m_groupConfirmationQueryButton->setText("查询");
    m_groupConfirmationQueryButton->setGeometry(290,35,80,30);
    m_groupConfirmationQueryButton->setStyleSheet("QPushButton{font: 10pt '微软雅黑';color: #2f3640;background-color: #f5f6fa;border-color: #2f3640;border-radius: 15px;border-style: solid;border-width: 2px;padding: 5px;}QPushButton::hover{color: #FFFFFF;background-color: #718093;border-color: #2f3640;}QPushButton::pressed,QPushButton::checked{color: #FFFFFF;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);}QPushButton::disabled{color: #7B68EE;background-color: #dcdde1;border-color: #dcdde1;}");
    connect(m_groupConfirmationQueryButton,&QPushButton::clicked,this,&InformationInterface::confirmationQueryTeamClicked);
    m_createGroupInputText = new QLineEdit(m_groupInterfaceWidget);
    m_createGroupInputText->setGeometry(380,35,100,30);
    m_createGroupInputText->setPlaceholderText("小组昵称");
    m_createGroupInputText->setStyleSheet("QLineEdit{border: 1px solid gray;border-radius: 4px;padding: 0 8px;background: white;selection-background-color: darkgray; }QListView{background-color: white;background-image: url(draft.png);background-attachment: fixed;}QLineEdit[echoMode='2']{lineedit-password-character: 9679;}QLineEdit:read-only{background: lightblue;}");
    m_addGroupButton = new QPushButton(m_groupInterfaceWidget);
    m_addGroupButton->setText("添加小组");
    m_addGroupButton->setGeometry(490,35,70,30);
    m_addGroupButton->setStyleSheet("QPushButton{font: 10pt '微软雅黑';color: #2f3640;background-color: #f5f6fa;border-color: #2f3640;border-radius: 15px;border-style: solid;border-width: 2px;padding: 5px;}QPushButton::hover{color: #FFFFFF;background-color: #718093;border-color: #2f3640;}QPushButton::pressed,QPushButton::checked{color: #FFFFFF;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);}QPushButton::disabled{color: #7B68EE;background-color: #dcdde1;border-color: #dcdde1;}");
    connect(m_addGroupButton,&QPushButton::clicked,this,&InformationInterface::addGroupClicked);
    m_groupErrorPrompt = new QLabel(m_groupInterfaceWidget);
    m_groupErrorPrompt->setGeometry(380,55,100,30);
    m_groupErrorPrompt->setStyleSheet("color:red;");

    //    m_modifyInformationButton = new QPushButton(this);
    //    m_modifyInformationButton->setText("修改信息");
    //    m_modifyInformationButton->setGeometry(10,260,150,70);

    m_logOutButton = new QPushButton(this);
    m_logOutButton->setText("退 出 登 录");
    m_logOutButton->setGeometry(10,340,150,70);
    m_logOutButton->setStyleSheet("QPushButton{color:#ffffff;background-color:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop:0 #aa55ff, stop: 1 #1296db);border-style:outset;border-width:2px;border-color:#0055ff;border-radius:10px;font:bold 14px;font-family: Segoe UI;min-width:100px;min-height:20px;padding:4px;}QPushButton:hover{color:#ffffff;background-color:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop:0 #ff55ff, stop: 1 #1296db);border-style:outset;border-width:2px;border-color:#0055ff;border-radius:10px;font:bold 14px;font-family: Segoe UI;min-width:100px;min-height:20px;padding:4px;}QPushButton:pressed{color:#ffffff;background-color:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop:0 #ff55ff, stop: 1 #aa00ff);border-style:outset;border-width:2px;border-color:#0055ff;border-radius:10px;font:bold 14px;font-family: Segoe UI;min-width:100px;min-height:20px;padding:4px;}");
    connect(m_logOutButton,&QPushButton::clicked,this,&InformationInterface::logOutButtonClicked);
}

void InformationInterface::personalCenterClicked()
{
    this->setWindowTitle("用户信息");
    m_currentStateText->setText("用 户 信 息");
    m_groupInterfaceWidget->setVisible(false);
    m_editInformationWidget->setVisible(false);
    m_personalCenterWidget->setVisible(true);

    m_personalCenterButton->setEnabled(false);
    m_groupQueryButton->setEnabled(true);
    //    m_modifyInformationButton->setEnabled(true);
    m_logOutButton->setEnabled(true);

    m_groupErrorPrompt->setText(nullptr);
}

void InformationInterface::editInformationClicked()
{
    m_currentStateText->setText("编 辑 个 人 信 息");
    m_modifyAccountNicknameText->setText(m_accountNicknameText->text());
    m_editAccountNumberText->setText(m_accountNumberText->text());
    m_modifyAccountMailboxText->setText(m_mailText->text());
    m_modifyAccountMobileNumberText->setText(m_telephoneNumberText->text());

    QJsonObject m_jsonData;
    m_jsonData.insert("accessDatabaseStatus","QueryDepartment");
    m_clientData = m_HttpClient->query(m_jsonData);
    m_modifyAccountDepartment->clear();
    if (nullptr == m_clientData)
    {
        m_ServerException->setVisible(true);
    }
    else
    {
        QStringList datas = m_clientData.split("}\n");
        foreach (QString data , datas)
        {
            data.append("}\n");
            QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
            QJsonObject jsonData = doc.object();
            m_modifyAccountDepartment->insertItem(jsonData["Departmentid"].toString().toInt(), jsonData["Departname"].toString());
        }
        m_modifyAccountDepartment->removeItem(0);
    }
    if (nullptr != m_departmentText->text())
    {
        m_modifyAccountDepartment->setCurrentText(m_departmentText->text());
    }

    m_personalCenterWidget->setVisible(false);
    m_editInformationWidget->setVisible(true);
}

void InformationInterface::submitModificationInformation()
{
    m_modifyErrorPrompt->setText(nullptr);
    QRegExp rx("^[a-z0-9A-Z]+[- | a-z0-9A-Z . _]+@([a-z0-9A-Z]+(-[a-z0-9A-Z]+)?\\.)+[a-z]{2,}$");
    if(rx.exactMatch(m_modifyAccountMailboxText->text()) || m_modifyAccountMailboxText->text() == nullptr)//匹配邮箱格式
    {
        if (m_modifyAccountMobileNumberText->text().length() == 11)
        {
            m_submitModificationInformationButton->setEnabled(false);
            QJsonObject m_jsonData;
            m_jsonData.insert("accessDatabaseStatus","ModifyInformation");
            m_jsonData.insert("modifyAccount",m_editAccountNumberText->text());
            m_jsonData.insert("modifyNickname",m_modifyAccountNicknameText->text());
            m_jsonData.insert("modifyMailbox",m_modifyAccountMailboxText->text());
            m_jsonData.insert("modifyPhoneNumber",m_modifyAccountMobileNumberText->text());
            m_jsonData.insert("modifyDepartmentName",m_modifyAccountDepartment->currentText());
            m_clientData = m_HttpClient->query(m_jsonData);

            if (nullptr == m_clientData)
            {
                m_ServerException->setVisible(true);
            }
            else if (m_clientData.contains("1",Qt::CaseSensitive))
            {
                m_accountNicknameText->setText(m_modifyAccountNicknameText->text());
                m_mailText->setText(m_modifyAccountMailboxText->text());
                m_telephoneNumberText->setText(m_modifyAccountMobileNumberText->text());
                m_departmentText->setText(m_modifyAccountDepartment->currentText());
                m_ServerException->setVisible(false);
                personalCenterClicked();
            }
            else if (m_clientData.contains("0",Qt::CaseSensitive))
            {
                m_ServerException->setVisible(false);
            }
            m_submitModificationInformationButton->setEnabled(true);
        }
        else
        {
            m_modifyErrorPrompt->setText("手机号填写不正确（不允许为空）");
        }
    }
    else
    {
        m_modifyErrorPrompt->setText("邮箱格式不匹配（例：123@qq.com）");
    }
}

void InformationInterface::groupQueryClicked()
{
    this->setWindowTitle("小组查询");
    m_currentStateText->setText("小 组 查 询");
    m_personalCenterWidget->setVisible(false);
    m_editInformationWidget->setVisible(false);
    m_groupInterfaceWidget->setVisible(true);

    m_groupConfirmationQueryButton->setEnabled(false);

    m_groupQueryButton->setEnabled(false);
    m_personalCenterButton->setEnabled(false);
    //    m_modifyInformationButton->setEnabled(true);
    m_logOutButton->setEnabled(false);

    m_groupInterface->clear();
    m_department->clear();

    QJsonObject m_jsonData;
    m_jsonData.insert("accessDatabaseStatus","QueryDepartment");
    m_clientData = m_HttpClient->query(m_jsonData);

    if (nullptr == m_clientData)
    {
        m_ServerException->setVisible(true);
        m_personalCenterButton->setEnabled(true);
        m_logOutButton->setEnabled(true);
        logOutButtonClicked();
    }
    else
    {
        m_department->insertItem(0,"全部");
        m_groupInterface->setColumnCount(m_groupInterfaceHeaderText.count());
        for(int i = 0; i < m_groupInterface->columnCount(); i++)
        {
            m_headerItem = new QTableWidgetItem(m_groupInterfaceHeaderText.at(i));
            m_headerItem->setForeground(Qt::blue);
            m_groupInterface->setHorizontalHeaderItem(i,m_headerItem);
        }

        QStringList datas = m_clientData.split("}\n");
        int i = 1;
        foreach (QString data , datas)
        {
            data.append("}\n");
            QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
            QJsonObject jsonData = doc.object();
            m_department->insertItem(i++,jsonData["Departname"].toString());
        }
        m_department->removeItem(i - 1);

        m_groupErrorPrompt->setText(nullptr);
        confirmationQueryTeamClicked();
    }
    m_groupConfirmationQueryButton->setEnabled(true);
    m_personalCenterButton->setEnabled(true);
    m_logOutButton->setEnabled(true);
}

void InformationInterface::confirmationQueryTeamClicked()
{
    m_groupConfirmationQueryButton->setEnabled(false);
    m_groupQueryButton->setEnabled(false);
    m_personalCenterButton->setEnabled(false);
    m_logOutButton->setEnabled(false);

    m_groupErrorPrompt->setText(nullptr);
    m_groupInterface->clearContents();

    if (m_department->currentText() == "全部")
    {
        QJsonObject m_jsonData;
        m_jsonData.insert("accessDatabaseStatus","QueryMembers");
        m_jsonData.insert("QueryMembers","");
        m_clientData = m_HttpClient->query(m_jsonData);
    }
    else
    {
        QJsonObject m_jsonData;
        m_jsonData.insert("accessDatabaseStatus","QueryMembers");
        m_jsonData.insert("QueryMembers",m_department->currentText());
        m_clientData = m_HttpClient->query(m_jsonData);
    }

    if (nullptr == m_clientData)
    {
        m_ServerException->setVisible(true);
        logOutButtonClicked();
    }
    else
    {
        QStringList datas = m_clientData.split("}\n");
        m_groupInterface->setRowCount(datas.length() - 1);
        int i = 0;
        foreach (QString data , datas)
        {
            data.append("}\n");

            QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
            QJsonObject jsonData = doc.object();

            QTableWidgetItem *accountNumber = new QTableWidgetItem(jsonData["accountNumber"].toString());
            accountNumber->setFlags(accountNumber->flags() & (~Qt::ItemIsEditable));
            QTableWidgetItem *name = new QTableWidgetItem(jsonData["name"].toString());
            name->setFlags(name->flags() & (~Qt::ItemIsEditable));
            QTableWidgetItem *phonenumber = new QTableWidgetItem(jsonData["phonenumber"].toString());
            phonenumber->setFlags(phonenumber->flags() & (~Qt::ItemIsEditable));
            QTableWidgetItem *mail = new QTableWidgetItem(jsonData["mail"].toString());
            mail->setFlags(mail->flags() & (~Qt::ItemIsEditable));
            QTableWidgetItem *departmentName = new QTableWidgetItem(jsonData["departmentName"].toString());
            departmentName->setFlags(departmentName->flags() & (~Qt::ItemIsEditable));

            m_groupInterface->setItem(i,0,accountNumber);
            m_groupInterface->setItem(i,1,name);
            m_groupInterface->setItem(i,2,phonenumber);
            m_groupInterface->setItem(i,3,mail);
            m_groupInterface->setItem(i,4,departmentName);

            if (m_isAdministrator)
            {
                m_deleteMemberButton = new QPushButton(QStringLiteral("删除"));
                m_deleteMemberButton->setProperty("accountNumber", jsonData["accountNumber"].toString());
                connect(m_deleteMemberButton, &QPushButton::clicked, this, &InformationInterface::deleteMemberClicked);
                m_groupInterface->setCellWidget(i,5,m_deleteMemberButton);
            }

            i++;
        }
    }
    m_groupConfirmationQueryButton->setEnabled(true);
    m_personalCenterButton->setEnabled(true);
    m_logOutButton->setEnabled(true);
}

void InformationInterface::addGroupClicked()
{
    if (nullptr != m_createGroupInputText->text())
    {
        m_addGroupButton->setEnabled(false);
        QJsonObject m_jsonData;
        m_jsonData.insert("accessDatabaseStatus","AddDepartment");
        m_jsonData.insert("AddDepartment",m_createGroupInputText->text());
        m_clientData = m_HttpClient->query(m_jsonData);
        if (nullptr == m_clientData)
        {
            m_ServerException->setVisible(true);
            logOutButtonClicked();
        }
        else if (m_clientData.contains("0",Qt::CaseSensitive))
        {
            m_groupErrorPrompt->setText("小组添加失败！");
        }
        else
        {
            m_groupErrorPrompt->setText("小组添加成功！");
            groupQueryClicked();
        }
        m_addGroupButton->setEnabled(true);
    }
    else
    {
        m_groupErrorPrompt->setText("昵称不允许为空！");
    }
}

void InformationInterface::deleteMemberClicked()
{
    QJsonObject m_jsonData;
    QPushButton *deleteButton = qobject_cast<QPushButton*>(sender());
    deleteButton->setEnabled(false);
    QString accountNumber = deleteButton->property("accountNumber").value<QString>();
    m_jsonData.insert("accessDatabaseStatus","DeleteMember");
    m_jsonData.insert("DeleteMember",accountNumber);
    m_clientData = m_HttpClient->query(m_jsonData);
    if (nullptr == m_clientData)
    {
        m_ServerException->setVisible(true);
        logOutButtonClicked();
    }
    else if (m_clientData.contains("1",Qt::CaseSensitive))
    {
        m_groupErrorPrompt->setText("删除成功！");
        groupQueryClicked();
        if (m_accountNumberText->text() == accountNumber)
        {
            logOutButtonClicked();
        }
    }
    else
    {
        m_groupErrorPrompt->setText("删除失败！");
    }
    deleteButton->setEnabled(true);
}

void InformationInterface::loginInformation(QString data)
{
    move((m_desktop->width()-this->width())/2,(m_desktop->height()-this->height())/2);

    m_groupInterfaceHeaderText.clear();
    if (data == "admin")
    {
        m_isAdministrator = true;
        m_createGroupInputText->setVisible(true);
        m_addGroupButton->setVisible(true);
        m_groupInterface->setGeometry(0,70,650,430);
        m_groupInterfaceHeaderText << "账 号" << "昵 称" << "手机号" << "邮 箱" << "小 组" << "操 作";
        m_personalCenterButton->setVisible(false);
        m_groupQueryButton->setText("编 辑 用 户");
        groupQueryClicked();
        m_currentStateText->setText("欢 迎 管 理 员");
    }
    else
    {
        m_isAdministrator = false;
        m_createGroupInputText->setVisible(false);
        m_addGroupButton->setVisible(false);
        m_groupInterface->setGeometry(0,70,524,430);
        m_groupInterfaceHeaderText << "账 号" << "昵 称" << "手机号" << "邮 箱" << "小 组";
        m_groupQueryButton->setText("小 组 查 询");
        m_personalCenterButton->setVisible(true);
    }
    m_loginInformationData = data;
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jsonData = doc.object();
    m_accountNicknameText->setText(jsonData["Nickname"].toString());
    m_accountNumberText->setText(jsonData["Account"].toString());
    m_mailText->setText(jsonData["Mail"].toString());
    m_telephoneNumberText->setText(jsonData["Phonenumber"].toString());
    m_departmentText->setText(jsonData["Departmentname"].toString());
}

void InformationInterface::logOutButtonClicked()
{
    personalCenterClicked();
    emit SwitchLoginInterface(m_accountNumberText->text());
}

void InformationInterface::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setPen(QColor("blue"));
    p.drawRect(0, 0, width() - 2, height() - 2);
}

void InformationInterface::mousePressEvent(QMouseEvent *event)
{
    m_bPressFlag = true;
    m_dragPosition = event->pos();
    QWidget::mousePressEvent(event);
}

void InformationInterface::mouseReleaseEvent(QMouseEvent *event)
{
    m_bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void InformationInterface::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bPressFlag)
    {
        QPoint relaPos(QCursor::pos() - m_dragPosition);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

InformationInterface::~InformationInterface()
{

}
