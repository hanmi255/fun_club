#ifndef USERENROLL_H
#define USERENROLL_H

#include <ElaLineEdit.h>
#include <ElaPushButton.h>
#include <ElaMessageBar.h>
#include <ElaWidget.h>
#include <qtimer.h>
#include "DataBaseManager.h"

class UserEnroll : public ElaWidget
{
    Q_OBJECT
public:
    explicit UserEnroll(QWidget* parent = 0);
    ~UserEnroll();
private:
    ElaLineEdit* userNameEdit{ nullptr };
    ElaLineEdit* pwdEdit{ nullptr };
    QTimer* closeTimer{ nullptr };
    DataBaseManager* dbManager{ nullptr };
private slots:
    /*
    * 创建用户
    * @param:userNameEdited 用户名
    * @param:pwdEdited 密码
    */
    void enroll();
};

#endif // USERENROLL_H
