#ifndef MENUSET_H
#define MENUSET_H

#include <QMouseEvent>
#include <boost/ptr_container/ptr_list.hpp>
#include "Menu.hpp"

class MenuSet 
{
   public:
	MenuSet();
	~MenuSet();
	void paint();	
	void addMenu(Menu *menu);
	void mouseEvent(QMouseEvent* event);
	void rePos();
	int clickedButtonId();
   private:
	boost::ptr_list<Menu> m_menus;
};

#endif /* MenuSet.hpp */
