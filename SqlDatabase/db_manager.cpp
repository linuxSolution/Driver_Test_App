#include "db_manager.h"
#include <QFile>
#include <QTextStream>

bool Db_Manager::add_database(QString dbfile)
{
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbfile);
    return true;
}

bool Db_Manager::addkey(const QString& key, const QString& value)
{

        bool success = false;
        QSqlDatabase m_db = QSqlDatabase::database();

        if(m_db.open())
        {
            QSqlQuery query;

            query.prepare("REPLACE INTO keys (key,value) VALUES (:key,:value)");
            query.bindValue(":key", key);
            query.bindValue(":value", value);
            if(query.exec()){
                success = true;
            }
            else{
                qDebug() << "Insert Error:" << query.lastError();
            }

            m_db.close();
            //mutex.unlock();
            return success;
       }
       else{
           qDebug() << "Error: connection with database failed" << endl;
       }
       return false;
}

QString Db_Manager::getKey(QString key)
{
    QSqlDatabase m_db = QSqlDatabase::database();

    if(m_db.open())
    {

     QSqlQuery query;
     QString r;

     query.prepare("SELECT key, value FROM keys WHERE key = (:key)");
     query.bindValue(":key", key);

     if(query.exec())
     {
        int idName = query.record().indexOf("value");
        if (query.next())
        {
            r = query.value(idName).toString();
        }
     }     

     m_db.close();
     return r;
    }
    else{
      qDebug() << "Error: connection with database failed";
    }
    return QString::null;
}

int Db_Manager::readKey(QString s, int def)
{
       QString str;

       if((str  = getKey(s))!= NULL){
            return str.toInt();
       }
       else {
           addkey(s,QString::number(def));
           return def;
       }
}

QString Db_Manager::readKey(QString s, QString def)
{
       QString str;

       if((str  = getKey(s))!= NULL){
            return str;
       }
       else {
           addkey(s,def);
           return def;
       }
}

void Db_Manager::saveKey(QString s, QString val){
    addkey(s,val);
}

void Db_Manager::saveKey(QString s, bool val){

    addkey(s,QString::number(val));
}

void Db_Manager::saveKey(QString s, int val){

    addkey(s,QString::number(val));
}


