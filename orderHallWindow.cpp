#include "orderHallWindow.h"
#include "ui_order_hall.h"

OrderHallWindow::OrderHallWindow(int orderNumber, bool mealFormat, QString tableNumber, double boxFee, map<Dish, int> numOfDish, double sumMoney, Customer* cus,Manager* manager)
	:orderNumber(orderNumber)
	,mealFormat(mealFormat)
	,tableNumber(tableNumber)
	,boxFee(boxFee)
	,sumMoney(sumMoney)
	,ui(new Ui::OrderHallForm())
	,cus(cus)
	,manager(manager)
{
	for (auto e:numOfDish)
	{
		this->numOfDish[e.first] = e.second;
	}
	ui->setupUi(this);
	ui->orderNumber->setText(QString::number(orderNumber));
	ui->mealFormat->setText("堂食");
	ui->tableNumber->setText(tableNumber);
	ui->name->setText(cus->getName());
	ui->phoneNumber->setText(cus->getPhone());
	ui->boxFee->setText(QString::number(boxFee));
	updateDishes();
	ui->sumMoney->setText(QString::number(sumMoney));

}

void OrderHallWindow::updateDishes()
{
	ui->tableWidget->setRowCount(0);
	for (auto e : numOfDish) {
		int row = ui->tableWidget->rowCount();
		ui->tableWidget->insertRow(row);
		ui->tableWidget->setItem(row, 0, new QTableWidgetItem(e.first.getProductName()));
		ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(e.second)));
		ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(e.first.getOriginalPrice())));
		ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(e.first.getDiscountedPrice())));
		ui->tableWidget->resizeRowsToContents();
	}

}

OrderHallWindow::~OrderHallWindow()
{
	delete ui;
}
