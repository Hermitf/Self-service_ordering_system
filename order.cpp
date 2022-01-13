#include "order.h"



double Order::getServiceFeeScale() const
{
	if (diningStyle == 0 && deskNumber[0] == 'A') return 0.01;
	else if (diningStyle == 0 && deskNumber[0] == 'B') return 0.03;
	else if (diningStyle == 0 && deskNumber[0] == 'C') return 0.05;
	else if (diningStyle == 1) return 0.03;
	return -1;
}


bool Order::getDiningStyle() const
{
	return diningStyle;
}

void Order::setDiningStyle(bool newDiningStyle)
{
	diningStyle = newDiningStyle;
}

int Order::getPeopleNumber() const
{
	return peopleNumber;
}

void Order::setPeopleNumber(int newPeopleNumber)
{
	peopleNumber = newPeopleNumber;
}

const QString& Order::getDeskNumber() const
{
	return deskNumber;
}

void Order::setDeskNumber(const QString& newDeskNumber)
{
	deskNumber = newDeskNumber;
}

int Order::getC_id() const
{
	return c_id;
}

void Order::setC_id(int newC_id)
{
	c_id = newC_id;
}

int Order::getID() const
{
	return ID;
}

void Order::setID(int newID)
{
	ID = newID;
}

Order::Order( bool diningStyle, int peopleNumber, const QString& deskNumber, const QString& deliverTime, int c_id) : diningStyle(diningStyle),peopleNumber(peopleNumber),deskNumber(deskNumber),deliverTime(deliverTime),c_id(c_id),ID(0){}

const QString Order::getDeliverTime() const
{
    return deliverTime;
}

void Order::setDeliverTime(const QString deliverTime)
{
    this->deliverTime = deliverTime;
}

