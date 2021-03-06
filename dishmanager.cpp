#include "dishmanager.h"


DishManager::DishManager(MysqlManager* sqlManager) :sqlManager(sqlManager)
{

}


void DishManager::addDish(Dish& d)
{
	MYSQL* m = sqlManager->connect();
	QString sql = QString::asprintf(
		"insert into dish(originalprice,discountedprice,dishname,sale,category) values(%lf,%lf,'%s',%d,%d);SELECT @@Identity;"
		,  d.getOriginalPrice(), d.getDiscountedPrice(), d.getProductName().toStdString().c_str(), d.getSale(),d.getCategory()
	);
	int judge = mysql_query(m, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(m);
		sqlManager->close(m);
		throw error;
	}

	MYSQL_ROW row;
	MYSQL_RES* res;
	do
	{
		res = mysql_store_result(m);
		if (res) break;
	} while (!mysql_next_result(m));

	row = mysql_fetch_row(res);
	int id = QString(row[0]).toInt();
	d.setID(id);
	sqlManager->close(m);
}

void DishManager::deleteDish(int id)
{
	MYSQL* m = sqlManager->connect();
	QString sql = QString::asprintf(
		"delete from dish where id=%d;"
		, id
	);
	int judge = mysql_query(m, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(m);
		sqlManager->close(m);
		throw error;
	}
	sqlManager->close(m);
}

void DishManager::modifyDishByID(Dish& d)
{
	MYSQL* m = sqlManager->connect();
	QString sql = QString::asprintf(
		"update dish set originalprice=%f, discountedprice=%f, dishname='%s', sale=%d, category=%d where id=%d;"
		, d.getOriginalPrice(), d.getDiscountedPrice(), d.getProductName().toStdString().c_str(), d.getSale(),d.getCategory(), d.getID()
	);
	int judge = mysql_query(m, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(m);
		sqlManager->close(m);
		throw error;
	}
	sqlManager->close(m);
}

void DishManager::reserchDish(QString str)
{
	MYSQL* m = sqlManager->connect();
	QString sql = QString::asprintf(
		"select * from dish where id like'%%%s%%'|| originalprice like'%%%s%%'|| discountedprice like'%%%s%%'|| dishname like'%%%s%%'|| sale like'%%%s%%'"
		, str.toStdString().c_str(), str.toStdString().c_str(), str.toStdString().c_str(), str.toStdString().c_str(), str.toStdString().c_str()
	);
	int judge = mysql_query(m, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(m);
		sqlManager->close(m);
		throw error;
	}
	sqlManager->close(m);
}

vector<Dish*>* DishManager::queryByCategory(int cg)
{
	vector<Dish*>* dishes = new vector<Dish*>;
	MYSQL* t = sqlManager->connect();
	QString sql = QString::asprintf(
		"select * from dish where category=%d;"
		, cg
	);
	int judge = mysql_query(t, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(t);
		sqlManager->close(t);
		throw error;//TODO 接异常
	}
	MYSQL_ROW row;
	MYSQL_RES* res = mysql_use_result(t);
	while((row = mysql_fetch_row(res))) {
		Dish* dish = new Dish(row[3], QString(row[1]).toDouble(), QString(row[2]).toDouble(), QString(row[4]).toInt(), QString(row[5]).toInt());
		dish->setID(QString(row[0]).toInt());
		dishes->push_back(dish);
	}
	sqlManager->close(t);
	return dishes;
}

vector<Dish*>* DishManager::queryAll()
{
	vector<Dish*>* dishes = new vector<Dish*>;
	MYSQL* t = sqlManager->connect();
	QString sql = QString::asprintf(
		"select * from dish;"
	);
	int judge = mysql_query(t, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(t);
		sqlManager->close(t);
		throw error;//TODO 接异常
	}
	MYSQL_ROW row;
	MYSQL_RES* res = mysql_use_result(t);
	while((row = mysql_fetch_row(res))) {
		Dish* dish = new Dish(row[3], QString(row[1]).toDouble(), QString(row[2]).toDouble(), QString(row[4]).toInt(), QString(row[5]).toInt());
		dish->setID(QString(row[0]).toInt());
		
		dishes->push_back(dish);
	}
	sqlManager->close(t);
	return dishes;
}
