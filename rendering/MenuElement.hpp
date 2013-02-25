#ifndef MENUELEMENT_H
#define MENUELEMENT_H

#include <QImage>
#include <QPixmap>
#include <QIcon>
#include <QPainter>
#include <QRect>
#include <QGLWidget>
#include <QWidget>
#include <QPushButton>
#include <QPalette>
#include <QMouseEvent>
#include <QColor>
#include <string>

class MenuElement //: public QPushButton
{
	public:
		MenuElement(QWidget *parent, QImage *image);
		MenuElement(QWidget *parent, std::string text);
		MenuElement(QWidget *parent);
		~MenuElement();

		void setRect(QRect *rect);
		QRect* getRect();
		void paint(QPainter &painter);
		QImage* getImage();

		void setText(QString string);
		void setText(std::string &text);
		void setText(std::string &text, int size);
	protected:
		QRect *m_rect;
		QImage *m_image;
		QString *m_text;
		QWidget *m_parent;
		QFont* m_font;
		int m_textsize;
};

#endif /* MenuElement.hpp */

