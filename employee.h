#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>

class Employee {
	QString workNumber;
	QString password;
public:
	Employee(QString workNumber, QString password);

	const QString& getPassword() const;
	void setPassword(const QString& newPassword);
	const QString& getWorkNumber() const;
	void setWorkNumber(const QString& newWorkNumber);
};

#endif // EMPLOYEE_H
