#pragma once

#include "qwidget.h"
#include "manager.h"
#include <iostream>
#include <map>

using std::map;

namespace Ui {
	class OrderTakeForm;
}

class OrderTakeWindow : public QWidget
{
	Q_OBJECT
private:
	Ui::OrderTakeForm* ui;
	Manager* manager;
	int orderNumber;
	bool mealFormat;
	double takeFee;
	map<Dish, int> numOfDish;
	double sumMoney;
	Customer* cus;
	QString time;
public:
	OrderTakeWindow(int orderNumber, bool mealFormat, double takeFee, map<Dish, int> numOfDish, double sumMoney, Customer* cus,QString time,Manager*manager);

	void updateDishes();
	~OrderTakeWindow();


};

