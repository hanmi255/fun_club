#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlTableModel>
#include "Result.h"

class DataBaseManager
{
public:
    DataBaseManager();
    Result connectToDatabase();
    Result enrollUser(const QString &username, const QString &password);
    Result loginUser(const QString &username, const QString &password);
    QSqlTableModel* getSongData();

private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
