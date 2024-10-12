#include "About.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QVBoxLayout>

#include <ElaImageCard.h>
#include <ElaText.h>
About::About(QWidget* parent): ElaWidget(parent)
{
    setWindowTitle("关于我们");
    setWindowIcon(QIcon(":/include/Image/Moon.jpg"));
    this->setIsFixedSize(true);
    setWindowModality(Qt::ApplicationModal);
    setWindowButtonFlags(ElaAppBarType::CloseButtonHint);
    ElaImageCard* pixCard = new ElaImageCard(this);
    pixCard->setFixedSize(60, 60);
    pixCard->setIsPreserveAspectCrop(false);
    pixCard->setCardImage(QImage(":/include/Image/Moon.jpg"));

    QVBoxLayout* pixCardLayout = new QVBoxLayout();
    pixCardLayout->addWidget(pixCard);
    pixCardLayout->addStretch();

    ElaText* loginLabel = new ElaText("LibrarySystem", this);
    QFont loginLabelFont = loginLabel->font();
    loginLabelFont.setWeight(QFont::Bold);
    loginLabel->setFont(loginLabelFont);
    loginLabel->setWordWrap(false);
    loginLabel->setTextPixelSize(18);

    ElaText* licenseText = new ElaText("MIT授权协议", this);
    licenseText->setWordWrap(false);
    licenseText->setTextPixelSize(14);
    ElaText* supportText = new ElaText("Windows支持版本: Qt5.12以上\nLinux支持版本: Qt5.14以上", this);
    supportText->setWordWrap(false);
    supportText->setTextPixelSize(14);
    ElaText* contactText = new ElaText("作者: hanmi", this);
    contactText->setWordWrap(false);
    contactText->setTextInteractionFlags(Qt::TextSelectableByMouse);
    contactText->setTextPixelSize(14);
    ElaText* copyrightText = new ElaText("版权所有 © 2024 HANMI", this);
    copyrightText->setWordWrap(false);
    copyrightText->setTextPixelSize(14);

    QVBoxLayout* textLayout = new QVBoxLayout();
    textLayout->setSpacing(15);
    textLayout->addWidget(loginLabel);
    textLayout->addWidget(licenseText);
    textLayout->addWidget(supportText);
    textLayout->addWidget(contactText);
    textLayout->addWidget(copyrightText);
    textLayout->addStretch();

    QHBoxLayout* contentLayout = new QHBoxLayout();
    contentLayout->addSpacing(30);
    contentLayout->addLayout(pixCardLayout);
    contentLayout->addSpacing(30);
    contentLayout->addLayout(textLayout);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 25, 0, 0);
    mainLayout->addLayout(contentLayout);
}

About::~About()
{
}
