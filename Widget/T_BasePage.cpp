#include "T_BasePage.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <ElaMenu.h>
#include <ElaText.h>
#include <ElaTheme.h>
#include <ElaToolButton.h>
#include <QMouseEvent>
#include <QDebug>

T_BasePage::T_BasePage(QWidget *parent)
    : ElaScrollPage(parent)
{
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=]() {
        if (!parent)
        {
            update();
        }
    });
}

T_BasePage::~T_BasePage()
{
}

void T_BasePage::createCustomWidget(QString desText)
{
    // 顶部元素
    QWidget *customWidget = new QWidget(this);
    ElaText *subTitleText = new ElaText(this);
    subTitleText->setText("项目地址：https://github.com/hanmi255/fun_club.git");
    subTitleText->setTextInteractionFlags(Qt::TextSelectableByMouse);
    subTitleText->setTextPixelSize(11);

    QVBoxLayout *topLayout = new QVBoxLayout(customWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->addWidget(subTitleText);
    topLayout->addSpacing(5);
    setCustomWidget(customWidget);
}

void T_BasePage::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
}

void T_BasePage::mousePressEvent(QMouseEvent *event)
{
    // 打印点击位置
    qDebug() << "Base class mousePressEvent: " << event->pos();

    // 调用父类的mousePressEvent，确保默认行为得以执行
    QWidget::mousePressEvent(event);
}
