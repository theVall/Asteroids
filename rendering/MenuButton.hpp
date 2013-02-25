#ifndef MENUBUTTON_H
#define MENUBUTTON_H

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

#include "MenuElement.hpp"

/**
 * @brief represents a button on the menu
 */
class MenuButton : public MenuElement 
{
	public:
    /**
     * @brief Ctor
     * @param *parent pointer to parent object
     * @param *image pointer to background image
     * @param id button ID
     */
		MenuButton(QWidget *parent, QImage *image, int id = buttonid);
    
    /**
     * @brief Ctor
     * @param *parent pointer to parent object
     * @param test button text
     * @param id button ID
     */
		MenuButton(QWidget *parent, std::string text, int id = buttonid);
    
    /**
     * @brief Ctor
     * @param *parent pointer to parent object
     * @param id button ID
     */
		MenuButton(QWidget *parent, int id = buttonid);
		
    /**
     * @brief Dtor
     */
    ~MenuButton();

    /**
     * @brief paints the button
     * @param painter reference to QPainter
     */
		void paint(QPainter &painter);

    /**
     * @brief mounse event handler
     * @param event Qt mouse event
     */
		void mouseEvent(QMouseEvent* event);

    /**
     * @brief enable menu button
     */
		void enable();

    /**
     * @brief disable menu button
     */
		void disable();

    /** 
     * @brief enum of the button states
     */
		enum buttonState{NORMAL, OVER, CLICKED};
		
    /** 
     * @brief get button ID
     */
    int getId();

    //state of button
		int m_state;

	private:
		
    //mouse over image
    QImage *m_over;
		
    //ID
    int m_id;
		
    //button ID
    static int buttonid;
		
    //indicates wheather button is active
    bool m_active;
};

#endif /* MenuButton.hpp */

