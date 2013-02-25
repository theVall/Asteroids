#include "MenuSet.hpp"

MenuSet::MenuSet()
{
}

MenuSet::~MenuSet() {}

void MenuSet::addMenu(Menu *menu)
{
    m_menus.push_back(menu);
}

void MenuSet::paint()
{

   for(boost::ptr_list<Menu>::iterator iter= m_menus.begin(); iter != m_menus.end(); ++iter)
   {
	if(iter->isActive())
	{
		iter->paint();
		return;
	}
   }
}

void MenuSet::mouseEvent(QMouseEvent *event)
{
   for(boost::ptr_list<Menu>::iterator iter= m_menus.begin(); iter != m_menus.end(); ++iter)
   {
	iter->mouseEvent(event);
   }
}

void MenuSet::rePos()
{
   for(boost::ptr_list<Menu>::iterator iter= m_menus.begin(); iter != m_menus.end(); ++iter)
   {
	iter->rePos();
   }
}

int MenuSet::clickedButtonId()
{
   int id = 0;
   for(boost::ptr_list<Menu>::iterator iter= m_menus.begin(); iter != m_menus.end(); ++iter)
   {
	id = iter->clickedButtonId();
	if(id != 0) return id;
   }
   return id;
}
