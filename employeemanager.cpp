#include "employeemanager.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

EmployeeManager::EmployeeManager(MysqlManager* sqlManager) :sqlManager(sqlManager)
{

}

void EmployeeManager::addEmployee(const Employee& e)
{
	MYSQL* m = sqlManager->connect();
	QString sql = QString::asprintf(
		"insert into manager(worknumber,password) values('%s','%s');"
		, e.getWorkNumber().toStdString().c_str(), e.getPassword().toStdString().c_str()
	);
	int judge = mysql_query(m, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(m);
		sqlManager->close(m);
		throw error;
	}
	sqlManager->close(m);
}

void EmployeeManager::deleteEmployee(Employee& e)
{
	MYSQL* m = sqlManager->connect();
	QString sql = QString::asprintf(
		"delete from manager where worknumber='%s';"
		, e.getWorkNumber().toStdString().c_str()
	);
	int judge = mysql_query(m, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(m);
		sqlManager->close(m);
		throw error;
	}
	sqlManager->close(m);

}

void EmployeeManager::modifyEmployee(Employee& e)
{
	MYSQL* m = sqlManager->connect();
	QString sql = QString::asprintf(
		"update manager set worknumber='%s' and password='%s';"
		, e.getWorkNumber().toStdString().c_str(), e.getPassword().toStdString().c_str()
	);
	int judge = mysql_query(m, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(m);
		sqlManager->close(m);
		throw error;
	}
	sqlManager->close(m);

}

void EmployeeManager::reserchEmployee(QString str)
{
	MYSQL* m = sqlManager->connect();
	QString sql = QString::asprintf(
		"select * from manager where worknumber like '%%%s%%' and password like '%%%s%%';"
		, str.toStdString().c_str(), str.toStdString().c_str()
	);
	int judge = mysql_query(m, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(m);
		sqlManager->close(m);
		throw error;
	}
	sqlManager->close(m);

}

bool EmployeeManager::logIn(QString workNumber, QString passWord)
{
	MYSQL* m = sqlManager->connect();
	QString sql = QString::asprintf(
		"select * from manager where worknumber='%s' and password='%s';"
		, workNumber.toStdString().c_str(), passWord.toStdString().c_str()
	);
	if (mysql_query(m, sql.toStdString().c_str())) {
		throw "读取失败";
	}
	else {
		MYSQL_RES* result = mysql_store_result(m);
		if (result != NULL) {
			int l = mysql_num_rows(result);
			if (l == 1) return true;
			else return false;
		}
		else throw "读取失败";
	}

}

bool EmployeeManager::register_(QString workNumber, QString password, QString passwordAgain)
{
	if (password != passwordAgain) throw "Input the different password!";
	addEmployee(Employee(workNumber, password));
	return true;
}
