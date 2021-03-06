#include "BackOfficeManagement.h"
#include"ui_managerWidget.h"
#include "dish.h"
#include"ComboItemDelegate.h"
#include <qmessagebox.h>

BackOfficeManagement::BackOfficeManagement(Manager* manager):ui(new Ui::BackForm),manager(manager),c_id(new vector<int>),o_id(new vector<int>)
{
	ui->setupUi(this);
	ui->chooseTime->setDate(QDate::currentDate());
	connect(ui->menuManagerButton, SIGNAL(clicked()), this, SLOT(onMenuManagerButtonClick()));
	connect(ui->orderManagerButton, SIGNAL(clicked()), this, SLOT(onOrderManagerButtonClick()));
	connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addItem()));
	connect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(changeItem(QTableWidgetItem*)));
	connect(ui->chooseTime, SIGNAL(dateChanged(QDate)), this, SLOT(onOrderManagerButtonClick()));
	connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
	ui->label_8->hide();
	ui->chooseTime->hide();
	ui->groupBox_4->hide();
	ui->addButton->setEnabled(false);
	ui->deleteButton->setEnabled(false);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void BackOfficeManagement::updateDishes()
{
	isUserChange = false;
	ui->tableWidget->clear();
	QStringList tableHeaderList;
	tableHeaderList<< tr("产品编号") << tr("产品名称") << tr("原价") << tr("折扣价") << tr("种类") << tr("销量") ;
	ui->tableWidget->setColumnCount(tableHeaderList.size());
	ui->tableWidget->setRowCount(0);
	for (int i = 0; i < tableHeaderList.size(); i++) {
		ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(tableHeaderList.at(i)));
		ui->tableWidget->setColumnWidth(i, ui->tableWidget->width() / tableHeaderList.size());
	}
	dishes = manager->getDishManager()->queryAll();
	QStringList list;
	for (int i = 0; i <= 6; i++) {
		list<<QString(Dish::getCg(i));
	}
	ui->tableWidget->setItemDelegateForColumn(4, new ComboItemDelegate(list, ui->tableWidget));
	ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
	for (auto e : (*dishes)) {
		int row = ui->tableWidget->rowCount();
		ui->tableWidget->insertRow(row);
		QTableWidgetItem* text = new QTableWidgetItem(QString::number(e->getID()));
		text->setFlags(text->flags() & (~Qt::ItemIsEditable));
		ui->tableWidget->setItem(row, 0, text);
		ui->tableWidget->setItem(row, 1, new QTableWidgetItem(e->getProductName()));
		ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(e->getOriginalPrice())));
		ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(e->getDiscountedPrice())));
		ui->tableWidget->setItem(row, 4, new QTableWidgetItem(Dish::getCg(e->getCategory()))); 

		text = new QTableWidgetItem(QString::number(e->getSale()));
		
		text->setFlags(text->flags() & (~Qt::ItemIsEditable));
		ui->tableWidget->setItem(row, 5, text);//禁止更改
		
	}
	ui->tableWidget->resizeRowsToContents();
	isUserChange = true;
}

void BackOfficeManagement::deleteItem()
{
	int currentRow = ui->tableWidget->currentRow();
	if (currentRow == -1) {
		QMessageBox::warning(this, "错误", "请选择一行");
		return;
	}
	int id=ui->tableWidget->item(currentRow, 0)->text().toInt();
	if (ui->menuManagerButton->isChecked()) {
	manager->getDishManager()->deleteDish(id);

	}
	else if (ui->orderManagerButton->isChecked()) {
		manager->getOrderManager()->deleteOrder(id);
	}
	ui->tableWidget->removeRow(currentRow);
}

void BackOfficeManagement::setAllbuttonunchecked()
{
	ui->menuManagerButton->setChecked(false);
	ui->orderManagerButton->setChecked(false);
}

void BackOfficeManagement::onMenuManagerButtonClick() 
{ 
	setAllbuttonunchecked(); 
	ui->menuManagerButton->setChecked(true); 
	updateDishes();
	ui->label_8->hide();
	ui->chooseTime->hide();
	ui->groupBox_4->hide();
	ui->addButton->setEnabled(true);
	ui->deleteButton->setEnabled(true);
}

void BackOfficeManagement::onOrderManagerButtonClick() 
{ 
	setAllbuttonunchecked(); 
	ui->orderManagerButton->setChecked(true); 
	updateOrder();

	ui->label_8->show();
	ui->chooseTime->show();
	ui->groupBox_4->show();
	ui->addButton->setEnabled(false);
	ui->deleteButton->setEnabled(true);
}

