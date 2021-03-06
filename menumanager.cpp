#include "menumanager.h"

MenuManager::MenuManager(MysqlManager* sqlManager) :sqlManager(sqlManager)
{

}

void MenuManager::addMenu(const Menu& m)
{
	MYSQL* t = sqlManager->connect();
	for (auto i = m.getDishes().begin(); i != m.getDishes().end(); i++) {
		QString sql = QString::asprintf(
			"insert into dish_menu(d_id,numberofdish,o_ID) values('%d','%d','%d');"
			, i->first->getID(), i->second, m.getID()
		);
		int judge = mysql_query(t, sql.toStdString().c_str());
		if (judge) {
			const char* error = mysql_error(t);
			sqlManager->close(t);
			throw error;
		}
		sql = QString::asprintf(
			"update dish set sale = sale + % d WHERE id = % d; "
			, i->second, i->first->getID()
		);
		judge = mysql_query(t, sql.toStdString().c_str());
		if (judge) {
			const char* error = mysql_error(t);
			sqlManager->close(t);
			throw error;
		}
	}

	sqlManager->close(t);

}

void MenuManager::deleteMenu(Menu& m)
{
	MYSQL* t = sqlManager->connect();
	for (auto i = m.getDishes().begin(); i != m.getDishes().end(); i++) {
		QString sql = QString::asprintf(
			"delete from dish_menu where o_id='%d';"
			, m.getID()
		);
		int judge = mysql_query(t, sql.toStdString().c_str());
		if (judge) {
			const char* error = mysql_error(t);
			sqlManager->close(t);
			throw error;
		}
	}
	sqlManager->close(t);

}

void MenuManager::modifyMenu(Menu& m)
{
	deleteMenu(m);
	addMenu(m);
}



Menu& MenuManager::queryById(int o_id)
{
	Menu* menu = new Menu(o_id);
	MYSQL* t = sqlManager->connect();
	QString sql = QString::asprintf(
		"select * from dish_menu inner join dish on dish.ID=dish_menu.d_ID where o_id=%d;"
		, o_id
	);
	int judge = mysql_query(t, sql.toStdString().c_str());
	if (judge) {
		const char* error = mysql_error(t);
		sqlManager->close(t);
		throw error;
	}
	MYSQL_ROW row;
	MYSQL_RES* result = mysql_use_result(t);
	while ((row = mysql_fetch_row(result))) {
		if (row == NULL) throw "菜品为空";
		Dish* dish = new Dish(row[6], QString(row[4]).toDouble(), QString(row[5]).toDouble(), QString(row[7]).toInt(),QString(row[8]).toInt());
		menu->addDish(*dish, QString(row[1]).toInt());
		dish->setID(QString(row[0]).toInt());
	}
	menu->setID(o_id);

	sqlManager->close(t);
	return *menu;
}
