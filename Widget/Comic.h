#ifndef COMIC_H
#define COMIC_H

#include "T_BasePage.h"
class ElaRadioButton;
class ElaToggleSwitch;
class ElaComboBox;
class Comic : public T_BasePage
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit Comic(QWidget *parent = nullptr);
    ~Comic();

private:
    ElaComboBox *_themeComboBox{nullptr};
    ElaToggleSwitch *_micaSwitchButton{nullptr};
    ElaRadioButton *_minimumButton{nullptr};
    ElaRadioButton *_compactButton{nullptr};
    ElaRadioButton *_maximumButton{nullptr};
    ElaRadioButton *_autoButton{nullptr};
};

#endif // COMIC_H
