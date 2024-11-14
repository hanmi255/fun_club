#ifndef MUSIC_H
#define MUSIC_H

#include "T_BasePage.h"
#include "DataBaseManager.h"
#include "spotifyapi.h"
#include <QLabel>

class QMediaPlayer;
class ElaTableView;
class Music : public T_BasePage {
    Q_OBJECT

public:
    Q_INVOKABLE explicit Music(QWidget *parent = nullptr);



private slots:
    void onSongClicked(const QModelIndex &index);
    void onSongFound(const QString &url);
    void onAuthenticationChanged();

Q_SIGNALS:
    void spotifyApiChanged();
    void error(const QString &errorString);

private:
    ElaTableView *tableView{ nullptr };
    QMediaPlayer *player{ nullptr };
    DataBaseManager *dbManager{ nullptr };
    SpotifyAPI *spotifyApi{ nullptr };
    QLabel *busyWidget{ nullptr };
};

#endif // MUSIC_H
