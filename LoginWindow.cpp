#include "LoginWindow.h"
#include "ui_login.h"
#include "RegWindow.h"
#include "qstring.h"
#include <qmessagebox.h>
#include "BackOfficeManagement.h"

LogInWindow::LogInWindow(Manager* manager):ui(new Ui::LoginWindow),manager(manager)
{
	ui->setupUi(this);
	connect(ui->regButton, SIGNAL(clicked()), this, SLOT(onRegButtonClick()));
	connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(onLoginButtonClick()));
	m_statusBar = new QStatusBar(this);
	layout()->addWidget(m_statusBar);
}

void LogInWindow::onRegButtonClick() {
	RegWindow* rw = new RegWindow(manager);
	rw->show();
	close();
}

LogInWindow::~LogInWindow()
{
	delete ui;
}

void LogInWindow::onLoginButtonClick()
{
	QString workNumber, password;
	workNumber = ui->workNumber->text();
	password = ui->password->text();
	try {
		bool t=manager->getEmployeeManager()->logIn(workNumber,password);
		if (t == true) {
			BackOfficeManagement* bom = new BackOfficeManagement(manager);
			bom->show();
			close();
		}
		else throw "查无此人";
	}
	catch (const char* e) {
		QMessageBox::warning(this, "错误", e);
	}
}
