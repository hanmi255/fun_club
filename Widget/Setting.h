#ifndef T_SETTING_H
#define T_SETTING_H

#include "T_BasePage.h"
class ElaRadioButton;
class ElaToggleSwitch;
class ElaComboBox;
class Setting : public T_BasePage
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit Setting(QWidget* parent = nullptr);
    ~Setting();

private:
    ElaComboBox* _themeComboBox{nullptr};
    ElaToggleSwitch* _micaSwitchButton{nullptr};
    ElaRadioButton* _minimumButton{nullptr};
    ElaRadioButton* _compactButton{nullptr};
    ElaRadioButton* _maximumButton{nullptr};
    ElaRadioButton* _autoButton{nullptr};
};

#endif // T_SETTING_H
