#ifndef EMPLOYEEMANAGER_H
#define EMPLOYEEMANAGER_H
#include<QString>
#include "employee.h"
#include "MysqlManager.h"

class EmployeeManager {
	MysqlManager* sqlManager;
public:
	EmployeeManager(MysqlManager* sqlManager);
	//增删改查
	void addEmployee(const Employee& e);
	void deleteEmployee(Employee& e);
	void modifyEmployee(Employee& e);
	void reserchEmployee(QString str);
	//登录后台管理系统
	bool logIn(QString workNumber, QString passWord);
	//注册账号
	bool register_(QString workNumber, QString password, QString passwordAgain);
};

#endif // EMPLOYEEMANAGER_H
