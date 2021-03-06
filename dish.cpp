#include "dish.h"

int Dish::getID() const
{
	return ID;
}

void Dish::setID(int newID)
{
	ID = newID;
}

int Dish::getCategory() const
{
	return category;
}

void Dish::setCategory(int newCategory)
{
	category = newCategory;
}

bool Dish::operator==(const Dish& dish) const
{
	return ID == dish.getID();
}

bool Dish::operator<(const Dish& dish) const
{
	return ID < dish.getID();
}


const char* Dish::getCg(int category) {
	return cg[category];
}




Dish::Dish(QString productName, double originalPrice, double discountedPrice, int sale, int category) {
	setProductName(productName);
	setOriginalPrice(originalPrice);
	setDiscountedPrice(discountedPrice);
	setSale(sale);
	setCategory(category);
}

const QString& Dish::getProductName() const
{
	return productName;
}

void Dish::setProductName(const QString& newProductName)
{
	productName = newProductName;
}

double Dish::getOriginalPrice() const
{
	return originalPrice;
}

void Dish::setOriginalPrice(double newOriginalPrice)
{
	originalPrice = newOriginalPrice;
}

double Dish::getDiscountedPrice() const
{
	return discountedPrice;
}

void Dish::setDiscountedPrice(double newDiscountedPrice)
{
	discountedPrice = newDiscountedPrice;
}

int Dish::getSale() const
{
	return sale;
}

void Dish::setSale(int newSale)
{
	sale = newSale;
}
const char* Dish::cg[] = { "店长推荐","折扣商品","蔬菜","肉类","海鲜","主食","甜品" };
//int Dish::getLeftNum() const
//{
//    return leftNum;
//}
//
//void Dish::setLeftNum(int leftNum)
//{
//    this->leftNum = leftNum;
//}

