#include "Anime.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QDesktopServices>
#include <ElaPromotionView.h>
#include <ElaPromotionCard.h>
#include <ElaText.h>
#include <ElaPivot.h>
#include <ElaScrollPageArea.h>
#include <ElaPopularCard.h>
#include <ElaFlowLayout.h>

Anime::Anime(QWidget *parent)
    : T_BasePage(parent),
    _promotionView(new ElaPromotionView(this)),
    _weekPivot(new ElaPivot(this)),
    _animeStack(new QStackedWidget(this))
{
    // 图片路径
    QStringList imagesPath = {
        ":/Image/Image/Anime/promotion_card/GGO.jpg",
        ":/Image/Image/Anime/promotion_card/di.png",
        ":/Image/Image/Anime/promotion_card/dico.jpg",
        ":/Image/Image/Anime/promotion_card/djdadh.jpg",
        ":/Image/Image/Anime/promotion_card/eeyumw.jpg",
        ":/Image/Image/Anime/promotion_card/gjufjpyr.jpg",
        ":/Image/Image/Anime/promotion_card/lhyuxlxbln.jpg",
        ":/Image/Image/Anime/promotion_card/mktunvpu.jpg",
        ":/Image/Image/Anime/promotion_card/xxmuyzrfvh.jpg",
        ":/Image/Image/Anime/promotion_card/yatoli.jpg",
        ":/Image/Image/Anime/promotion_card/zhssdefulil.jpg"
    };

    // 创建展示图片
    for (const QString &imagePath : imagesPath) {
        ElaPromotionCard *scene = new ElaPromotionCard(this);
        scene->setCardPixmap(QPixmap(imagePath));
        _promotionView->appendPromotionCard(scene);
    }
    _promotionView->setIsAutoScroll(true);

    // 设置中央布局
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Anime");
    QVBoxLayout *centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(0, 0, 0, 0);
    centerLayout->setSpacing(20);

    centerLayout->addWidget(_promotionView);

    // 时间表
    ElaText *pivotText = new ElaText("时间表", this);
    pivotText->setTextPixelSize(18);
    _weekPivot = new ElaPivot(this);
    _weekPivot->setPivotSpacing(15);
    _weekPivot->setMarkWidth(65);
    QVector<QString> week = {
        "周一", "周二", "周三", "周四", "周五", "周六", "周日"
    };
    for(const QString &week : week) {
        _weekPivot->appendPivot(week);
    }
    _weekPivot->setCurrentIndex(0);

    ElaScrollPageArea *pivotArea = new ElaScrollPageArea(this);
    QHBoxLayout *pivotLayout = new QHBoxLayout(pivotArea);
    pivotLayout->addWidget(_weekPivot);

    // 连接信号槽
    connect(_weekPivot, &ElaPivot::pivotClicked, this, &Anime::onPivotClicked);

    // // 推荐卡片
    // struct PopularCardData {
    // QString cardPixmapPath;
    // QString title;
    // QString subTitle;
    // QString detailedText;

    // };

    // QVector> cardDataList = {
    // {
    // {
    // ":/Image/Image/Anime/popular_card/week1/1 (1).jpg",
    // "LoveLive! Superstar!!",
    // "2024/偶像/音乐",
    // "结成了学园偶像组合Liella!的涩谷香音等人迎来了新一届学生。新的少女们开始作为“学园偶像”活动！！",
    // },
    // {
    // ":/Image/Image/Anime/popular_card/week1/1 (2).jpg",
    // "稗记舞咏",
    // "2024/热血/战斗/冒险",
    // "没有了神话的国度为了找回奔向各地的八百万神灵设立了一种职业——歌士官。",
    // },
    // {
    // ":/Image/Image/Anime/popular_card/week1/1 (2).jpg",
    // "稗记舞咏",
    // "2024/热血/战斗/冒险",
    // "没有了神话的国度为了找回奔向各地的八百万神灵设立了一种职业——歌士官。",
    // },
    // {
    // ":/Image/Image/Anime/popular_card/week1/1 (2).jpg",
    // "稗记舞咏",
    // "2024/热血/战斗/冒险",
    // "没有了神话的国度为了找回奔向各地的八百万神灵设立了一种职业——歌士官。",
    // },
    // {
    // ":/Image/Image/Anime/popular_card/week1/1 (2).jpg",
    // "稗记舞咏",
    // "2024/热血/战斗/冒险",
    // "没有了神话的国度为了找回奔向各地的八百万神灵设立了一种职业——歌士官。",
    // },
    // {
    // ":/Image/Image/Anime/popular_card/week1/1 (2).jpg",
    // "稗记舞咏",
    // "2024/热血/战斗/冒险",
    // "没有了神话的国度为了找回奔向各地的八百万神灵设立了一种职业——歌士官。",
    // },
    // },
    // };

    // 设置动画栈
    _animeStack->setStyleSheet(
        "QStackedWidget {"
        " border: 2px solid black;"
        " border-radius: 15px;"
        " background-color: transparent;"
        " padding: 10px;"
        "}"
        );

    // 动画卡片路径
    QVector<QVector<QString>> animeCardPath = {
        {
            ":/Image/Image/Anime/popular_card/week1/1 (1).jpg",
            ":/Image/Image/Anime/popular_card/week1/1 (2).jpg",
            ":/Image/Image/Anime/popular_card/week1/1 (3).jpg",
            ":/Image/Image/Anime/popular_card/week1/1 (4).jpg",
            ":/Image/Image/Anime/popular_card/week1/1 (5).jpg",
            ":/Image/Image/Anime/popular_card/week1/1 (6).jpg",
            ":/Image/Image/Anime/popular_card/week1/1 (7).jpg",
            ":/Image/Image/Anime/popular_card/week1/1 (8).jpg",
            ":/Image/Image/Anime/popular_card/week1/1 (9).jpg"
        },
        {
            ":/Image/Image/Anime/popular_card/week2/2 (1).jpg",
            ":/Image/Image/Anime/popular_card/week2/2 (2).jpg",
            ":/Image/Image/Anime/popular_card/week2/2 (3).jpg",
            ":/Image/Image/Anime/popular_card/week2/2 (4).jpg"
        },
        {
            ":/Image/Image/Anime/popular_card/week3/3 (1).jpg",
            ":/Image/Image/Anime/popular_card/week3/3 (2).jpg",
            ":/Image/Image/Anime/popular_card/week3/3 (3).jpg",
            ":/Image/Image/Anime/popular_card/week3/3 (4).jpg",
            ":/Image/Image/Anime/popular_card/week3/3 (5).jpg",
            ":/Image/Image/Anime/popular_card/week3/3 (6).jpg",
            ":/Image/Image/Anime/popular_card/week3/3 (7).jpg",
            ":/Image/Image/Anime/popular_card/week3/3 (8).jpg"
        },
        {
            ":/Image/Image/Anime/popular_card/week4/4 (1).jpg",
            ":/Image/Image/Anime/popular_card/week4/4 (2).jpg",
            ":/Image/Image/Anime/popular_card/week4/4 (3).jpg",
            ":/Image/Image/Anime/popular_card/week4/4 (4).jpg",
            ":/Image/Image/Anime/popular_card/week4/4 (5).jpg",
            ":/Image/Image/Anime/popular_card/week4/4 (6).jpg",
            ":/Image/Image/Anime/popular_card/week4/4 (7).jpg",
            ":/Image/Image/Anime/popular_card/week4/4 (8).jpg",
            ":/Image/Image/Anime/popular_card/week4/4 (9).jpg"
        },
        {
            ":/Image/Image/Anime/popular_card/week5/5 (1).jpg",
            ":/Image/Image/Anime/popular_card/week5/5 (2).jpg",
            ":/Image/Image/Anime/popular_card/week5/5 (3).jpg",
            ":/Image/Image/Anime/popular_card/week5/5 (4).jpg",
            ":/Image/Image/Anime/popular_card/week5/5 (5).jpg",
            ":/Image/Image/Anime/popular_card/week5/5 (6).jpg",
            ":/Image/Image/Anime/popular_card/week5/5 (7).jpg",
            ":/Image/Image/Anime/popular_card/week5/5 (8).jpg"
        },
        {
            ":/Image/Image/Anime/popular_card/week6/6 (1).jpg",
            ":/Image/Image/Anime/popular_card/week6/6 (2).jpg",
            ":/Image/Image/Anime/popular_card/week6/6 (3).jpg",
            ":/Image/Image/Anime/popular_card/week6/6 (4).jpg",
            ":/Image/Image/Anime/popular_card/week6/6 (5).jpg",
            ":/Image/Image/Anime/popular_card/week6/6 (6).jpg",
            ":/Image/Image/Anime/popular_card/week6/6 (7).jpg",
            ":/Image/Image/Anime/popular_card/week6/6 (8).jpg",
            ":/Image/Image/Anime/popular_card/week6/6 (9).jpg",
            ":/Image/Image/Anime/popular_card/week6/6 (10).jpg"
        },
        {
            ":/Image/Image/Anime/popular_card/week7/7 (1).jpg",
            ":/Image/Image/Anime/popular_card/week7/7 (2).jpg",
            ":/Image/Image/Anime/popular_card/week7/7 (3).jpg",
            ":/Image/Image/Anime/popular_card/week7/7 (4).jpg",
            ":/Image/Image/Anime/popular_card/week7/7 (5).jpg",
            ":/Image/Image/Anime/popular_card/week7/7 (6).jpg",
            ":/Image/Image/Anime/popular_card/week7/7 (7).jpg",
            ":/Image/Image/Anime/popular_card/week7/7 (8).jpg",
            ":/Image/Image/Anime/popular_card/week7/7 (9).jpg",
            ":/Image/Image/Anime/popular_card/week7/7 (10).jpg"
        }
    };

    // 创建页面并添加到 _animeStack
    for (const QVector<QString>& animeContent : animeCardPath) {
        QWidget *animePage = new QWidget(this);

        // 创建一个流式布局
        ElaFlowLayout *animeLayout = new ElaFlowLayout(animePage);
        animeLayout->setContentsMargins(100, 0, 0, 0);
        animeLayout->setIsAnimation(true);

        for (const QString &path : animeContent) {
            QLabel *card = new QLabel(this);
            card->setPixmap(QPixmap(path));
            card->setFixedSize(150, 200);
            card->setScaledContents(true); // 确保图片可以自动缩放适应标签

            card->setCursor(Qt::PointingHandCursor);
            // 安装事件过滤器
            card->installEventFilter(this);
            animeLayout->addWidget(card);
        }
        _animeStack->addWidget(animePage);
    }
    _animeStack->setCurrentIndex(0);

    QVBoxLayout *week_AnimeLayout = new QVBoxLayout(this);
    week_AnimeLayout->addWidget(pivotArea);
    week_AnimeLayout->addWidget(_animeStack, Qt::AlignCenter);

    centerLayout->addWidget(pivotText);
    centerLayout->addLayout(week_AnimeLayout);
    centerLayout->addStretch();
    addCentralWidget(centralWidget, true, true, 0);
}

Anime::~Anime()
{
    delete this->_promotionView;
    delete this->_weekPivot;
    delete this->_animeStack;
}

void Anime:: onPivotClicked(int index)
{
    /**
    * 设置当前页面索引为指定索引
    */
    _animeStack->setCurrentIndex(index);
}

// 过滤器
bool Anime::eventFilter(QObject *obj, QEvent *event)
{
    /**
    * 判断事件类型是否为鼠标按钮按下事件 QEvent::MouseButtonPress。
    * 将事件转换为 QMouseEvent 类型，并检查是否是左键点击。
    * 使用 qobject_cast(obj) 将对象转换为 QLabel 类型，如果转换成功，则说明点击的对象是创建的卡片。
    * 打开指定的 URL
    * 返回 true 表示事件已被处理，不再进行默认处理。
    */
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            QLabel *label = qobject_cast<QLabel*>(obj);
            if (label) {
                QDesktopServices::openUrl(QUrl("https://www.bilibili.com/video/BV1GJ411x7h7"));
                return true;
            }
        }
    }
    return QObject::eventFilter(obj, event);
}
