#pragma once
#include "customermanager.h"
#include "dishmanager.h"
#include "employeemanager.h"
#include "menumanager.h"
#include"ordermanager.h"
#include "MysqlManager.h"

class Manager
{
	CustomerManager* customerManager;
	DishManager* dishManager;
	EmployeeManager* employeeManager;
	MenuManager* menuManager;
	OrderManager* orderManager;
public:
	Manager(MysqlManager* mm);
    CustomerManager* getCustomerManager() const;
    DishManager* getDishManager() const;
    EmployeeManager* getEmployeeManager() const;
    MenuManager* getMenuManager() const;
    OrderManager* getOrderManager() const;
};

