#include "customer.h"

Customer::Customer(QString name, QString address, QString phone)
{
	setName(name);
	setAddress(address);
	setPhone(phone);
}

const QString& Customer::getName() const
{
	return name;
}

void Customer::setName(const QString& newName)
{
	name = newName;
}

const QString& Customer::getAddress() const
{
	return address;
}

void Customer::setAddress(const QString& newAddress)
{
	address = newAddress;
}

const QString& Customer::getPhone() const
{
	return phone;
}

void Customer::setPhone(const QString& newPhone)
{
	phone = newPhone;
}

int Customer::getID() const
{
	return ID;
}

void Customer::setID(int newID)
{
	ID = newID;
}
