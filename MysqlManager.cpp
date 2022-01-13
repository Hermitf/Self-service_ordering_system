#include "MysqlManager.h"
#include<iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::ios;

MysqlManager::MysqlManager()
{
	//读文件中的数据
	ifstream myFile("connectionInfo.txt", ios::in);
	if (!myFile.is_open()) {
		throw "File open fail!";
	}
	myFile >> host >> user >> psw >> schema >> port;

}

MYSQL* MysqlManager::connect()
{
	MYSQL* mysql = new MYSQL();
	mysql_init(mysql);
	if (!(mysql_real_connect(mysql, host.c_str(), user.c_str(), psw.c_str(), schema.c_str(), port, NULL, CLIENT_MULTI_STATEMENTS))) {
		throw mysql_error(mysql);
	}
	else {
		return mysql;
	}
}

void MysqlManager::close(MYSQL* mysql)
{
	mysql_close(mysql);
}
