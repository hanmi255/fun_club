#ifndef HOME_H
#define HOME_H

#include "T_BasePage.h"

class ElaPromotionView;
class QMouseEvent;
class QStackedWidget;
class Home : public T_BasePage
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit Home(QWidget* parent = nullptr);
    ~Home();

protected:
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private slots:
    void nextPage();
    void prevPage();

private:
    void animatePageChange(int fromIndex, int toIndex);

    ElaPromotionView* _promotionView{nullptr};
    QStackedWidget* _textStack{nullptr};
    bool _isAnimating;

Q_SIGNALS:
    Q_SIGNAL void animeNavigation();
    Q_SIGNAL void comicNavigation();
    Q_SIGNAL void gameNavigation();
    Q_SIGNAL void musicNavigation();
};

#endif // HOME_H
