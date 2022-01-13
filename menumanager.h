#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <QString>
#include "menu.h"
#include "MysqlManager.h"

class MenuManager
{
	MysqlManager* sqlManager;
public:
	MenuManager(MysqlManager* sqlManager);
	void addMenu(const Menu& m);
	void deleteMenu(Menu& m);
	void modifyMenu(Menu& m);
	Menu& queryById(int o_id);

};

#endif // MENUMANAGER_H
