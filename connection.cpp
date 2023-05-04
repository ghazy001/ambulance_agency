#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("integ");
db.setUserName("ghazi");//inserer nom de l'utilisateur
db.setPassword("ghazi2001");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
