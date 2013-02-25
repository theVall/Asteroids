/**
 * @file MainWindow.hpp
 * @author Gruppe 2
 */

#ifndef MAIN_WINDOW_HPP_
#define MAIN_WINDOW_HPP_

#include <QMainWindow>
#include <QMenuBar>
#include <QtGui>

#include "RenderFrame.hpp"
#include "io/TriangleMeshFactory.hpp"
#include "io/Read3DS.hpp"
#include "rendering/TexturedMesh.hpp"
#include "control/Logic.hpp"

/**
 * @brief   A simple main window class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        /**
         * @brief Default Ctor to create a main window with an initial size of 800 x 600 Pixels
         */
        MainWindow(QMainWindow *parent = 0);

        /**
         * @brief   Dtor
         */
        ~MainWindow();

        /**
         * @brief starts the logic
         */
        void startLogic();

    protected:
        /**
         * @brief ends all
         */
        void closeEvent(QCloseEvent *event);

private:
        // custom QGLWidget class to display the scene
        RenderFrame* m_renderFrame;

        // main window logic
        Logic* m_logic;

        // main menu for open and quit operations
        QMenu* m_fileMenu;
};

#endif /* MainWindow.hpp */
