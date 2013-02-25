#include "MenuElement.hpp"
#include <iostream>

MenuElement::MenuElement(QWidget *parent) 
//	: QPushButton(parent)
{
	m_parent = parent;
	m_image = new QImage("res/menu/element.png");
	m_rect = new QRect(m_image->rect());
	m_text = new QString();
	m_textsize = 16;
	m_font = new QFont("Helvetica [Cronyx]", m_textsize);

}
MenuElement::MenuElement(QWidget *parent, QImage* image) 
{
	m_parent = parent;
	m_image = image;
	m_rect = new QRect(m_image->rect());
	m_text = new QString();
	m_textsize = 16;
	m_font = new QFont("Helvetica [Cronyx]", m_textsize);
}

MenuElement::MenuElement(QWidget *parent, std::string text) 
{
	m_parent = parent;
	m_image = new QImage("res/menu/element.png");
	m_rect = new QRect(m_image->rect());
	m_textsize = 16;
	m_text = new QString(text.c_str());
	m_font = new QFont("Helvetica [Cronyx]", m_textsize);
}
MenuElement::~MenuElement()
{
	delete m_image;
	delete m_rect;
	delete m_text;
	delete m_font;
}

void MenuElement::setText(std::string &text)
{
	delete m_text;
	m_text = new QString(text.c_str());
}

void MenuElement::setText(QString text)
{
	delete m_text;
	m_text = new QString(text);
}

void MenuElement::setText(std::string &text, int size)
{
	delete m_text;
	m_text = new QString(text.c_str());
	m_textsize = size;
	m_font = new QFont("Helvetica [Cronyx]", m_textsize);
}

QImage* MenuElement::getImage()
{
	return m_image;
}

void MenuElement::setRect(QRect *rect)
{
	m_rect = rect;
}

QRect* MenuElement::getRect()
{
	return m_rect;
}
/*
void MenuElement::setQImage(QImage *qImage)
{
	m_image = image;
}
*/
void MenuElement::paint(QPainter &painter)
{
	painter.drawImage(*m_rect, *m_image);
	painter.setPen(QColor(130, 130, 230));
	painter.setFont(*m_font);
	painter.drawText(*m_rect, Qt::AlignCenter,*m_text);
}
