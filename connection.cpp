#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projet");
db.setUserName("mouadh");//inserer nom de l'utilisateur
db.setPassword("mouadh2001");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
