#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("source_projet2a");
db.setUserName("iheb");//inserer nom de l'utilisateur
db.setPassword("iheb2001");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
