#include "Music.h"

#include <QVBoxLayout>
#include <QHeaderView>
#include <QMediaPlayer>
#include <ElaTableView.h>
#include <ElaMessageBar.h>

Music::Music(QWidget *parent) :
    tableView(new ElaTableView(this)),
    player(new QMediaPlayer(this)),
    dbManager(new DataBaseManager()),
    spotifyApi(new SpotifyAPI())

{
    connect(spotifyApi, &SpotifyAPI::isAuthenticatedChanged, this, &Music::onAuthenticationChanged);

    // 初始化Spotify的API
    spotifyApi->setCredentials();
    spotifyApi->authorize();

    // 设置中央布局
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Music");
    QVBoxLayout *centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(0, 0, 0, 0);
    centerLayout->setSpacing(20);

    // 忙碌指示器
    busyWidget = new QLabel("Loading...", centralWidget);
    busyWidget->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(busyWidget);

    Result result = dbManager->connectToDatabase();
    if (result.getStatus() == Result::Failure) {
        ElaMessageBar::error(ElaMessageBarType::Top, "ERROR!", result.getMessage(), 500, this);
    }
    QStandardItemModel *model = dbManager->getSongData();
    tableView->setModel(model);
    tableView->setColumnHidden(4, true); // 隐藏文件路径列
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(tableView, &QTableView::clicked, this, &Music::onSongClicked);


    centerLayout->addWidget(tableView);
    tableView->setVisible(false);
    addCentralWidget(centralWidget, true, true, 0);
}

void Music::onSongClicked(const QModelIndex &index) {
    QString songName = tableView->model()->index(index.row(), 0).data().toString();

}

void Music::onSongFound(const QString &url) {
    if (!url.isEmpty()) {
        player->setSource(QUrl(url));
        player->play();
    }
}

void Music::onAuthenticationChanged()
{
    if (spotifyApi->isAuthenticated()) {
        busyWidget->setVisible(false);
        tableView->setVisible(true);
    }
}
