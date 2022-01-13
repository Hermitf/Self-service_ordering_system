#pragma once
#include "qwidget.h"
#include "manager.h"

namespace Ui {
	class QueryWindow;
};

class QueryCustomerImformation:public QWidget
{
	Q_OBJECT
;private:
	Ui::QueryWindow* ui;
	Manager* manager;
public:
	QueryCustomerImformation(Manager *manager);
	~QueryCustomerImformation();
private slots:
	void onQueryButtonClicked();
};

