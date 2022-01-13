#ifndef CUSTOMERMANAGER_H
#define CUSTOMERMANAGER_H
#include "MysqlManager.h"
#include "customer.h"
#include <QString>
#include "dish.h"
#include<iostream>
#include <map>

using std::map;

class CustomerManager
{
	MysqlManager* sqlManager;
public:
	CustomerManager(MysqlManager* sqlManager);
	//对于顾客进行增删改查
	void addCustomer(Customer& c);
	void deleteCustomer(Customer& c);
	void modifyCustomer(Customer& c);
	void reserchDish(QString str);
	void reserchByNameAndPhone(QString name, QString phone,QString &address, int& c_ID);
	Customer* reserchByID(int c_ID);
};

#endif // CUSTOMERMANAGER_H
