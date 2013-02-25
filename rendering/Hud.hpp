/**
 * @file Hud.hpp
 * @author Jannis Eichborn (jeichborn@uos.de)
 * @author Felix Schueler (fschueler@uos.de)
 */

#ifndef HUD_HPP_
#define HUD_HPP_

#include <GL/gl.h>        /* Header File For The OpenGL32 Library */
#include <GL/glu.h>       /* Header File For The GLu32 Library */

#include "io/TextureFactory.hpp"
#include "rendering/Body.hpp"
#include "math/glVector.hpp"

#include <vector>
#include <utility>

#include <QGLWidget>
#include <QPainter>
#include <QRectF>
#include <QImage>
#include <QString>
#include <QPointF>
#include <QBrush>
#include <QColor>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QFont>
#include <QImage>
#include <QMutex>
#include <iostream>
#include <string>
#include <sstream>

/**
 * @brief Class used to update and render the hud
 */
class Hud
{
public:

    /**
     * @brief Ctor.
     */
    Hud(QGLWidget *parent);

    /**
     * @brief Dtor.
     */
    ~Hud();

    /**
     * @brief Renders the hud ontop of the 3D environment
     */
    void paint();

    /**
     * @brief Sets the current coordinates of the asterois
     * @param set Contains all coordinates
     */
    void setBodies(std::vector<glVector<float> > *vec);

    /**
     * @brief Updates the position & orientation of the fighter
     * @param Updates the position and axis of the fighter
     */
    void setFighter(glVector<float> *info);

    /**
     * @brief sets lifepoints
     * @param p The lost LP
     */
    void setLP(int p);

    /**
     * @brief Setsthe player's points
     * @param s The current score
     */
    void setScore(int s);

    /**
     * @brief Sets the energy of the weapon
     * @param v The current energy
     */
    void setWeaponStatus(int e);

    /**
     * @brief Increases the level
     * @param level The current level the player is in
     */
    void setLvl(int level);

    /**
     * @brief Sets the speed of the ship to be shown
     * @param speed The current speed
     */
    void setSpeed(double speed);

    /**
     * @brief Sets the maximal Speed of the fighter
     * @param max The maximal speed
     */
    void setMaxSpeed(double max);

    /**
     * @brief adpats the parameters to the screen size
     */
    void resize();

    /**
     * @brief Sets the active weapon
     */
    void setActiveWeapon(int type);

    /**
     * @brief Sets the mutex to be locked on
     */
    void setPosMutex(QMutex* mutex);

    void setVisible(bool val);

    void reset();

    void setPlayerName(QString name);


private:
    /**
     * @brief maps the coordinates to the egocentric coordinate system
     */
    void mapBodies();

    /**
     * @brief Prints game over
     * @param The printer which is supposed to print this
     */
    void paintGameOver(QPainter* painter);

    /**
     * @brief Prints the needed texts
     * @param The printer which is supposed to print this
     */
    void paintTexts(QPainter* painter);

    /**
     * @brief Paints the radar
     * @param The printer which is supposed to print this
     */
    void paintRadar(QPainter* painter);

    /**
     * @brief Paints the life bars
     * @param The printer which is supposed to print this
     */
    void paintLife(QPainter* painter);

    /**
     * @brief Paints Weapon and Speed bars
     * @param The printer which is supposed to print this
     */
    void paintBars(QPainter* painter);

    // The QGLWidget the hud was built from
    QGLWidget *m_parent;

    // The display height
    int m_height;

    // The display width
    int m_width;

    // The diameter of the radar
    int m_diameter;

    // The radius of the radar
    int m_radius;

    // The lifepoints of the ship
    int m_lp;

    // The gained points of the player
    int m_score;

    // The power of the weapon
    int m_weaponStatus;

    // The current level the player is in
    int m_level;

    // The current position of the fighter
    glVector<float> m_fighterPos;

    // The current X-orientation of the fighter, used for normalization
    glVector<float> m_fighterDirX;

    // The current Y-orientation of the fighter, used for normalization
    glVector<float> m_fighterDirY;

    // The current Z-orientation of the fighter, used for normalization
    glVector<float> m_fighterDirZ;

    // Contains the maximal speed of the fighter
    double m_maxSpeed;

    // Contains the current speed of the fighter
    double m_speed;

    // BodySet to represent all positions in space
    std::vector<glVector<float> > *m_bodies;

    // Holds the relative coordinates of asteroids above the ship
    std::vector<glVector<float> > m_bodiesAbove;

     // Holds the relative coordinates of asteroids below the ship
    std::vector<glVector<float> > m_bodiesBelow;

    // The standard colour of the hud
    QColor *m_colour;

    // Sets the visibilty of the hud (used for flashing)
    bool m_visible;

    // Contains the number of flashs left to show
    int m_hitFlashs;

    // Holds the time a flash is still having to last
    int m_flashTime;

    // States which weapon is active
    int m_activeWeapon;

    //Images
    QImage* m_laserIm;
    QImage* m_plasmaIm;

    QMutex* m_posMutex;

    bool m_enabled;

    int m_newLvl;

    QString m_playerName;
};
#endif /* Hud.hpp */
