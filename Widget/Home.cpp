#include "Home.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDesktopServices>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QPixmap>
#include <QStackedWidget>
#include <QResizeEvent>
#include <QMouseEvent>
#include <ElaPromotionView.h>
#include <ElaPromotionCard.h>
#include <ElaText.h>
#include <ElaPopularCard.h>
#include <ElaFlowLayout.h>

Home::Home(QWidget* parent)
    : T_BasePage(parent),
    _promotionView(new ElaPromotionView(this)),
    _textStack(new QStackedWidget(this)),
    _isAnimating(false)
{

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
    _textStack->setFixedSize(350, 140);
    _textStack->setStyleSheet(
        "QStackedWidget {"
        "   border: 2px solid black;"
        "   border-radius: 15px;"
        "   background-color: transparent;"
        "   padding: 10px;"
        "}"
        );

    // 页面标题和内容
    struct PageContent {
        QString title;
        QString content;
    };

    QVector<PageContent> pages = {
        { "既见未来，为何不拜？", "既然你来到这里，想来也是为了“那个”吧？若想寻得请继续探索吧。相信你会得到答案..." },
        { "二重定象", "心爱之人在地狱哀嚎，绵绵的钢铁穿插大地，哭泣的花、欢笑的草，一切都在讽寓" },
        { "三面寓人", "眼看喜、耳听怒、鼻嗅爱、舌尝思、身本忧、意见欲" },
        { "四天狂舞", "鲜血、夜空，动即是风、止即是空，向上绽放耀眼光华"},
        { "五言济世", "铁之公主，泥制人偶，螺旋阶梯，圣文咏唱，皎洁地消散而去"}
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

        content->setTextStyle(ElaTextType::Body);

        pageLayout->addWidget(title, 0, Qt::AlignTop | Qt::AlignLeft); // 放置在左上角
        pageLayout->addSpacing(20);
        pageLayout->addWidget(content, 0, Qt::AlignTop); // 放置在上方
        pageLayout->addStretch();

        _textStack->addWidget(page);
    }
    _textStack->setCurrentIndex(0);

    // toGitHubCard
    ElaPopularCard* toGitHubCard = new ElaPopularCard(this);
    toGitHubCard->setCardButtontext("穿越");
    toGitHubCard->setCardPixmap(QPixmap(":/Image/Image/Home/github.png"));
    toGitHubCard->setTitle("Fun_Club");
    toGitHubCard->setSubTitle("5.0⭐ ACGM集成");
    toGitHubCard->setInteractiveTips("访问");
    toGitHubCard->setDetailedText("Fun_Club为所有ACGM爱好者服务");
    toGitHubCard->setCardFloatPixmap(QPixmap(":/Image/Image/IARC/IARC_3+.svg.png"));
    connect(toGitHubCard, &ElaPopularCard::popularCardButtonClicked, this, [=]() {
        QDesktopServices::openUrl(QUrl("https://github.com/hanmi255/fun_club"));
    });

    QHBoxLayout* text_cardLayout = new QHBoxLayout();
    text_cardLayout->addWidget(_textStack, 1);
    text_cardLayout->addWidget(toGitHubCard, 2);

    centerLayout->addLayout(text_cardLayout);

    // 推荐卡片
    struct PopularCardData {
        QString buttonText;
        QString cardPixmapPath;
        QString title;
        QString subTitle;
        QString interactiveTips;
        QString detailedText;
        QString cardFloatPixmapPath;
        std::function<void()> onButtonClicked; // 处理按钮点击的槽函数
    };

    QVector<PopularCardData> cardDataList = {
        {
            "穿越",
            ":/Image/Image/Home/YourName.jpg",
            "Anime",
            "5.0⭐ 动画",
            "访问",
            "默示录",
            ":/Image/Image/IARC/IARC_3+.svg.png",
            [=]() {
                Q_EMIT animeNavigation();
            }
        }, //toAnime
        {
            "穿越",
            ":/Image/Image/Home/Bleach.jpg",
            "Comic",
            "5.0⭐ 漫画",
            "访问",
            "千纸鹤",
            ":/Image/Image/IARC/IARC_3+.svg.png",
            [=]() {
                Q_EMIT comicNavigation();
            }
        }, //toComic
        {
            "穿越",
            ":/Image/Image/Home/Mario.jpg",
            "Game",
            "5.0⭐ 游戏",
            "访问",
            "游戏人生",
            ":/Image/Image/IARC/IARC_3+.svg.png",
            [=]() {
                Q_EMIT gameNavigation();
            }
        }, //toGame
        {
            "穿越",
            ":/Image/Image/Home/Music.png",
            "Music",
            "5.0⭐ 音乐",
            "访问",
            "献祭曲",
            ":/Image/Image/IARC/IARC_3+.svg.png",
            [=]() {
                Q_EMIT musicNavigation();
            }
        } //toMusic
    };

    // 创建一个流式布局
    ElaFlowLayout* flowLayout = new ElaFlowLayout(0, 5, 5);
    flowLayout->setContentsMargins(100, 0, 0, 0);
    flowLayout->setIsAnimation(true);

    // 遍历数据列表，创建卡片并添加到布局
    for (const PopularCardData& data : cardDataList) {
        ElaPopularCard* card = new ElaPopularCard(this);

        // 设置卡片属性
        card->setCardButtontext(data.buttonText);
        card->setCardPixmap(QPixmap(data.cardPixmapPath));
        card->setTitle(data.title);
        card->setSubTitle(data.subTitle);
        card->setInteractiveTips(data.interactiveTips);
        card->setDetailedText(data.detailedText);
        card->setCardFloatPixmap(QPixmap(data.cardFloatPixmapPath));

        // 连接按钮点击信号到对应的槽函数
        connect(card, &ElaPopularCard::popularCardButtonClicked, this, data.onButtonClicked);

        // 将卡片添加到流式布局
        flowLayout->addWidget(card);
    }

    // 将流式布局添加到中央布局
    centerLayout->addLayout(flowLayout, Qt::AlignCenter);

    // centerLayout->addStretch();
    addCentralWidget(centralWidget, true, true, 0);
}

Home::~Home()
{
    delete this->_promotionView;
    delete this->_textStack;
}

void Home::resizeEvent(QResizeEvent* event)
{
    // 调用基类的resizeEvent方法
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
