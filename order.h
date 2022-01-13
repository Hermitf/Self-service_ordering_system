#ifndef ORDER_H
#define ORDER_H
#include"dish.h"
#include<vector>
using std::vector;

class Order
{
	int ID;
	bool diningStyle;//0为堂食，1为外卖
	int peopleNumber;
	QString deskNumber;
	QString deliverTime;
	int c_id;
public:
	Order(bool diningStyle, int peopleNumber, const QString& deskNumber, const QString& deliverTime, int c_id);

	//根据就餐方式，判断服务费或是外卖费，再根据桌号判断就餐费
	double getServiceFeeScale() const;

	int getC_id() const;
	void setC_id(int newC_id);
	bool getDiningStyle() const;
	void setDiningStyle(bool newDiningStyle);
	int getPeopleNumber() const;
	void setPeopleNumber(int newPeopleNumber);
	const QString& getDeskNumber() const;
	void setDeskNumber(const QString& newDeskNumber);
	int getID() const;
	void setID(int newID);
    const QString getDeliverTime() const;
    void setDeliverTime(const QString deliverTime);

};

#endif // ORDER_H
