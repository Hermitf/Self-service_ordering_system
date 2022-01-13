#include "manager.h"


Manager::Manager(MysqlManager* mm):customerManager(new CustomerManager(mm)),dishManager(new DishManager(mm)),employeeManager(new EmployeeManager(mm)),menuManager(new MenuManager(mm)),orderManager(new OrderManager(mm))
{
}

CustomerManager* Manager::getCustomerManager() const
{
    return customerManager;
}

DishManager* Manager::getDishManager() const
{
    return dishManager;
}

EmployeeManager* Manager::getEmployeeManager() const
{
    return employeeManager;
}

MenuManager* Manager::getMenuManager() const
{
    return menuManager;
}

OrderManager* Manager::getOrderManager() const
{
    return orderManager;
}

