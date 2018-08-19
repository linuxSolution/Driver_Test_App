#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSql>


class Db_Manager
{
public:
    Db_Manager(const QString& path);
    static bool add_database(QString dbfile);
    static QString getEvent(QDateTime from, QDateTime to);
    static bool addEvent(const QString& event, const QString& desc);

    static bool addkey(const QString& key, const QString& value);
    static QString getKey(QString key);

    static bool readKey_b(QString s, bool def);
    static int  readKey(QString s, int def);
    static QString readKey(QString s, QString def);
    static void saveKey(QString s, QString val);
    static void saveKey(QString s, bool val);
    static void saveKey(QString s, int val);

};

#endif // DB_MANAGER_H

