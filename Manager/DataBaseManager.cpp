#include "DataBaseManager.h"

// 数据库配置
DataBaseManager::DataBaseManager() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("123fun_club");
    db.setUserName("root");
    db.setPassword("miHoYo4869384");
}

// 连接到数据库
Result DataBaseManager::connectToDatabase() {
    if (db.open()) {
        return Result(Result::Success, "数据库连接成功");
    } else {
        return Result(Result::Failure, db.lastError().text());
    }
}

// 注册
Result DataBaseManager::enrollUser(const QString &username, const QString &password) {
    QSqlQuery query;

    // 检查用户名是否已存在
    query.prepare("SELECT COUNT(*) FROM user WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        return Result(Result::Failure, "查询错误" + query.lastError().text());
    }

    if (query.next() && query.value(0).toInt() > 0) {
        return Result(Result::Failure, "用户名已存在");
    }

    // 插入新用户
    query.prepare("INSERT INTO user (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec()) {
        return Result(Result::Success, "注册成功");
    } else {
        return Result(Result::Failure, query.lastError().text());
    }
}


// 登录
Result DataBaseManager::loginUser(const QString &username, const QString &password) {
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        return Result(Result::Success, "登录成功");
    } else {
        return Result(Result::Failure, "用户名或密码错误");
    }
}

// 获取歌曲数据
QStandardItemModel *DataBaseManager::getSongData() {
    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderLabels({"歌曲名称", "歌手", "专辑", "时长", "文件路径"});

    QSqlQuery query("SELECT title, artist, album, duration, file_path FROM songs");

    while (query.next()) {
        QList<QStandardItem *> items;
        for (int i = 0; i < query.record().count(); ++i) {
            items.append(new QStandardItem(query.value(i).toString()));
        }
        model->appendRow(items);
    }

    return model;
}
