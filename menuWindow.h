#pragma once

#include <qwidget.h>
#include "dishmanager.h"
#include "manager.h"
#include <iostream>
#include <map>
#include <QTableWidgetItem>

using std::map;

namespace Ui {
	class MenuForm;
}

class MenuWindow:public QWidget
{
	Q_OBJECT
private:
	Ui::MenuForm* ui;
	Manager* manager;
	vector<Dish*>* currentDishes=nullptr;
	map<Dish, int> numOfDish;
	double sumMoney = 0;
	bool isUserChange = true;
	
public:
	MenuWindow(Manager* manager,QWidget* parent = nullptr);
	void updateDishes(int category);
	void setAllbuttonunchecked();
	void setUnedited(int row, int currentrow, QString text);
	~MenuWindow();

private slots:
	void onreCommendButtonClick();
	void onVegetableButtonClick();
	void onStapleButtonClick();
	void onSeafoodButtonClick();
	void onMeatButtonClick();
	void onDiscountedButtonClick();
	void onDessertButtonClick();
	void changeItem(QTableWidgetItem* item);
	void onCheckOutButtonClick();
	void onQueryButtonClick();
};

