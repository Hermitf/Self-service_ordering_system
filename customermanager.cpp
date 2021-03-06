#include "customermanager.h"
#include <QTextStream>

CustomerManager::CustomerManager(MysqlManager* sqlManager) :sqlManager(sqlManager)
{

}

void CustomerManager::addCustomer(Customer& c)
{
	MYSQL* m = sqlManager->connect();
	QString sql = QString::asprintf(
		"insert into customer(name_,phone,address) values('%s','%s','%s');SELECT @@Identity;"
		, c.getName().toStdString().c_str(), c.getPhone().toStdString().c_str(), c.getAddress().toStdString().c_str()
	);
	int judge = mysql_query(m, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(m);
		sqlManager->close(m);
		throw error;
	}
	MYSQL_ROW row;
	MYSQL_RES* res; //查询结果
	do
	{
		res = mysql_store_result(m);
		if (res) break;
	} while (!mysql_next_result(m));

	row = mysql_fetch_row(res);
	int id = QString(row[0]).toInt();
	c.setID(id);
	mysql_free_result(res);
	sqlManager->close(m);

}

void CustomerManager::deleteCustomer(Customer& c)
{
	MYSQL* m = sqlManager->connect();
	QString sql = QString::asprintf(
		"delete from customer where id=='%d';"
		, c.getID()
	);
	int judge = mysql_query(m, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(m);
		sqlManager->close(m);
		throw error;
	}
	sqlManager->close(m);

}

void CustomerManager::modifyCustomer(Customer& c)
{
	MYSQL* m = sqlManager->connect();
	QString sql = QString::asprintf(
		"update customer set id=='%d' and name_=='%s' and phone=='%s' and address=='%s';"
		, c.getID(), c.getName().toStdString().c_str(), c.getPhone().toStdString().c_str(), c.getAddress().toStdString().c_str()
	);
	int judge = mysql_query(m, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(m);
		sqlManager->close(m);
		throw error;
	}
	sqlManager->close(m);

}

void CustomerManager::reserchDish(QString str)
{
	MYSQL* m = sqlManager->connect();
	QString sql = QString::asprintf(
		"select * from customer where id like'%%%s%%'|| name_ like'%%%s%%'|| phone like'%%%s%%'|| address like'%%%s%%'"
		, str.toStdString().c_str(), str.toStdString().c_str(), str.toStdString().c_str(), str.toStdString().c_str()
	);
	int judge = mysql_query(m, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(m);
		sqlManager->close(m);
		throw error;
	}
	sqlManager->close(m);

}

void CustomerManager::reserchByNameAndPhone(QString name,QString phone, QString& address, int& c_ID)
{	
	MYSQL* m = sqlManager->connect();

	QString sql;
	QTextStream(&sql) << "SELECT address,ID FROM customer WHERE name_='" <<name<< "' and phone='" <<phone<< "';";
	int judge = mysql_query(m, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(m);
		sqlManager->close(m);
		throw error;
	}
	MYSQL_ROW row;
	MYSQL_RES* res = mysql_use_result(m);
	row = mysql_fetch_row(res);
	if (row == NULL) throw "未查询到此人";
	address = QString(row[0]);
	c_ID = QString(row[1]).toInt();
	sqlManager->close(m);
	

}

Customer* CustomerManager::reserchByID(int c_ID)
{	
	MYSQL* m = sqlManager->connect();

	QString sql;
	QTextStream(&sql) << "SELECT * FROM customer WHERE id=" <<c_ID<< ";";
	int judge = mysql_query(m, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(m);
		sqlManager->close(m);
		throw error;
	}
	MYSQL_ROW row;
	MYSQL_RES* res = mysql_use_result(m);
	row = mysql_fetch_row(res);
	if (row == NULL) throw "未查询到此人";
	Customer* cus = new Customer(QString(row[0]),QString(row[1]),QString(row[2]));
	sqlManager->close(m);
	return cus;
}