void BackOfficeManagement::updateOrder()
{
	isUserChange = false;
	ui->tableWidget->clear();
	QStringList tableHeaderList;
	tableHeaderList << tr("订单编号")<< tr("附加费用") << tr("就餐形式") << tr("桌号") << tr("姓名") << tr("地址") << tr("预计送达时间") << tr("手机号") ;
	ui->tableWidget->setColumnCount(tableHeaderList.size());
	ui->tableWidget->setRowCount(0);
	for (int i = 0; i < tableHeaderList.size(); i++) {
		ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(tableHeaderList.at(i)));
		ui->tableWidget->setColumnWidth(i, ui->tableWidget->width() / tableHeaderList.size());
	}
	QString time=ui->chooseTime->date().toString("yyyy-MM-dd");
	orders = manager->getOrderManager()->rearchByTime(time,o_id,c_id);
	Customer* cus;
	QStringList list;
	list << "堂食" << "外卖";
	ui->tableWidget->setItemDelegateForColumn(2, new ComboItemDelegate(list, ui->tableWidget));
	ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	for (auto i = 0; i < orders->size();i++) {
		int row = ui->tableWidget->rowCount();
		ui->tableWidget->insertRow(row);
		try {
			cus = manager->getCustomerManager()->reserchByID((*c_id)[i]);
		}
		catch (const char* e) {
			QMessageBox::warning(this, "错误", e);
			continue;
		}
		
		(*orders)[i]->setID((*o_id)[i]);
		(*orders)[i]->setC_id((*c_id)[i]);
		QTableWidgetItem* textt = new QTableWidgetItem(QString::number((*o_id)[i]));
		textt->setFlags(textt->flags() & (~Qt::ItemIsEditable));//变为不可编辑
		ui->tableWidget->setItem(row, 0, textt);
		ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number((*orders)[i]->getServiceFeeScale())));
		ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString(((*orders)[i]->getDiningStyle())?"外卖":"堂食")));
		ui->tableWidget->setItem(row, 3, new QTableWidgetItem((*orders)[i]->getDeskNumber()));
		ui->tableWidget->setItem(row, 4, new QTableWidgetItem(cus->getName()));
		ui->tableWidget->setItem(row, 5, new QTableWidgetItem(cus->getAddress()));
		ui->tableWidget->setItem(row, 6, new QTableWidgetItem(manager->getOrderManager()->getTime(*(*orders)[i])));
		ui->tableWidget->setItem(row, 7, new QTableWidgetItem(cus->getPhone()));
				
	}
	ui->tableWidget->resizeRowsToContents();
	orderNum = orders->size();
	ui->label_3->setText(QString::number(orderNum));
	int takeOut = 0;
	int hall = 0;
	sumMoney = 0;
	for (auto e : *orders) {
		sumMoney+=manager->getMenuManager()->queryById(e->getID()).getSumfee();
		if (e->getDiningStyle() == 0) hall++;
		else takeOut++;
	}
	ui->label_5->setText(QString::number(sumMoney));
	ui->label_6->setText(QString::number(takeOut)+":"+QString::number(hall));
	isUserChange = true;



}

void BackOfficeManagement::addItem()
{

	isUserChange = false;
	int row = ui->tableWidget->rowCount();
	QString name="";
	double oripri = 0;
	double dispri = 0;
	int cate = 0;
	int sale = 0;
	Dish* dish = new Dish(name, oripri, dispri, sale, cate); 
	manager->getDishManager()->addDish(*dish);
	ui->tableWidget->insertRow(row);

	QTableWidgetItem* text = new QTableWidgetItem(QString::number(dish->getID()));
	text->setFlags(text->flags() & (~Qt::ItemIsEditable));
	ui->tableWidget->setItem(row, 0, text);

	ui->tableWidget->setItem(row, 1, new QTableWidgetItem(name));
	ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(oripri)));
	ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(dispri)));
	ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString(Dish::getCg(cate))));

	text = new QTableWidgetItem(QString::number(sale));
	text->setFlags(text->flags() & (~Qt::ItemIsEditable));
	ui->tableWidget->setItem(row, 5, text);
	
	isUserChange = true;

}

void BackOfficeManagement::changeItem(QTableWidgetItem* item)
{
	if (!isUserChange)return;
	int currentRow = item->row();//获取当前行号，从0开始
	int currentColumn = item->column();//获取当前列号，从0开始
	//if (currentColumn != 1) return;
	//else {
		if (ui->menuManagerButton->isChecked()) {
			int orderNum=QString(ui->tableWidget->item(currentRow, 0)->text()).toInt();
			QString name = ui->tableWidget->item(currentRow, 1)->text();
			double originMoney =  QString(ui->tableWidget->item(currentRow, 2)->text()).toDouble();
			double discountMoney =  QString(ui->tableWidget->item(currentRow, 3)->text()).toDouble();
			int category ;
			for (int i = 0; i <= 6; i++) {
				if (Dish::getCg(i) == ui->tableWidget->item(currentRow, 4)->text()) { category = i; break; }
			}
			int sale = QString(ui->tableWidget->item(currentRow, 5)->text()).toInt();
			Dish* dish = new Dish(name, originMoney, discountMoney, sale, category);
			dish->setID(orderNum);
			manager->getDishManager()->modifyDishByID(*dish);
		}
		//else if (ui->orderManagerButton->isChecked()) {
		//	int orderNum=QString(ui->tableWidget->item(currentRow, 0)->text()).toInt();
		//	double otherMoney =  QString(ui->tableWidget->item(currentRow, 1)->text()).toDouble();
		//	bool diningStyle=(QString(ui->tableWidget->item(currentRow, 2)->text()).toInt())!=0;
		//	QString deskNum =  QString(ui->tableWidget->item(currentRow, 3)->text());
		//	QString name= QString(ui->tableWidget->item(currentRow, 4)->text());
		//	QString address= QString(ui->tableWidget->item(currentRow, 5)->text());
		//	QString time= QString(ui->tableWidget->item(currentRow, 6)->text());
		//	QString phone= QString(ui->tableWidget->item(currentRow, 7)->text());
		//	Order* order = new Order(diningStyle, 0, deskNum, time, 0);
		//	//order->setID(order->getID());
		//	//manager->getOrderManager()->modifyOrder(*order);
		//	//
		//}
	//}

}


BackOfficeManagement::~BackOfficeManagement()
{
	delete ui;
}


