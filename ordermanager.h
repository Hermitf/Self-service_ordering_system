#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H
#include "MysqlManager.h"
#include "order.h"

class OrderManager
{
	MysqlManager* sqlManager;
public:
	OrderManager(MysqlManager* sqlManager);

	void addOrder(Order& o);
	void deleteOrder(int o_ID);
	void modifyOrder(Order& o);
	QString getTime(Order& o); 
	void rearchByC_ID(int c_ID,int &o_ID, double& serviceFeeScale,bool &diningStyle,QString &deskNumber,QString &time);
	vector<Order*>* rearchAll(vector<int>* o_ID, vector<int>* c_ID);
	vector<Order*>* rearchByTime(QString time, vector<int>* o_ID, vector<int>* c_ID);
	vector<int>* rearchByC_ID();
};

#endif // ORDERMANAGER_H
