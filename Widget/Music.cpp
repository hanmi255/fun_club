#include "Music.h"

#include <QVBoxLayout>
#include <QHeaderView>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <ElaTableView.h>
#include <ElaMessageBar.h>
#include <ElaLineEdit.h>
#include <QPushButton>

Music::Music(QWidget *parent) :
    _tableView(new ElaTableView(this)),
    player(new QMediaPlayer(this)),
    audiooutput(new QAudioOutput(this)),
    dbManager(new DataBaseManager())
    // spotifyApi(new SpotifyAPI())
{
    currentSongUrl = "";  // 初始化当前歌曲路径为空
    // connect(spotifyApi, &SpotifyAPI::isAuthenticatedChanged, this, &Music::onAuthenticationChanged);

    //// 初始化Spotify的API
    // spotifyApi->setCredentials();
    // spotifyApi->authorize();

    // 设置中央布局
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Music");
    QVBoxLayout *centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(0, 0, 0, 0);
    centerLayout->setSpacing(20);

    // // 忙碌加载页
    // busyWidget = new QLabel("Loading...", centralWidget);
    // busyWidget->setAlignment(Qt::AlignCenter);
    // centerLayout->addWidget(busyWidget);

    // 获取数据
    Result result = dbManager->connectToDatabase();
    if (result.getStatus() == Result::Failure) {
        ElaMessageBar::error(ElaMessageBarType::Top, "ERROR!", result.getMessage(), 500, this);
    }
    model = dbManager->getSongData();
    QFont tableHeaderFont = _tableView->horizontalHeader()->font();
    tableHeaderFont.setPixelSize(16);
    _tableView->horizontalHeader()->setFont(tableHeaderFont);
    _tableView->setModel(model);
    _tableView->setAlternatingRowColors(true);
    _tableView->setIconSize(QSize(38, 38));
    _tableView->verticalHeader()->setHidden(true);
    _tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    _tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    _tableView->horizontalHeader()->setMinimumSectionSize(60);
    _tableView->verticalHeader()->setMinimumSectionSize(46);
    _tableView->setFixedHeight(600);

    connect(_tableView, &ElaTableView::tableViewShow, this, [=]() {
        _tableView->setColumnWidth(0, 250);
        _tableView->setColumnWidth(1, 210);
        _tableView->setColumnWidth(2, 250);
        _tableView->setColumnWidth(3, 50);
        _tableView->setColumnWidth(4, 60);
    });
    _tableView->setColumnHidden(4, true); // 隐藏文件路径列

    connect(_tableView, &ElaTableView::clicked, this, &Music::onSongClicked);

    // 搜索歌曲或歌手
    _searchEdit = new ElaLineEdit(this);
    _searchEdit->setPlaceholderText("搜索歌曲或歌手");
    _searchEdit->setFixedSize(300, 35);
    connect(_searchEdit, &ElaLineEdit::textEdited, this, &Music::onSearchEditTextEdit);
    connect(_searchEdit, &ElaLineEdit::focusIn, this, &Music::onSearchEditTextEdit);

    centerLayout->addWidget(_searchEdit);
    centerLayout->addWidget(_tableView);
    centerLayout->addStretch();
    // _tableView->setVisible(false);
    addCentralWidget(centralWidget, true, true, 0);
}

// 点击歌曲后播放或暂停
void Music::onSongClicked(const QModelIndex &index) {
    QString songName = _tableView->model()->index(index.row(), 0).data().toString();
    QString url = AppPath + _tableView->model()->index(index.row(), 4).data().toString();

    if (currentSongUrl != url) {
        // 如果与当前播放的歌曲不同，切换新歌曲并播放
        currentSongUrl = url;
        qDebug() << "切换播放:" << songName << "路径:" << url;
        playMusic(url);
    } else {
        // 如果是同一首歌，则根据状态进行播放或暂停
        if (player->playbackState() == QMediaPlayer::PlayingState) {
            qDebug() << "暂停播放:" << songName;
            player->pause();
        } else {
            qDebug() << "继续播放:" << songName;
            player->play();
        }
    }
}

// 播放音乐
void Music::playMusic(const QString &url) {
    //将音频输出设备与player对象关联
    if(!url.isEmpty()){
        player->setAudioOutput(audiooutput);
        player->setSource(QUrl(url));
        player->play();
        player->isPlaying();
    }
    else{
        qDebug() << "文件不存在";
    }
}

// 暂停音乐
void Music::pauseMusic() {
    if(player->isPlaying()){
        player->pause();
    }
}

// void Music::onAuthenticationChanged()
// {
//     if (spotifyApi->isAuthenticated()) {
//         busyWidget->setVisible(false);
//         _tableView->setVisible(true);
//     }
// }

void Music::onSearchEditTextEdit(const QString &searchText)
{
    if (searchText.isEmpty()) {
        // 没有输入时显示所有数据
        model->setFilter(""); // 清空过滤条件
        _tableView->clearSelection();
        _tableView->viewport()->update();
        return;
    }

    QString searchEscaped = searchText;
    searchEscaped.replace("'", "''");  // 转义单引号以防止SQL注入

    // 检索歌曲数据并更新视图
    QString filterText = QString("title LIKE '%%1%' OR artist LIKE '%%1%'").arg(searchEscaped);

    model->setFilter(filterText); // 设置筛选条件
    _tableView->clearSelection();
    _tableView->scrollTo(model->index(0, 0));
    _tableView->viewport()->update();
}
