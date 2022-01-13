#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <QString>

class Customer
{
	QString name;
	QString address;
	QString phone;
	int ID=0;
public:
	Customer(QString name, QString address, QString phone);
	const QString& getName() const;
	void setName(const QString& newName);
	const QString& getAddress() const;
	void setAddress(const QString& newAddress);
	const QString& getPhone() const;
	void setPhone(const QString& newPhone);
	int getID() const;
	void setID(int newID);
};

#endif // CUSTOMER_H
