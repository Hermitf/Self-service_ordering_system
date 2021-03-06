#ifndef DISH_H
#define DISH_H
#include<QString>


class Dish {
	QString productName;
	int ID;
	double originalPrice;
	double discountedPrice;
	int sale;
	int category;
	const static char* cg[];
	//int leftNum;//剩余量
public:
	Dish(QString productName, double originalPrice, double discountedPrice, int sale,int category);

	const QString& getProductName() const;
	void setProductName(const QString& newProductName);
	double getOriginalPrice() const;
	void setOriginalPrice(double newOriginalPrice);
	double getDiscountedPrice() const;
	void setDiscountedPrice(double newDiscountedPrice);
	int getSale() const;
	void setSale(int newSale);
	int getID() const;
	void setID(int newID);
	int getCategory() const;
	void setCategory(int newCategory);
	bool operator==(const Dish& dish) const;
	bool operator<(const Dish& dish) const;
    //int getLeftNum() const;
    //void setLeftNum(int leftNum);
    static const char * getCg(int category);

};



#endif // DISH_H
