#pragma once
#include "manager.h"
#include <qwidget.h>
#include<QTableWidgetItem>

namespace Ui {
	class BackForm;
}

class BackOfficeManagement:public QWidget
{
	Q_OBJECT
private:
	int orderNum=0;
	double sumMoney=0;
	int divisionNum=0;
	Ui::BackForm* ui;
	Manager* manager;
	vector<Dish*>* dishes=nullptr;
	vector<Order*>* orders;
	vector<Customer*>* cus;
	vector<int>* o_id;
	vector<int>* c_id;
	bool isUserChange =true;
public:
	BackOfficeManagement(Manager* manager);
	void updateDishes();
	void setAllbuttonunchecked();
	void updateOrder();
	~BackOfficeManagement();
private slots:
	void onMenuManagerButtonClick();
	void onOrderManagerButtonClick();
	void addItem();
	void deleteItem();
	void changeItem(QTableWidgetItem* item);
};

