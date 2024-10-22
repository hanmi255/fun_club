#include "mainwindow.h"

#include "UserLogin.h"
#include "About.h"
#include "Anime.h"
#include "Home.h"
#include "Setting.h"

MainWindow::MainWindow(QWidget* parent)
    : ElaWindow(parent)
{
    //初始化窗口
    initWindow();

    //额外布局
    initEdgeLayout();

    //中心窗口
    initContent();

    // 拦截默认关闭事件
    _closeDialog = new ElaContentDialog(this);
    connect(_closeDialog, &ElaContentDialog::rightButtonClicked, this, &MainWindow::closeWindow);
    connect(_closeDialog, &ElaContentDialog::middleButtonClicked, this, &MainWindow::showMinimized);
    this->setIsDefaultClosed(false);
    connect(this, &MainWindow::closeButtonClicked, this, [=]() {
        _closeDialog->exec();
    });

    // 连接登录成功信号
    connect(_userLoginPage, &UserLogin::loginSuccessful, this, &MainWindow::onLoginSuccessful);

    //移动到中心
    moveToCenter();
}

MainWindow::~MainWindow()
{
    delete this->_aboutPage;
    delete this->_userLoginPage;
    delete this->_homePage;
    delete this->_settingPage;
    delete this->_animePage;
    delete this->_closeDialog;
}

//登录成功
void MainWindow::onLoginSuccessful(const QString& userName)
{
    setUserInfoCardPixmap(QPixmap(":/include/Image/Cirno.jpg"));
    setUserInfoCardTitle(userName);
}

//初始化窗口
void MainWindow::initWindow()
{
    setWindowTitle("Library System");

    setWindowIcon(QIcon(":/include/Image/Cirno.jpg"));
    resize(1200, 740);

    _userLoginPage = new UserLogin();
    _userLoginPage->hide();
    connect(this, &ElaWindow::userInfoCardClicked, this, [=]() {
        _userLoginPage->setFixedSize(400, 400);
        _userLoginPage->moveToCenter();
        _userLoginPage->show();
    });

    setUserInfoCardPixmap(QPixmap(":/Image/Image/defaultHeadFrame.png"));
    setUserInfoCardTitle("未登录");
    setUserInfoCardSubTitle("这个人很懒，什么都没写~~~");
}

// 初始化边框
void MainWindow::initEdgeLayout()
{

}

//初始化内容
void MainWindow::initContent()
{
    _homePage = new Home(this);
    _animePage = new Anime(this);
    _settingPage = new Setting(this);

    addPageNode("首页", _homePage, ElaIconType::House);
    addPageNode("动画", _animePage, ElaIconType::CameraMovie);

    addFooterNode("关于我们", nullptr, _aboutKey, 0, ElaIconType::Angel);
    _aboutPage = new About();
    _aboutPage->hide();
    connect(this, &ElaWindow::navigationNodeClicked, this, [=](ElaNavigationType::NavigationNodeType nodeType, QString nodeKey) {
        if (_aboutKey == nodeKey)
        {
            _aboutPage->setFixedSize(400, 400);
            _aboutPage->moveToCenter();
            _aboutPage->show();
        }
    });

    addFooterNode("设置", _settingPage, _settingKey, 0, ElaIconType::GearComplex);
    connect(this, &MainWindow::userInfoCardClicked, this, [=]() { this->navigation(_homePage->property("ElaPageKey").toString()); });
    connect(_homePage, &Home::animeNavigation, this, [=](){ this->navigation(_animePage->property("ElaPageKey").toString());});

    qDebug() << "已注册的事件列表" << ElaEventBus::getInstance()->getRegisteredEventsName();
}
