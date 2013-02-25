/**
 * @file RenderFrame.hpp
 * @file Gruppe 2
 */

#ifndef RENDERFRAME_HPP_
#define RENDERFRAME_HPP_

#include <iostream>
#include <set>
#include <QGLWidget>
#include <QTimer>
#include <QMutex>
#include <QImage>
#include <set>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QInputDialog>
#include <QString>

#include "rendering/Asteroid.hpp"
#include "rendering/Bullet.hpp"
#include "view/Camera.hpp"
#include "rendering/TriangleMesh.hpp"
#include "rendering/Skybox.hpp"
#include "math/Global.hpp"
#include "rendering/Hud.hpp"
#include "rendering/Fighter.hpp"
#include "rendering/BodySet.hpp"
#include "rendering/MenuSet.hpp"
#include "rendering/PowerUp.hpp"
#include "rendering/TexturedMesh.hpp"
#include "io/Read3DS.hpp"

class RenderFrame : public QGLWidget
{
    Q_OBJECT

    public:
            /**
             * @brief Ctor.
             */
            RenderFrame(QWidget *parent = 0);

            /**
             * @brief	Dtor.
             */
            ~RenderFrame();

           /**
            * @brief renders everything
            */
           void renderAll();

            /**
             * @brief fighter getter
             * @return current fighter
             */
            Fighter* getFighter();

            /**
             * @brief bodyset setter
             * @param bs new bodyset
             */
           void setBodySet(BodySet* bs);

           /**
            * @brief bodyset getter
            * @return current bodyset
            */
           BodySet* getBodySet();

           /**
            * @brief skybox setter
            * @param sb new skybox
            */
           void setSkybox(Skybox* sb);

           /**
            * @brief skybox getter
            * @return current skybox
            */
           Skybox* getSkybox();

           /**
            * @brief hud setter
            * @param h new hud
            */
           void setHud(Hud* h);

           /**
            * @brief hud getter
            * @return current hud
            */
           Hud* getHud();

           /**
            * @brief camera setter
            * @param h new camera
            */
           void setCamera(Camera* c);

           /**
            * @brief camera getter
            * @return current camera
            */
           Camera* getCamera();

           /**
            * @brief Menu getter
            * @return menu
            */
           MenuSet* getMenuSet();

           static void setMaterials(Asteroid* a);

           static void setMaterials(Bullet* b);

           static void setMaterials(PowerUp* p);
           
           static void setLaserMaterials(Bullet* b);

           void stop();

           // timer
           QTimer *m_timer;

           // set of all currently pressed keys
           std::set<Qt::Key> m_pressedKeys;

           boost::ptr_list<QMouseEvent*> m_mouseEvents;

           //
           bool m_wait;

           // locks critical code
           QMutex m_key_mutex;

	   QMutex m_mouse_mutex;

           // bullet timeout
           int m_check;

	   static Asteroid* getNewAsteroid(glVector<float> pos, glVector<float> dir, float size, double speed);
	   static Asteroid* getNewAsteroid(glVector<float> pos);

	   static Bullet* getNewBullet(glVector<float> pos, glVector<float> dir, double speed, int range, int damage);
		static Bullet* getNewLaserBullet(glVector<float> pos, glVector<float> dir, double speed, int range, int damage);
	   static PowerUp* getNewPowerUp(glVector<float> pos, glVector<float> dir, int type, double speed, long lifetime);

	   static void setMesh(TexturedMesh* mesh);

     QString getPlayerName();
     QTimer* m_nameTimer;
       bool m_inputAccepted;
 public slots:
     void callPlayerName();
     void setAccepted();

protected:
        /**
         * @brief initializes glut
         */
        void initializeGlut();

        /**
         * @brief 	The OpenGL initialization method. This is always called before
         * 			the fist paintGL operation, so all necessary OpenGL initialization
         * 			should be done here
         */
        void initializeGL();

        /**
         * @brief	The resize method for OpenGL related stuff
         */
        void resizeGL(int w, int h);

        /**
         * @brief	The render function.
         */
        void paintGL();

        /**
         * @brief	Our custom key press handler
         *
         * @param	e	The generated key event description
         */
        void keyPressEvent(QKeyEvent* e);

        /**
         * @brief	Our custom key release event handler
         *
         * @param	e	The generated key event description
         */
        void keyReleaseEvent(QKeyEvent* e);

        /**
         * @brief	Our custom mouse event handler
         *
         * @param	e	The generated mouse event description
         */
        void mouseMoveEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* event);
        /**
         * @brief   Moves the camera in the x-y plane if dx and / or dy are > MOUSE_SENSITY
         *
         * @param 	dx 	The number of pixels the mouse has moved in x direction
         * @param	dy 	The number of pixels the mouse has moved in y direction
         */
        void moveCamXY(int dx, int dy);

        /**
         * @brief   Moves the camera in the z-x plane dy is > MOUSE_SENSITY
         *
         * @param 	dx 	The number of pixels the mouse has moved in x direction
         * @param	dy 	The number of pixels the mouse has moved in y direction
         */
        void moveCamZ(int dy);

        /**
         * @brief   Turns the camera around the current up-axis if
         * 			dx and / or dy are > MOUSE_SENSITY
         *
         * @param 	dx 	The number of pixels the mouse has moved in x direction
         * @param	dy 	The number of pixels the mouse has moved in y direction
         */
        void moveCamHead(int dx, int dy);

        // camera object to display the scene
        Camera  m_cam;

        // a skybox for the scene
        Skybox* m_skybox;

        // head up display
        Hud*    m_hud;

        // menu
        MenuSet*   m_menuset;

        // last x position of the mouse
        int     m_mouseX;

        // last y position of the mouse
        int     m_mouseY;

        // set containing all bodies in space except the fighter
        BodySet* m_bodies;

        // fighter
        Fighter* m_fighter;

        // Prtotype big asteroid
        static Asteroid* m_asteroid;

        static Bullet* m_bullet;
        static Bullet* m_laserBullet;
        
        static PowerUp* m_powerUp;

	static Read3DS* m_asteroidReader;
	static Read3DS* m_bulletReader;
	static Read3DS* m_laserBulletReader;
	static Read3DS* m_powerupReader;

  QInputDialog*  m_inputDialog;
  QString m_playerName;

};

#endif /* RenderFrame.hpp */
