#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QStatusBar>
#include <QVBoxLayout>

#include <ElaWindow.h>
#include <ElaContentDialog.h>
#include <ElaDockWidget.h>
#include <ElaEventBus.h>
#include <ElaLog.h>
#include <ElaMenu.h>
#include <ElaMenuBar.h>
#include <ElaProgressBar.h>
#include <ElaStatusBar.h>
#include <ElaText.h>
#include <ElaToolBar.h>
#include <ElaToolButton.h>

class UserLogin;
class About;
class Anime;
class Comic;
class Game;
class Music;
class Home;
class Setting;
class MainWindow : public ElaWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initWindow();
    void initEdgeLayout();
    void initContent();

private:
    ElaContentDialog *_closeDialog{ nullptr };
    Home *_homePage{ nullptr };
    About *_aboutPage{ nullptr };
    Anime *_animePage{ nullptr };
    Comic *_comicPage{ nullptr };
    Music *_musicPage{ nullptr };
    Game *_gamePage{ nullptr };
    Setting *_settingPage{ nullptr };
    UserLogin *_userLoginPage{ nullptr };

    QString _aboutKey{ "" };
    QString _settingKey{ "" };

private slots:
    void onLoginSuccessful(const QString &userName);
};
#endif // MAINWINDOW_H
