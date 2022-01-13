#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>
#include "manager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
	class Form;
}
QT_END_NAMESPACE

class StartWindow:public QWidget
{
	Q_OBJECT
private:
	Manager* manager;
	Ui::Form* ui;
public:
	StartWindow(Manager* manager,QWidget* parent = nullptr);
	~StartWindow();

private slots:
	void onManagerButtonClick();
	void onCustomerButtonClick();
};
#endif // STARTWINDOW_H
