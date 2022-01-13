#include "StartWindow.h"
#include "ui_start.h"
#include<iostream>
#include "menuWindow.h"
#include "LoginWindow.h"

StartWindow::StartWindow(Manager* manager,QWidget* parent):manager(manager),QWidget(parent),ui(new Ui::Form)
{
	/*QWidget* widget = new QWidget(this);
	this->setCentralWidget(widget);*/
	ui->setupUi(this);
	connect(ui->managerButton, SIGNAL(clicked()), this, SLOT(onManagerButtonClick()));
	connect(ui->label_3, SIGNAL(linkActivated(QString)), this, SLOT(onManagerButtonClick()));
	connect(ui->customerButton, SIGNAL(clicked()), this, SLOT(onCustomerButtonClick()));
	connect(ui->label_2, SIGNAL(linkActivated(QString)), this, SLOT(onCustomerButtonClick()));
}

StartWindow::~StartWindow()
{
	delete ui;
}

void StartWindow::onManagerButtonClick() {
	LogInWindow* lw=new LogInWindow(manager);
	lw->show();
	close();
}
void StartWindow::onCustomerButtonClick() {
	//OrderWindow* ow=new OrderWindow(this);
	MenuWindow* mw=new MenuWindow(manager);
	mw->show();
	close();
}