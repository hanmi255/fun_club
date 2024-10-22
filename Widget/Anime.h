#ifndef ANIME_H
#define ANIME_H

#include "T_BasePage.h"

class ElaPivot;
class ElaPromotionView;
class QStackedWidget;
class Anime : public T_BasePage
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit Anime(QWidget* parent = nullptr);
    ~Anime();

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
private:
    ElaPivot* _weekPivot{nullptr};
    ElaPromotionView* _promotionView{nullptr};
    QStackedWidget* _animeStack{nullptr};

private slots:
    void onPivotClicked(int index);
};

#endif // ANIME_H
