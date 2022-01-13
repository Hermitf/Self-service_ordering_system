#ifndef DISHMANAGER_H
#define DISHMANAGER_H
#include <QString>
#include <iostream>
#include <vector>
#include"dish.h"
#include "MysqlManager.h"

using std::vector;

class DishManager {
	MysqlManager* sqlManager;
public:
	DishManager(MysqlManager* sqlManager);
	//增删改查
	void addDish(Dish& d);
	void deleteDish(int id);
	void modifyDishByID(Dish& d);
	void reserchDish(QString str);
	vector<Dish*>* queryByCategory(int cg);
	vector<Dish*>* queryAll();
};

#endif // DISHMANAGER_H
