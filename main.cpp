#include <QApplication>
#include <QMessageBox>
#include <mysql.h>
#include <iostream>
#include "MysqlManager.h"
#include "employeemanager.h"
#include "manager.h"
#include "StartWindow.h"

using std::cout;
using std::endl;


int main(int argc, char* argv[])
{
	MysqlManager* mm = new MysqlManager;
	Manager* manager = new Manager(mm);
	QApplication a(argc, argv);
	StartWindow s(manager);
	s.show();
	return a.exec();
}
