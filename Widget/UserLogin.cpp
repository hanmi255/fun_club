#include "UserLogin.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <ElaImageCard.h>
#include <ElaText.h>

UserLogin::UserLogin(QWidget* parent)
    : ElaWidget(parent), closeTimer(new QTimer(this)), dbManager(new DataBaseManager())
{
    setWindowTitle("登录");
    setWindowIcon(QIcon(":/Image/Image/Login.jpg"));

    this->setIsFixedSize(true);
    setWindowModality(Qt::ApplicationModal);
    setWindowButtonFlags(ElaAppBarType::CloseButtonHint);

    QLabel* titleLabel = new QLabel("用户登录", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);

    QLabel* userNameLabel = new QLabel("用户名", this);
    QFont userNameLabelFont = userNameLabel->font();
    userNameLabelFont.setWeight(QFont::Bold);
    userNameLabel->setFont(userNameLabelFont);
    userNameLabel->setWordWrap(false);

    userNameEdit = new ElaLineEdit(this);
    userNameEdit->setPlaceholderText("输入用户名");
    userNameEdit->setFixedSize(200, 35);
    connect(userNameEdit, &ElaLineEdit::textChanged, [=]() {
        userNameEdit->setText(userNameEdit->text().trimmed());
    });

    QLabel* pwdLabel = new QLabel("密码", this);
    QFont pwdLabelFont = pwdLabel->font();
    pwdLabelFont.setWeight(QFont::Bold);
    pwdLabel->setFont(pwdLabelFont);
    pwdLabel->setWordWrap(false);

    pwdEdit = new ElaLineEdit(this);
    pwdEdit->setPlaceholderText("输入密码");
    pwdEdit->setFixedSize(200, 35);

    // 设置密码框的回显模式为密码模式
    pwdEdit->setEchoMode(QLineEdit::Password);
    connect(pwdEdit, &ElaLineEdit::textChanged, [=]() {
        pwdEdit->setText(pwdEdit->text().trimmed());
    });

    ElaPushButton* loginButton = new ElaPushButton("登录", this);
    loginButton->setFixedSize(60, 32);
    connect(loginButton, &ElaPushButton::clicked, [=]() {
        login();
    });

    // 连接定时器超时信号到关闭窗口的槽函数
    connect(closeTimer, &QTimer::timeout, this, &UserLogin::close);

    //跳转注册页面
    _userEnrollPage = new UserEnroll();
    _userEnrollPage->hide();
    ElaPushButton* enrollButton = new ElaPushButton("注册", this);
    enrollButton->setFixedSize(60, 32);
    connect(enrollButton, &ElaPushButton::clicked, [=]() {
        _userEnrollPage->setFixedSize(400, 400);
        _userEnrollPage->moveToCenter();
        _userEnrollPage->show();
        this->close();
    });

    // 创建一个水平布局来包含登录和注册按钮
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(enrollButton);
    buttonLayout->setSpacing(10); // 调整按钮之间的间隔

    QVBoxLayout* formLayout = new QVBoxLayout();
    formLayout->setSpacing(8);  // 调整控件之间的间隔为 8
    formLayout->addWidget(userNameLabel);
    formLayout->addWidget(userNameEdit);
    formLayout->addWidget(pwdLabel);
    formLayout->addWidget(pwdEdit);
    formLayout->addLayout(buttonLayout); // 将水平按钮布局添加到表单布局
    formLayout->setAlignment(Qt::AlignCenter);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->addWidget(titleLabel, 0, Qt::AlignCenter); // 居中标题

    // 添加一个固定大小的占位控件，距离20像素
    QSpacerItem* topSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);
    mainLayout->addSpacerItem(topSpacer);

    mainLayout->addLayout(formLayout, 0); // 居中表单布局

    // 添加底部占位符，使内容居中
    QSpacerItem* bottomSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addSpacerItem(bottomSpacer);

    setLayout(mainLayout);

    Result result = dbManager->connectToDatabase();
    if (result.getStatus() == Result::Failure) {
        ElaMessageBar::error(ElaMessageBarType::Top, "ERROR!", result.getMessage(), 500, this);
    }
}

UserLogin::~UserLogin()
{
    delete _userEnrollPage;
    delete dbManager;
    delete closeTimer;
}

void UserLogin::login()
{
    QString username = userNameEdit->text();
    QString password = pwdEdit->text();

    if (userNameEdit->text().isEmpty() || pwdEdit->text().isEmpty())
    {
        ElaMessageBar::warning(ElaMessageBarType::Top, "WARNING!", "用户名或密码不能为空", 500, this);
        return;
    }

    Result result = dbManager->loginUser(username, password);

    if (result.getStatus() == Result::Failure) {
        ElaMessageBar::error(ElaMessageBarType::Top, "ERROR!", result.getMessage(), 500, this);
    }
    else {
        ElaMessageBar::success(ElaMessageBarType::Top, "SUCCESS!", "登录成功", 500, this);
        Q_EMIT loginSuccessful(userNameEdit->text()); // 发出登录成功信号
        closeTimer->start(500); // 等待500毫秒后关闭窗口
    }
}
