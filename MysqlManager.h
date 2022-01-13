#ifndef CONNECTMYSQL_H
#define CONNECTMYSQL_H
#include <mysql.h>
#include <string>

using std::string;

class MysqlManager
{
	string host;
	string user;
	string psw;
	string schema;
	int port = 0;
public:
	MysqlManager();
	MYSQL* connect();
	void close(MYSQL* mysql);

};

#endif // CONNECTMYSQL_H
