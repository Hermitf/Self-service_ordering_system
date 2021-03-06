#include "ordermanager.h"
#include <QDateTime>
#include <QTextStream>
#include<vector>
#include <iostream>
#include"customer.h"

using std::vector;

OrderManager::OrderManager(MysqlManager* sqlManager) :sqlManager(sqlManager)
{

}

void OrderManager::addOrder(Order& o)
{
	MYSQL* t = sqlManager->connect();
	QString sql;	
	QTextStream(&sql) << "insert into order_(servicefeescale,diningstyle,peoplenumber,desknumber,deliverytime,c_id) values('"
		<< o.getServiceFeeScale()<<"','" << (o.getDiningStyle() ? 1 : 0) << "','" << o.getPeopleNumber() << "','" << o.getDeskNumber() << "',date_add(now(), interval 30 minute),'" << o.getC_id()<<"');SELECT @@Identity;";
	int judge = mysql_query(t, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(t);
		sqlManager->close(t);
		throw error;
	}

	MYSQL_ROW row;
	MYSQL_RES* res;
	do
	{
		res = mysql_store_result(t);
		if (res) break;
	} while (!mysql_next_result(t));

	row = mysql_fetch_row(res);
	int id=QString(row[0]).toInt();
	o.setID(id);
	o.setDeliverTime(getTime(o));
	sqlManager->close(t);
}

void OrderManager::deleteOrder(int o_ID)
{
	MYSQL* t = sqlManager->connect();
	QString sql = QString::asprintf(
		"delete from dish_menu where o_ID=%d; delete from order_ where id=%d;"
		, o_ID,o_ID
	);
	int judge = mysql_query(t, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(t);
		sqlManager->close(t);
		throw error;
	}
	sqlManager->close(t);
}

void OrderManager::modifyOrder(Order& o)
{
	MYSQL* t = sqlManager->connect();
	QString sql = QString::asprintf(
		"update order_ set id='%d' and servicefeescale='%lf' and diningstyle='%d' and peoplenumber='%d' and desknumber='%s' and c_id='%d';"
		, o.getID(), o.getServiceFeeScale(), o.getDiningStyle(), o.getDiningStyle(), o.getPeopleNumber(), o.getDeskNumber().toStdString().c_str(), o.getC_id()
	);
	int judge = mysql_query(t, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(t);
		sqlManager->close(t);
		throw error;
	}
	sqlManager->close(t);
}

QString OrderManager::getTime(Order& o)
{
	MYSQL* t = sqlManager->connect();
	QString sql;
	QTextStream(&sql) << "select deliverytime FROM order_ where id='"<<o.getID()<<"';";
	int judge = mysql_query(t, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(t);
		sqlManager->close(t);
		throw error;
	}
	MYSQL_ROW row;
	MYSQL_RES* res = mysql_use_result(t);
	row = mysql_fetch_row(res);
	QString time = QString(row[0]);

	sqlManager->close(t);
	return time;
}

void OrderManager::rearchByC_ID(int c_ID, int &o_ID,double &serviceFeeScale, bool &diningStyle, QString &deskNumber, QString &time)
{
	MYSQL* m = sqlManager->connect();

	QString sql;
	QTextStream(&sql) << "SELECT ID,servicefeescale,diningstyle,desknumber,deliverytime FROM order_ WHERE c_id='" << c_ID << "';";
	int judge = mysql_query(m, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(m);
		sqlManager->close(m);
		throw error;
	}
	MYSQL_ROW row;
	MYSQL_RES* res = mysql_use_result(m);
	row = mysql_fetch_row(res);
	if (row == NULL) throw "未查询到订单";
	o_ID = QString(row[0]).toInt();
	serviceFeeScale = QString(row[1]).toDouble();
	diningStyle = QString(row[2]).toInt()!=0;
	deskNumber = QString(row[3]);
	time = QString(row[4]);
	sqlManager->close(m);

}



vector<Order*>* OrderManager::rearchAll(vector<int>* o_ID, vector<int>*c_ID)
{
	vector<Order*>* orders=new vector<Order*>;
	MYSQL* m = sqlManager->connect();

	QString sql;
	QTextStream(&sql) << "SELECT * FROM order_ ;";
	int judge = mysql_query(m, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(m);
		sqlManager->close(m);
		throw error;
	}
	MYSQL_ROW row;
	MYSQL_RES* result = mysql_use_result(m);
	while ((row = mysql_fetch_row(result))) {
		orders->push_back(new Order((QString(row[2]).toInt() != 0), 0, QString(row[4]), QString(row[5]), 0));
		c_ID ->push_back( QString(row[6]).toInt());
		o_ID->push_back(QString(row[0]).toInt());
	}

	sqlManager->close(m);
	return orders;
}


vector<Order*>* OrderManager::rearchByTime(QString time, vector<int>* o_ID, vector<int>* c_ID)
{
	vector<Order*>* orders = new vector<Order*>;
	MYSQL* m = sqlManager->connect();

	QString sql;
	QTextStream(&sql) << "SELECT * FROM order_ WHERE deliverytime like '" << time << "%';";
	int judge = mysql_query(m, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(m);
		sqlManager->close(m);
		throw error;
	}
	MYSQL_ROW row;
	MYSQL_RES* result = mysql_use_result(m);
	while ((row = mysql_fetch_row(result))) {
		orders->push_back(new Order((QString(row[2]).toInt() != 0), 0, QString(row[4]), QString(row[5]), 0));
		c_ID->push_back(QString(row[6]).toInt());
		o_ID->push_back(QString(row[0]).toInt());
	}

	sqlManager->close(m);
	return orders;
}


vector<int>* OrderManager::rearchByC_ID()
{
	vector<int>* IDs = new vector<int>;
	MYSQL* m = sqlManager->connect();

	QString sql;
	QTextStream(&sql) << "SELECT c_id FROM order_ WHERE deliverytime like '" << time << "%';";
	int judge = mysql_query(m, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(m);
		sqlManager->close(m);
		throw error;
	}
	MYSQL_ROW row;
	MYSQL_RES* result = mysql_use_result(m);
	while ((row = mysql_fetch_row(result))) {
		IDs->push_back(QString(row[0]).toInt());

	}

	sqlManager->close(m);
	return IDs;
}