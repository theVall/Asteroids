#include "MenuButton.hpp"
#include <iostream>
int MenuButton::buttonid = 1;

MenuButton::MenuButton(QWidget *parent, int id) 
	: MenuElement(parent), m_id(id), m_active(true)
{
	m_state = NORMAL;
	m_image = new QImage("res/menu/button.png");
	m_over = new QImage("res/menu/buttonSelected.png");
}

MenuButton::MenuButton(QWidget *parent, QImage *image, int id) 
	: MenuElement(parent, image), m_id(id), m_active(true)
{
	m_state = NORMAL;
	m_over = new QImage("res/menu/buttonSelected.png");
}

MenuButton::MenuButton(QWidget *parent, std::string text, int id) 
	: MenuElement(parent, text), m_id(id), m_active(true)
{
	m_state = NORMAL;
	m_image = new QImage("res/menu/button.png");
	m_over = new QImage("res/menu/buttonSelected.png");
}

MenuButton::~MenuButton()
{
	delete m_image;
	delete m_rect;
	delete m_text;
	delete m_font;
	delete m_over;
}

int MenuButton::getId()
{
	return m_id;
}

void MenuButton::mouseEvent(QMouseEvent* event)
{
	if(m_state == CLICKED) return;

	if(m_rect->contains(event->pos()))
	{
	        if(event->button() != Qt::LeftButton)
		{
			m_state = OVER;
		}
		else
		{	
			m_state = CLICKED;
		}
	}
	else
	{
		m_state = NORMAL;
	}	
}

void MenuButton::disable()
{
	m_active = false;
}

void MenuButton::enable()
{
	m_active = true;
}

void MenuButton::paint(QPainter &painter)
{
	if(!m_active) return;
	switch(m_state)
	{
		case OVER:
			painter.drawImage(*m_rect, *m_over);
		break;
		default:
		case NORMAL:
			painter.drawImage(*m_rect, *m_image);
		break;
	}
	painter.setPen(QColor(130, 130, 230));
	painter.setFont(*m_font);
	painter.drawText(*m_rect, Qt::AlignCenter,*m_text);
}
