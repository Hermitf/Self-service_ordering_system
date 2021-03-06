#include "menuWindow.h"
#include "ui_menuWidget.h"
#include "orderHallWindow.h"
#include "orderTakeWindow.h"
#include "order.h"
#include <utility>
#include <vector>
#include <qmessagebox.h>
#include "queryCustomerImformation.h"



MenuWindow::MenuWindow(Manager* manager, QWidget* parent):QWidget(parent),ui(new Ui::MenuForm),manager(manager)
{
	ui->setupUi(this);
	connect(ui->recommendButton, SIGNAL(clicked()), this, SLOT(onreCommendButtonClick()));
	connect(ui->vegetableButton, SIGNAL(clicked()), this, SLOT(onVegetableButtonClick()));
	connect(ui->stapleButton, SIGNAL(clicked()), this, SLOT(onStapleButtonClick()));
	connect(ui->seafoodButton, SIGNAL(clicked()), this, SLOT(onSeafoodButtonClick()));
	connect(ui->meatButton, SIGNAL(clicked()), this, SLOT(onMeatButtonClick()));
	connect(ui->discountedButton, SIGNAL(clicked()), this, SLOT(onDiscountedButtonClick()));
	connect(ui->dessertButton, SIGNAL(clicked()), this, SLOT(onDessertButtonClick()));
	onreCommendButtonClick();
	connect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(changeItem(QTableWidgetItem*)));
	connect(ui->checkoutButton, SIGNAL(clicked()), this, SLOT(countMoney()));
	connect(ui->checkoutButton, SIGNAL(clicked()), this, SLOT(onCheckOutButtonClick()));
	connect(ui->quickQueryButton, SIGNAL(clicked()), this, SLOT(onQueryButtonClick()));
	ui->deskNumber->setValidator(new QRegularExpressionValidator(QRegularExpression("[ABC][1-9][0-9]?")));
	ui->peopleNumber->setValidator(new QRegularExpressionValidator(QRegularExpression("[1-9]|1[0-2]")));
	ui->phoneNumber->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
}	

void MenuWindow::setUnedited(int row,int currentrow,QString text)
{
		//QTableWidgetItem* count=new QTableWidgetItem("0");
		QTableWidgetItem* textt=new QTableWidgetItem(text);
		textt->setFlags(textt->flags()& (~Qt::ItemIsEditable));//变为不可编辑
		ui->tableWidget->setItem(row, currentrow, textt);
}

void MenuWindow::updateDishes(int category)
{
	isUserChange = false;
	ui->tableWidget->setRowCount(0);
	currentDishes = manager->getDishManager()->queryByCategory(category);
	for (auto e : (*currentDishes)) {
		int row = ui->tableWidget->rowCount();
		ui->tableWidget->insertRow(row);
		setUnedited(row, 0, e->getProductName());
		ui->tableWidget->setItem(row, 1, new QTableWidgetItem(numOfDish.count(*e) ? QString::number(numOfDish[*e]):"0"));
		setUnedited(row, 2, QString::number(e->getOriginalPrice()));
		setUnedited(row, 3, QString::number(e->getDiscountedPrice()));
		setUnedited(row, 4, QString::number(e->getSale()));
		ui->tableWidget->resizeRowsToContents();
	}
	isUserChange = true;
}

void MenuWindow::setAllbuttonunchecked()
{
	ui->recommendButton->setChecked(false);
	ui->vegetableButton->setChecked(false);
	ui->stapleButton->setChecked(false);
	ui->seafoodButton->setChecked(false);
	ui->meatButton->setChecked(false);
	ui->discountedButton->setChecked(false);
	ui->dessertButton->setChecked(false);
}


MenuWindow::~MenuWindow()
{
	delete ui;
}

#define buttonFunc(n1,n2,n3) \
void MenuWindow::on##n1##ButtonClick() \
{ \
	setAllbuttonunchecked(); \
	ui->n2->setChecked(true); \
	updateDishes(n3); \
}

buttonFunc(Vegetable, vegetableButton,2);
buttonFunc(reCommend, recommendButton,0);
buttonFunc(Staple, stapleButton,5);
buttonFunc(Seafood, seafoodButton,4);
buttonFunc(Meat, meatButton,3);
buttonFunc(Discounted, discountedButton,1);
buttonFunc(Dessert, dessertButton,6);

void MenuWindow::changeItem(QTableWidgetItem* item)
{
	if (!isUserChange)return;
	int currentRow=item->row();//获取当前行号，从0开始
	int currentColumn = item->column();//获取当前列号，从0开始
	if (currentColumn != 1) return;
	else {
		
		QString text = ui->tableWidget->item(currentRow, currentColumn)->text();
		QString money = ui->tableWidget->item(currentRow, 3)->text();
		QString symbol = ui->tableWidget->item(currentRow, 0)->text();
		numOfDish[*(*currentDishes)[currentRow]] = text.toInt();
	}

}

void MenuWindow::onCheckOutButtonClick()
{
	//获取页面中堂食或者外卖的选项
	bool diningstyle= ui->carryoutButton->isChecked();
	//获取填入的桌号
	QString dsknum = ui->deskNumber->text();
	if (dsknum == ""&&!diningstyle) { QMessageBox::warning(this, "错误", "请输入桌号！"); return; }
	//获取填入的人数
	int peonum = ui->peopleNumber->text().toInt();
	if (peonum == NULL&&!diningstyle) { QMessageBox::warning(this, "错误", "请输入人数！"); return; }
	//先存人的信息
	QString name = ui->name->text();
	if (name == "") { QMessageBox::warning(this, "错误", "请输入姓名！"); return; }
	QString phonum=ui->phoneNumber->text();
	if (phonum == "") { QMessageBox::warning(this, "错误", "请输入电话！"); return; }
	QString adr=ui->address->text();
	if(diningstyle&&adr=="") {QMessageBox::warning(this, "错误", "请输入地址！"); return; }
	Customer* cus = new Customer(name, adr, phonum);
	if(numOfDish.size()==0) {QMessageBox::warning(this, "错误", "未点菜品！"); return; }
	try {
		manager->getCustomerManager()->addCustomer(*cus);
		//将数据插入数据库订单，并补充菜品菜单数据库
		Order* order = new Order(diningstyle, peonum, dsknum, "", cus->getID());

		manager->getOrderManager()->addOrder(*order);
		//获取订单数据库中的订单号
		int ordernum = order->getID();

		Menu* menu = new Menu(order->getID());
		for (auto i = numOfDish.begin(); i != numOfDish.end(); i++) {
			menu->addDish(*new Dish(i->first), i->second);
		}
		manager->getMenuManager()->addMenu(*menu);
		//获取总金额
		sumMoney=menu->getSumfee();
		//获取填入的餐桌费
		double otherMoney = order->getServiceFeeScale() * sumMoney;
		if (diningstyle == 0) {
			OrderHallWindow* ohw = new OrderHallWindow(ordernum, diningstyle, dsknum, otherMoney, numOfDish, sumMoney+ otherMoney,cus,manager);
			ohw->show();
		}
		else {
			QString time = manager->getOrderManager()->getTime(*order);
			OrderTakeWindow* otw = new OrderTakeWindow(ordernum, diningstyle, otherMoney, numOfDish, sumMoney+ otherMoney, cus,time,manager);
			otw->show();
		}
		
	}
	catch (const char* e) {
		QMessageBox::warning(this, "错误", e);
	}
}

void MenuWindow::onQueryButtonClick()
{
	QueryCustomerImformation* qci = new QueryCustomerImformation(manager);
	qci->show();
}
