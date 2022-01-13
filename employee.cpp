#include "employee.h"

Employee::Employee(QString workNumber, QString password) {
	setWorkNumber(workNumber);
	setPassword(password);
}

const QString& Employee::getWorkNumber() const
{
	return workNumber;
}

void Employee::setWorkNumber(const QString& newWorkNumber)
{
	workNumber = newWorkNumber;
}


const QString& Employee::getPassword() const
{
	return password;
}

void Employee::setPassword(const QString& newPassword)
{
	password = newPassword;
}
