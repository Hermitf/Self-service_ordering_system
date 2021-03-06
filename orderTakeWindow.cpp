#include "orderTakeWindow.h"
#include "ui_order_takeAway.h"


OrderTakeWindow::OrderTakeWindow(int orderNumber, bool mealFormat, double takeFee, map<Dish, int> numOfDish, double sumMoney, Customer* cus, QString time,Manager *manager)
	:orderNumber(orderNumber)
	, mealFormat(mealFormat)
	, takeFee(takeFee)
	, sumMoney(sumMoney)
	, ui(new Ui::OrderTakeForm())
	, cus(cus)
	,time(time)
	,manager(manager)
{
	for (auto e : numOfDish)
	{
		this->numOfDish[e.first] = e.second;
	}
	ui->setupUi(this);
	ui->orderNumber->setText(QString::number(orderNumber));
	ui->mealFormat->setText("外卖");
	ui->name->setText(cus->getName());
	ui->phoneNumber->setText(cus->getPhone());
	ui->address->setText(cus->getAddress());
	ui->takeFee->setText(QString::number(takeFee));
	ui->time->setText(time);
	updateDishes();
	ui->sumMoney->setText(QString::number(sumMoney));

}

void OrderTakeWindow::updateDishes()
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

OrderTakeWindow::~OrderTakeWindow()
{
	delete ui;
}
