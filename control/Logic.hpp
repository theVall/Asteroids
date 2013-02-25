/**
 * @file Logic.hpp
 *
 * @date 21.02.2012
 * @author Gruppe2
 */

#ifndef LOGIC_H
#define LOGIC_H

//c++ stuff
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>

//intern stuff
#include "rendering/TriangleMesh.hpp"
#include "rendering/TexturedMesh.hpp"
#include "rendering/MenuSet.hpp"
#include "rendering/Skybox.hpp"
#include "rendering/BodySet.hpp"
#include "rendering/Shield.hpp"
#include "rendering/Particle.hpp"
//Armory
#include "rendering/Weapon.hpp"
#include "rendering/Laser.hpp"
#include "rendering/Plasma.hpp"

#include "io/LevelReader.hpp"
#include "io/LevelMaker.hpp"
#include "io/Read3DS.hpp"
#include "io/SoundOutput.hpp"
#include "io/HighScore.hpp"

#include "view/RenderFrame.hpp"

//Qt related stuff
#include <QThread>
#include <QMutex>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QString>
#include <QInputDialog>

class Logic : public QThread
{
    public:
        enum Key {TURNUP=1, TURNDN, TURNLE, TURNRI, ROTLEF, ROTRIG, MOVEUP, MOVEDN, SHOOT, CHANGEWEAPON, MENUBREAK};
	enum Button {MENU_START=1, MENU_NEWGAME, MENU_PLAYERNAME, MENU_CONTINUE, MENU_HIGHSCORE, MENU_CONTROLS, MENU_BACKMAIN};
        /**
         * @brief Ctor
         */
        Logic(RenderFrame* rf);

        /**
         * @brief Dtor
         */
        ~Logic();

        /**
         * @briefs sets m_running to false
         */
        void stop();

    protected:
        /**
         * @brief starts a new game in Level 1 with a new Fightermodel
         */
        void newGame(QString filename);

        /**
         * @brief MainLOOP to update and handle key actions
         */
        void run();

        /**
         * @brief loads the next level from the given xml file and renders it
         */
        void nextLevel();

        /**
         * @brief Checks collisions between fighter and asteroids
         */
        void collisionCheck();

        /**
         * @brief initialises m_keys with default values
         */
        void initKeys();

        /**
         * @brief assigns a movement to a specified key
         * @param k new key
         * @param v movement
         */
        void setKey(Qt::Key k, Key v);

        /**
         * @brief performs the movement of a specified key
         */
        void doKeyActions();

        /**
         * @brief creates new Bullet Object
         */
        void createBullet();


        /**
         * @brief perform actions of the menu
         */
        void doMenuActions();

        /**
         * @brief shatters a small asteroid in particles dependant on radius
         * @param pos position of exploding Asteroid
         * @param rad radius of asteroid
         */
        void explodeAsteroid(glVector<float> pos, int rad);

        /**
         * @brief splits asteroid into 3 asteroids
         */
        void splitAsteroids(glVector<float> pos, glVector<float> dir, double speed);

        /**
         * @brief halts the game and shows the menu
         */
        void gameBreak();

       /**
         * @brief resume the game and hide the menu
         */
        void gameContinue();

        void setPlayerName();

	void newHighScore();
    private:

// ################ thread data ##################

        //mutex for qThread
        QMutex mutex;

        // thread running?
        bool m_running;

// ################ pointer ##################

        // pointer to fighter
        Fighter* m_fighter;

        // pointer to skybox
        Skybox* m_skybox;

        // pointer to set of the bodys appearing on the screen
        BodySet* m_bodies;

        // pointer to head up display
        Hud* m_hud;

        // pointer to xml levelReader
        LevelReader* m_levelReader;

        // pointer to qt widget openGL render frame
        RenderFrame* m_renderFrame;

        // pointer to camera
        Camera* m_cam;

        // High score
        HighScore* m_highScore;

        // sound output
        SoundOutput sound;

        //menu button pointer
        MenuButton* m_startbutton;
	MenuButton* m_menu_button_continue;
        Menu* m_menu_highscore;
	QImage* m_menu_scoreImage;

	MenuElement* m_menu_highscores[5];
	MenuElement* menu_score;
        MenuSet* m_menuset;

        Menu* m_menu_main;

        Menu* m_menu_start;

	Menu* m_menu_newHighScore;
        // playing?
        bool m_playing;

// ################# game data #################

        //value for current level
        int m_level;

        //value for current score
        int m_score;

        //value to get to the next level
        int m_levelbarrier;

        //value for current life points
        int m_LP;

        //value for the status of the weapon
        float m_weaponStatus;

        //value for the energy consumption of the weapon
        int m_weaponEnergy;

        //value for the weapon refreshing rate
        float m_weaponRefresh;

        //value for initial bullet speed
        int m_bulletspeed;

        //value for damage of the fighter
        int m_damage;

        //value which indicates wheather shield is enabled
        bool m_shield;

        // values are the specified movement to the keys
        std::map<Qt::Key, Key> m_actions;

        QString m_playerName;


        //value for radius of big asteroid
        int m_radBigAsteroid;

        //value for radius of small asteroid
        int m_radSmallAsteroid;

	bool gameover;
};

#endif /* Logic.hpp */
