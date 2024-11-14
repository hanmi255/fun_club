#ifndef GAME_H
#define GAME_H

#include "T_BasePage.h"

class Game : public T_BasePage
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit Game(QWidget *parent = nullptr);
    ~Game();
};

#endif // GAME_H
