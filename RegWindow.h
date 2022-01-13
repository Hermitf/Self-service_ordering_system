#pragma once
#include <qwidget.h>
#include"manager.h"

namespace Ui {
	class RegisterWindow;
}

class RegWindow:public QWidget
{
	Q_OBJECT
private:
	Ui::RegisterWindow* ui;
	Manager* manager;
public:
	RegWindow(Manager* manager);
	~RegWindow();
private slots:
	void onBackButtonClick();
	void onRegButtonClick();
};


