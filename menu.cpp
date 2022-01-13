#include "menu.h"

int Menu::getID() const
{
	return o_ID;
}

void Menu::setID(int newID)
{
	o_ID = newID;
}

void Menu::addDish(Dish& d, int num)
{
	dishes.push_back(pair(&d, num));
}

void Menu::deleteDish(Dish& d)
{
	for (auto i = dishes.begin(); i != dishes.end(); i++) {
		if (i->first->getID() == d.getID()) { dishes.erase(i); break; }
	}

}

void Menu::modifyDish(Dish& d, int num)
{
	for (auto i = dishes.begin(); i != dishes.end(); i++) {
		if (i->first->getID() == d.getID()) {
			i->second = num;
			break;
		}
	}
}

const vector<pair<Dish*, int> >& Menu::getDishes() const
{
	return dishes;
}

Menu::Menu(int ID) : o_ID(ID) {}

double Menu::getSumfee()
{
	double sum = 0;
	for (auto i = dishes.begin(); i != dishes.end(); i++) {
		sum += i->first->getDiscountedPrice() * i->second;
	}
	return sum;
}
