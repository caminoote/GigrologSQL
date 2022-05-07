#include "riverlistsql.h"
#include "QObject"

riverlistsql::riverlistsql(QObject *parent) :
    QSqlQueryModel(parent)
{

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./RiverDB.db");


     _isConnectionOpen = true;

    if(!db.open())
    {
        qDebug() << db.lastError().text();
        _isConnectionOpen = false;
    }


    QSqlQuery qry(db);
    qry.prepare("CREATE TABLE IF NOT EXISTS RiverList (Id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT, nameOfRiver text, lenghtOfRiver text, flowOfRiver text,runoffOfRiver text, areaOfRiver text, Id_river integer)");
    if( !qry.exec() )
    {
        qDebug() << db.lastError().text();
        _isConnectionOpen = false;
    }

    refresh();
}

QSqlQueryModel* riverlistsql::getModel(){
    return this;
}
bool riverlistsql::isConnectionOpen(){
    return _isConnectionOpen;
}
QHash<int, QByteArray> riverlistsql::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole + 1] = "nameOfRiver";
    roles[Qt::UserRole + 2] = "lenghtOfRiver";
    roles[Qt::UserRole + 3] = "flowOfRiver";
    roles[Qt::UserRole + 4] = "runoffOfRiver";
    roles[Qt::UserRole + 5] = "areaOfRiver";
    roles[Qt::UserRole + 6] = "Id";
    return roles;
}


QVariant riverlistsql::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    if(role < Qt::UserRole-1)
    {
        value = QSqlQueryModel::data(index, role);
    }
    else
    {
        int columnIdx = role - Qt::UserRole - 1;
        QModelIndex modelIndex = this->index(index.row(), columnIdx);
        value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
    }
    return value;
}

const char* riverlistsql::SQL_SELECT =
        "SELECT nameOfRiver,lenghtOfRiver,flowOfRiver,runoffOfRiver,areaOfRiver, Id"
        " FROM RiverList";

void riverlistsql::refresh()
{
    this->setQuery(riverlistsql::SQL_SELECT,db);
}

void riverlistsql::add(const QString& nameRiv, const QString& lenghtRiv, const QString& flowRiv, const QString& runoffRiv, const QString& areaRiv){

    QSqlQuery query(db);
    QString phQuery= QString("INSERT INTO RiverList (nameOfRiver,lenghtOfRiver,flowOfRiver,runoffOfRiver,areaOfRiver) VALUES ('%1', '%2', '%3', '%4', '%5')")
            .arg(nameRiv)
            .arg(lenghtRiv)
            .arg(flowRiv)
            .arg(runoffRiv)
            .arg(areaRiv);
    query.exec(phQuery);

    refresh();

}

void riverlistsql::edit(const QString& nameRiv, const QString& lenghtRiv, const QString& flowRiv, const QString& runoffRiv, const QString& areaRiv, const int index){

    QSqlQuery query(db);
    QString phQuery= QString("UPDATE RiverList SET nameOfRiver = '%1',lenghtOfRiver = '%2',flowOfRiver = %3, runoffOfRiver = %4, areaOfRiver = %5, WHERE Id = %6")
            .arg(nameRiv)
            .arg(lenghtRiv)
            .arg(flowRiv)
            .arg(runoffRiv)
            .arg(areaRiv)
            .arg(index);
    query.exec(phQuery);

    refresh();

}
void riverlistsql::del(const int Id){


    QSqlQuery query(db);
    QString strQuery= QString("DELETE FROM RiverList WHERE Id = %1")
            .arg(Id);
    query.exec(strQuery);

    refresh();
}

QString riverlistsql::count(const QString& textCount){

    QSqlQuery query(db);
    QString phQuery= QString("SELECT COUNT (Id) FROM RiverList WHERE circulation <= %1")
            .arg(textCount.toInt());
    query.exec(phQuery);

    QString info;
    while(query.next())
    {
        info = query.value(0).toString();

    }
    return(info);

}
