#include "RegWindow.h"
#include "ui_reg.h"
#include "LoginWindow.h"
#include <QMessageBox>

RegWindow::RegWindow(Manager* manager):ui(new Ui::RegisterWindow),manager(manager)
{
	ui->setupUi(this);
	connect(ui->backButton, SIGNAL(clicked()), this, SLOT(onBackButtonClick()));
	connect(ui->regButton, SIGNAL(clicked()), this, SLOT(onRegButtonClick()));
}
void RegWindow::onBackButtonClick()
{
	LogInWindow* lw = new LogInWindow(manager);
	lw->show();
	close();
}

void RegWindow::onRegButtonClick()
{
	QString workNumber, password, password2;
	workNumber = ui->workNumber->text();
	password = ui->password->text();
	password2 = ui->password2->text();
	try {
		manager->getEmployeeManager()->register_(workNumber, password, password2);
		QMessageBox::about(this, "提示", "注册成功");
	}
	catch (const char* e) {
		QMessageBox::warning(this, "错误", e);
	}
}


RegWindow::~RegWindow()
{
	delete ui;
}
