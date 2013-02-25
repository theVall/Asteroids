#include "Menu.hpp"

Menu::Menu(QWidget *parent)
//	: QWidget(parent)
{
	m_parent = parent;
	int parentMid = parent->geometry().center().x();

	int menuToTop = 50;
	int buttonToTop = 0;
	int menuWidth = 350;
	int menuHight = 400;

	int menuLeft = parentMid - menuWidth/2;

	m_buttonOffsetY = 15;

	QSize menuSize(menuWidth, menuHight);

	m_menuRect = new QRect(QPoint(menuLeft, menuToTop), menuSize);
	m_nextYButtonPos = menuToTop + buttonToTop;

	m_background = new QImage("res/menu/frame.png");
	m_pixmap = QPixmap::fromImage(*m_background);

//	setAutoFillBackground(false);
	rePos();

}

bool Menu::isActive()
{
	return m_active;
}
int Menu::clickedButtonId()
{

	for(boost::ptr_list<MenuButton>::iterator it = m_buttons.begin();
		it != m_buttons.end(); ++it)
	{
		if(it->m_state == MenuButton::CLICKED)
		{
			it->m_state = MenuButton::NORMAL;
			return it->getId();
		}
	}
	return 0;
}


Menu::~Menu()
{
}

void Menu::enable()
{
	m_active = true;
}

void Menu::disable()
{
	m_active = false;
}

void Menu::mouseEvent(QMouseEvent *event)
{
	if(!m_active) return;
	for(boost::ptr_list<MenuButton>::iterator it = m_buttons.begin();
		it != m_buttons.end(); ++it)
	{
		it->mouseEvent(event);
	}
}

void Menu::rePos(){
	QPoint parentMid(m_parent->geometry().center());
	QPoint menuMid(m_menuRect->center());
	QPoint dif = parentMid - menuMid;
	m_menuRect->moveCenter(parentMid);

	//setGeometry(*m_menuRect);
	for(boost::ptr_list<MenuButton>::iterator it = m_buttons.begin();
		it != m_buttons.end(); ++it)
	{
		it->getRect()->translate(dif);
	}
	for(boost::ptr_list<MenuElement>::iterator it = m_elems.begin();
		it != m_elems.end(); ++it)
	{
		it->getRect()->translate(dif);
	}

}

void Menu::addButton(MenuButton* button){

	int posX = m_menuRect->center().x() - button->getImage()->size().width()/2;
	int posY = m_nextYButtonPos;
	m_nextYButtonPos += m_buttonOffsetY + button->getImage()->size().height();
	button->setRect(new QRect(QPoint(posX, posY), button->getImage()->size()));
	m_buttons.push_back(button);
}

void Menu::addElement(MenuElement* elem)
{
	int posX = m_menuRect->center().x() - elem->getImage()->size().width()/2;
	int posY = m_nextYButtonPos;
	m_nextYButtonPos += m_buttonOffsetY + elem->getImage()->size().height();
	elem->setRect(new QRect(QPoint(posX, posY), elem->getImage()->size()));
	m_elems.push_back(elem);
	
}

void Menu::paintEvent(QPaintEvent* e)
{
	//QWidget::paintEvent(e);
	paint();
}

void Menu::paint()
{
	if(m_active)
	{
		QPainter painter(m_parent);
		painter.save();
		painter.setRenderHint(QPainter::Antialiasing, true);
		//painter.drawImage(*m_menuRect, *m_background);
		painter.drawPixmap(*m_menuRect, m_pixmap);
		for(boost::ptr_list<MenuButton>::iterator it = m_buttons.begin();
			it != m_buttons.end(); ++it)
		{
			it->paint(painter);
		}
		for(boost::ptr_list<MenuElement>::iterator it = m_elems.begin();
			it != m_elems.end(); ++it)
		{
			it->paint(painter);
		}
		painter.restore();
		painter.end();
	}
}
