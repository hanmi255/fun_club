#ifndef HOME_H
#define HOME_H

#include "T_BasePage.h"
#include <ElaPromotionView.h>
#include <ElaPromotionCard.h>
#include <ElaText.h>
#include <ElaPushButton.h>
#include <ElaWidget.h>

class QMouseEvent;
class QStackedWidget;
class Home : public T_BasePage
{
    Q_OBJECT
public:
    explicit Home(QWidget* parent = 0);
    ~Home();
protected:
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
private slots:
    void nextPage();
    void prevPage();

private:
    void animatePageChange(int fromIndex, int toIndex);

    ElaPromotionView* _promotionView{ nullptr };
    QStackedWidget* _textStack{ nullptr };
    bool _isAnimating;
};

#endif // HOME_H
