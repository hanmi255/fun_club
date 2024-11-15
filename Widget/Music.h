#ifndef MUSIC_H
#define MUSIC_H

#include "T_BasePage.h"
#include "DataBaseManager.h"
// #include "spotifyapi.h"
#include <QLabel>
#define AppPath QCoreApplication::applicationDirPath()

class QMediaPlayer;
class QAudioOutput;
class ElaTableView;
class ElaLineEdit;
class Music : public T_BasePage {
    Q_OBJECT

public:
    Q_INVOKABLE explicit Music(QWidget *parent = nullptr);
    void playMusic(const QString &url);
    void pauseMusic();

private slots:
    void onSongClicked(const QModelIndex &index);
    // void onAuthenticationChanged();
    void onSearchEditTextEdit(const QString& searchText);

Q_SIGNALS:
    // void spotifyApiChanged();
    void error(const QString &errorString);

private:
    ElaTableView *_tableView{ nullptr };
    ElaLineEdit *_searchEdit{ nullptr };
    QMediaPlayer *player{ nullptr };
    QAudioOutput *audiooutput{ nullptr };
    DataBaseManager *dbManager{ nullptr };
    // SpotifyAPI *spotifyApi{ nullptr };
    QLabel *busyWidget{ nullptr };
    QSqlTableModel *model;
    QString currentSongUrl;
};

#endif // MUSIC_H
