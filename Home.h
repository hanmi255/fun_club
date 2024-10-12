#ifndef HOME_H
#define HOME_H

#include "T_BasePage.h"
#include <ElaPromotionView.h>
#include <ElaPromotionCard.h>

class Home : public T_BasePage
{
    Q_OBJECT
public:
    explicit Home(QWidget* parent = 0);
    ~Home();
private:
    ElaPromotionView* _promotionView{nullptr};
};

#endif // HOME_H
