#ifndef DISH_MENU_H
#define DISH_MENU_H
#include <vector>
#include "dish.h"
#include<utility>

using std::vector;
using std::pair;

class Menu
{
	vector<pair<Dish*, int>> dishes;
	int o_ID;
public:
	Menu(int ID);
	double getSumfee();

	int getID() const;
	void setID(int newID);

	//菜的增删改查
	void addDish(Dish& d, int num);
	void deleteDish(Dish& d);
	void modifyDish(Dish& d, int num);
	const vector<pair<Dish*, int> >& getDishes() const;
};

#endif // DISH_MENU_H
