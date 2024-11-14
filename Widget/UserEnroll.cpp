#include "UserEnroll.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QSpacerItem>
#include <ElaImageCard.h>
#include <ElaText.h>

UserEnroll::UserEnroll(QWidget *parent)
    : ElaWidget(parent),
    closeTimer(new QTimer(this)),
    dbManager(new DataBaseManager())
{
    setWindowTitle("注册");
    setWindowIcon(QIcon(":/Image/Image/Login.jpg"));

    this->setIsFixedSize(true);
    setWindowModality(Qt::ApplicationModal);
    setWindowButtonFlags(ElaAppBarType::CloseButtonHint);

    QLabel *titleLabel = new QLabel("用户注册", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);

    QLabel *userNameLabel = new QLabel("用户名", this);
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

    QLabel *pwdLabel = new QLabel("密码", this);
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

    ElaPushButton *confirmButton = new ElaPushButton("确认", this);
    confirmButton->setFixedSize(60, 32);
    connect(confirmButton, &ElaPushButton::clicked, [=]() {
        enroll();
    });

    // 连接定时器超时信号到关闭窗口的槽函数
    connect(closeTimer, &QTimer::timeout, this, &UserEnroll::close);

    ElaPushButton *cancelButton = new ElaPushButton("取消", this);
    cancelButton->setFixedSize(60, 32);
    connect(cancelButton, &ElaPushButton::clicked, [=]() {
        close();
    });

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(confirmButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->setSpacing(10);

    QVBoxLayout *formLayout = new QVBoxLayout();
    formLayout->setSpacing(8);  // 调整控件之间的间隔为 8
    formLayout->addWidget(userNameLabel);
    formLayout->addWidget(userNameEdit);
    formLayout->addWidget(pwdLabel);
    formLayout->addWidget(pwdEdit);
    formLayout->addLayout(buttonLayout);
    formLayout->setAlignment(Qt::AlignCenter);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->addWidget(titleLabel, 0, Qt::AlignCenter); // 居中标题

    // 添加一个固定大小的占位控件，距离20像素
    QSpacerItem *topSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);
    mainLayout->addSpacerItem(topSpacer);

    mainLayout->addLayout(formLayout, 0); // 居中表单布局

    // 添加底部占位符，使内容居中
    QSpacerItem *bottomSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addSpacerItem(bottomSpacer);

    setLayout(mainLayout);

    Result result = dbManager->connectToDatabase();
    if (result.getStatus() == Result::Failure) {
        ElaMessageBar::error(ElaMessageBarType::Top, "ERROR!", result.getMessage(), 500, this);
    }
}

UserEnroll::~UserEnroll()
{
    delete dbManager;
    delete closeTimer;
}

void UserEnroll::enroll()
{
    QString username = userNameEdit->text();
    QString password = pwdEdit->text();

    if (userNameEdit->text().isEmpty() || pwdEdit->text().isEmpty())
    {
        ElaMessageBar::warning(ElaMessageBarType::Top, "WARNING!", "用户名或密码不能为空", 500, this);
        return;
    }

    Result result = dbManager->enrollUser(username, password);

    if (result.getStatus() == Result::Failure) {
        ElaMessageBar::error(ElaMessageBarType::Top, "ERROR!", result.getMessage(), 500, this);
    }
    else {
        ElaMessageBar::success(ElaMessageBarType::Top, "SUCCESS!", "注册成功", 500, this);
        closeTimer->start(500); // 等待500毫秒后关闭窗口
    }
}
