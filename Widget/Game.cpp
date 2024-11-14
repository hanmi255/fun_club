#include "Game.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <ElaPopularCard.h>
#include <ElaFlowLayout.h>

Game::Game(QWidget *parent)
    : T_BasePage(parent)
{
    // 设置中央布局
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Game");
    QVBoxLayout *centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(0, 0, 0, 0);
    centerLayout->setSpacing(20);

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
            "进入",
            "图片路径",
            "Mygo_GBC五子棋",
            "5.0⭐ 动画",
            "开始",
            "默示录",
            ":/Image/Image/IARC/IARC_3+.svg.png",
            [=]() {

            }
        }, //toMygo_GBC
        {
            "进入",
            "图片路径",
            "Comic",
            "5.0⭐ 漫画",
            "开始",
            "千纸鹤",
            ":/Image/Image/IARC/IARC_3+.svg.png",
            [=]() {

            }
        }, //toGenShin
        {
            "进入",
            "图片路径",
            "Game",
            "5.0⭐ 游戏",
            "开始",
            "游戏人生",
            ":/Image/Image/IARC/IARC_3+.svg.png",
            [=]() {

            }
        }, //toPVZ
        {
            "进入",
            "图片路径",
            "Music",
            "5.0⭐ 音乐",
            "开始",
            "献祭曲",
            ":/Image/Image/IARC/IARC_3+.svg.png",
            [=]() {

            }
        } //toHaJiMi
    };

    // 创建一个流式布局
    ElaFlowLayout *flowLayout = new ElaFlowLayout(0, 5, 5);
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

Game::~Game()
{

}
