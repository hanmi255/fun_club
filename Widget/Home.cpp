#include "Home.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QPixmap>
#include <QStackedWidget>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QFontDatabase>

Home::Home(QWidget* parent)
    : T_BasePage(parent),
    _promotionView(new ElaPromotionView(this)),
    _textStack(new QStackedWidget(this)),
    _isAnimating(false)
{
    // 加载自定义字体
    int fontId = QFontDatabase::addApplicationFont(":/Font/Font/satisfy.regular.ttf");
    QString customFontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);

    // 图片路径
    QStringList imagesPath = {
        ":/Image/Image/Home/miku.png",
        ":/Image/Image/Home/beach.png",
        ":/Image/Image/Home/classroom.png",
        ":/Image/Image/Home/dream.png"
    };

    // 创建展示图片
    for (const QString& imagePath : imagesPath) {
        ElaPromotionCard* scene = new ElaPromotionCard(this);
        scene->setCardPixmap(QPixmap(imagePath));
        _promotionView->appendPromotionCard(scene);
    }
    _promotionView->setIsAutoScroll(true);

    // 设置中央布局
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("MIKU`s Life");
    QVBoxLayout* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(0, 0, 0, 0);
    centerLayout->setSpacing(20);

    centerLayout->addWidget(_promotionView);

    // 设置文本栈
    _textStack->setMinimumSize(400, 500);
    _textStack->setStyleSheet(
        "QStackedWidget {"
        "   border: 2px solid black;"
        "   border-radius: 15px;"
        "   background-color: #DFF9F9;"
        "   padding: 10px;"
        "}"
        );

    // 页面标题和内容
    struct PageContent {
        QString title;
        QString content;
    };

    QVector<PageContent> pages = {
        { "Page1", "************** **************" },
        { "Page2", "************** **************" },
        { "Page3", "************** **************" }
    };

    // 创建页面并添加到 _textStack
    for (const PageContent& pageContent : pages) {
        QWidget* page = new QWidget(this);
        QVBoxLayout* pageLayout = new QVBoxLayout(page);
        pageLayout->setContentsMargins(10, 10, 10, 10); // 设置内边距

        ElaText* title = new ElaText(this);
        title->setText(pageContent.title);
        title->setTextStyle(ElaTextType::Title);

        ElaText* content = new ElaText(this);
        content->setText(pageContent.content);
        content->setStyleSheet(
            QString(
                "QTextEdit {"
                " border: none;"
                " background-color: transparent;"
                " font-family: '%1';"
                " font-size: 18pt;"
                " line-height: 1.5;"
                " padding: 10px;"
                "}"
            ).arg(customFontFamily)
        );

        pageLayout->addWidget(title, 0, Qt::AlignTop | Qt::AlignLeft); // 放置在左上角
        pageLayout->addSpacing(20);
        pageLayout->addWidget(content, 0, Qt::AlignTop); // 放置在上方
        pageLayout->addStretch();

        _textStack->addWidget(page);
    }

    _textStack->setCurrentIndex(0);
    centerLayout->addWidget(_textStack, 1, Qt::AlignCenter);
    centerLayout->addStretch();

    addCentralWidget(centralWidget, true, true, 0);
}

Home::~Home()
{
    delete this->_promotionView;
    delete this->_textStack;
    // delete this->_leftButton;
    // delete this->_rightButton;
}

void Home::resizeEvent(QResizeEvent* event)
{
    T_BasePage::resizeEvent(event);
}

void Home::mousePressEvent(QMouseEvent* event)
{
    if (_isAnimating) {
        return; // 忽略用户点击
    }

    // 获取点击位置相对于文本栈的位置
    QPoint clickPos = event->pos();
    QRect stackRect = _textStack->geometry();

    // 检查点击是否在文本栈内部
    if (stackRect.contains(clickPos)) {
        int stackWidth = stackRect.width();
        int clickX = clickPos.x() - stackRect.left();

        if (clickX < stackWidth / 2) {
            prevPage();  // 点击左半侧翻到上一页
        } else {
            nextPage();  // 点击右半侧翻到下一页
        }
    }

    // 调用基类的mousePressEvent方法
    T_BasePage::mousePressEvent(event);
}

void Home::nextPage()
{
    int currentIndex = _textStack->currentIndex();
    int nextIndex = currentIndex + 1;

    if (nextIndex < _textStack->count()) {
        animatePageChange(currentIndex, nextIndex);
    }
}

void Home::prevPage()
{
    int currentIndex = _textStack->currentIndex();
    int prevIndex = currentIndex - 1;

    if (prevIndex >= 0) {
        animatePageChange(currentIndex, prevIndex);
    }
}

void Home::animatePageChange(int fromIndex, int toIndex)
{
    if (fromIndex < 0 || fromIndex >= _textStack->count() ||
        toIndex < 0 || toIndex >= _textStack->count()) {
        qWarning() << "animatePageChange 中的索引超出范围";
        return;
    }

    QWidget* fromWidget = _textStack->widget(fromIndex);
    QWidget* toWidget = _textStack->widget(toIndex);

    if (!fromWidget || !toWidget) {
        qWarning() << "animatePageChange 中的页面指针无效";
        return;
    }

    // 禁止点击
    _isAnimating = true;

    // 设置目标页面初始透明度为0并显示
    QGraphicsOpacityEffect* toEffect = new QGraphicsOpacityEffect(toWidget);
    toWidget->setGraphicsEffect(toEffect);
    toWidget->setVisible(true);

    QPropertyAnimation* fadeIn = new QPropertyAnimation(toEffect, "opacity");
    fadeIn->setDuration(250);
    fadeIn->setStartValue(0);
    fadeIn->setEndValue(1);

    // 设置当前页面淡出
    QGraphicsOpacityEffect* fromEffect = new QGraphicsOpacityEffect(fromWidget);
    fromWidget->setGraphicsEffect(fromEffect);

    QPropertyAnimation* fadeOut = new QPropertyAnimation(fromEffect, "opacity");
    fadeOut->setDuration(250);
    fadeOut->setStartValue(1);
    fadeOut->setEndValue(0);

    // 创建动画组同时执行
    QParallelAnimationGroup* group = new QParallelAnimationGroup(this);
    group->addAnimation(fadeIn);
    group->addAnimation(fadeOut);

    // 确保动画指针的生命周期
    fadeIn->setParent(group);
    fadeOut->setParent(group);
    toEffect->setParent(toWidget);
    fromEffect->setParent(fromWidget);

    connect(group, &QParallelAnimationGroup::finished, [=]() {
        // 动画完成后设置新页面为当前页
        _textStack->setCurrentIndex(toIndex);

        // 隐藏前一页
        fromWidget->setVisible(false);

        // 清理动画效果对象
        delete fromEffect;
        delete toEffect;

        // 重启点击
        _isAnimating = false;
    });

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

