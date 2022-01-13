#pragma once

#include "qwidget.h"
#include "manager.h"
#include <iostream>
#include <map>

using std::map;

namespace Ui {
	class OrderHallForm;
}

class OrderHallWindow : public QWidget
{
	Q_OBJECT
private:
	Ui::OrderHallForm* ui;
	Manager* manager;
	int orderNumber;
	bool mealFormat;
	QString tableNumber;
	double boxFee;
	map<Dish, int> numOfDish;
	double sumMoney;
	Customer* cus;
public:
	OrderHallWindow(int orderNumber,bool mealFormat,QString tableNumber,double boxFee,map<Dish, int> numOfDish,double sumMoney,Customer*cus,Manager* manager);

	void updateDishes();
	~OrderHallWindow();


};

