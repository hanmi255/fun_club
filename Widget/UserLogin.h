#ifndef USERLOGIN_H
#define USERLOGIN_H

#include <ElaWidget.h>
#include <ElaLineEdit.h>
#include <ElaPushButton.h>
#include <ElaMessageBar.h>
#include <qtimer.h>
#include "UserEnroll.h"

class UserCreate;
class UserLogin : public ElaWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit UserLogin(QWidget *parent = 0);
    ~UserLogin();

private:
    ElaLineEdit *userNameEdit{ nullptr };
    ElaLineEdit *pwdEdit{ nullptr };
    UserEnroll *_userEnrollPage{ nullptr };
    QTimer *closeTimer{ nullptr };
    DataBaseManager *dbManager{ nullptr };

Q_SIGNALS:
    Q_SIGNAL void loginSuccessful(const QString &userName);

private slots:
    /*
    * 登录
    * @param userNameEdited 用户名
    * @param pwdEdited 密码
    */
    void login();
};

#endif // USERLOGIN_H
