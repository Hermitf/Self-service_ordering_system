#include "ui_query.h"
#include "queryCustomerImformation.h"
#include <QMessageBox>
#include<iostream>
#include <map>
#include "orderHallWindow.h"
#include "orderTakeWindow.h"
#include<utility>
#include<QRegularExpression>
#include<QRegularExpressionValidator>

using std::map;

QueryCustomerImformation::QueryCustomerImformation(Manager*manager):ui(new Ui::QueryWindow()),manager(manager)
{
	ui->setupUi(this);

	connect(ui->queryButton, SIGNAL(clicked()), this, SLOT(onQueryButtonClicked()));
	ui->phone->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
}

void QueryCustomerImformation::onQueryButtonClicked()
{
	QString name=ui->name->text(), phone=ui->phone->text(), address;
	int o_ID,c_ID;
	double serviceFeeScale;
	bool diningStyle;
	QString deskNumber, time;
	try {
		manager->getCustomerManager()->reserchByNameAndPhone(name, phone,address,c_ID);
		Customer* cus = new Customer(name, address, phone);
		manager->getOrderManager()->rearchByC_ID(c_ID,o_ID,serviceFeeScale, diningStyle, deskNumber, time);
		Menu& menu=manager->getMenuManager()->queryById(o_ID);
		//获取总金额
		map<Dish, int>* dishes=new map<Dish,int>;
		double sumMoney=menu.getSumfee();
		for (auto i = menu.getDishes().begin(); i != menu.getDishes().end(); i++) {
			dishes->insert(pair(*(i->first), i->second));
			
			//(*dishes)[*(i->first)] = i->second;
		}
		std::cout << dishes->size() << std::endl;
		if (diningStyle == 0) {
			double deskMoney =serviceFeeScale * sumMoney;
			OrderHallWindow* ohw = new OrderHallWindow(o_ID, diningStyle, deskNumber, deskMoney, *dishes, sumMoney + deskMoney, cus,manager);
			ohw->show();
		}
		else {
			OrderTakeWindow* otw = new OrderTakeWindow(o_ID, diningStyle, 4, *dishes, sumMoney, cus, time,manager);
			otw->show();
		}
		this->close();

	}
	catch (const char* e) {
		QMessageBox::warning(this, "错误", e);
	}
}

QueryCustomerImformation::~QueryCustomerImformation()
{
	delete ui;
}
