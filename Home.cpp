#include "Home.h"

#include <QVBoxLayout>

Home::Home(QWidget* parent): T_BasePage(parent)
{
    //预览窗口标题
    setWindowTitle("首页");

    //顶部元素
    createCustomWidget("首页精选书籍");

    //滚动卡片
    _promotionView = new ElaPromotionView(this);

    ElaPromotionCard* book1 = new ElaPromotionCard(this);
    book1->setCardPixmap(QPixmap(":/include/Image/Books/DataStruct.png"));

    ElaPromotionCard* book2 = new ElaPromotionCard(this);
    book2->setCardPixmap(QPixmap(":/include/Image/Books/ComputerNetWork.png"));

    _promotionView->appendPromotionCard(book1);
    _promotionView->appendPromotionCard(book2);
    _promotionView->setIsAutoScroll(true);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("ElaCard");
    QVBoxLayout* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(0, 0, 0, 0);
    centerLayout->addSpacing(20);
    centerLayout->addWidget(_promotionView);
    centerLayout->addSpacing(100);
    centerLayout->addStretch();
    addCentralWidget(centralWidget, true, true, 0);
}

Home::~Home()
{
}
