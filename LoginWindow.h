#pragma once
#include <qwidget.h>
#include"manager.h"
#include<QStatusBar>

namespace Ui {
	class LoginWindow;
}

class LogInWindow:public QWidget
{
	Q_OBJECT
private:
	Ui::LoginWindow* ui;
	Manager* manager; 
	QStatusBar* m_statusBar;
public:
	LogInWindow(Manager* manager);
	~LogInWindow();
private slots:
	void onRegButtonClick();
	void onLoginButtonClick();
};