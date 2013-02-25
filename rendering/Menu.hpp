#ifndef MENU_H
#define MENU_H

#include <boost/ptr_container/ptr_list.hpp>
#include "MenuElement.hpp"
#include "MenuButton.hpp"
#include <QWidget>
#include <QGLWidget>
#include <QPainter>
#include <QMouseEvent>


class Menu 
//:public QWidget
{
  // Q_OBJECT
   public:
	Menu(QWidget *parent);
	~Menu();
	void paint();	
	void addButton(MenuButton *button);
	void addElement(MenuElement *elem);
	void mouseEvent(QMouseEvent* event);
	void rePos();
	void enable();
	void disable();
	int clickedButtonId();
	bool isActive();
	int m_nextYButtonPos;
   protected:
	void paintEvent(QPaintEvent *e);
   private:
	QWidget *m_parent;
	boost::ptr_list<MenuElement> m_elems;
	boost::ptr_list<MenuButton> m_buttons;
	int m_buttonOffsetY;
	QRect *m_menuRect;
	QImage *m_background;
	QPixmap m_pixmap;
	bool m_active;	

};

#endif /* Menu.hpp */
