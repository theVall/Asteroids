/**
 * @file Hud.cpp
 * @author Jannis Eichborn (jeichborn@uos.de)
 * @author Felix Schueler (fschueler@uos.de)
 */

#include "Hud.hpp"

Hud::Hud(QGLWidget *parent)
{
    // Set the parent and the initial m_bodies
    m_parent = parent;
    m_height = m_parent->height();
    m_width  = m_parent->width();
    m_bodies = 0;
    m_posMutex = 0;
    m_enabled = false;
    // Make the initial settings of the instruments
    m_lp = 100;
    m_score = 0;
    m_weaponStatus = 100;
    m_level = 1;
    m_visible = true;
    m_hitFlashs = 0;
    m_flashTime = 15;
    // Initialize the ship
    glVector<float> x(1,0,0), y(0,1,0), z(0,0,1), pos(0,0,0);
    m_fighterPos  = pos;
    m_fighterDirX = x;
    m_fighterDirY = y;
    m_fighterDirZ = z;
    m_speed=0;
    m_maxSpeed = 1;
    //Set colour
    m_colour = new QColor(100,200,0);
    m_radius = 1;
    m_diameter = 2;
    // Starting with a new level
    m_newLvl = 155;
    // Set Weapon
    m_activeWeapon = 1;
    // Playername
    m_playerName = "Player";
}

Hud::~Hud()
{
    m_bodies->clear();
    m_bodiesAbove.clear();
    m_bodiesBelow.clear();
    delete m_laserIm;
    delete m_plasmaIm;
    delete m_colour;
}

void Hud::resize()
{
    m_height = m_parent->height();
    m_width = m_parent->width();
    m_diameter = m_width/5;
    if(m_diameter > 300)
    {
        m_diameter = 300;
    }
    m_radius = m_diameter/2;
}

void Hud::paint()

{   if(m_enabled)
    {
        // Set up painter
        QPainter painter(m_parent);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);

        // Print game over if necessary
        if (m_lp <= 0)
        {
            paintGameOver(&painter);
            // And quit
            return;
        }

        // Do painting jobs
        paintTexts(&painter);
        paintRadar(&painter);
        paintLife(&painter);
        paintBars(&painter);

        // Finish the painter
        painter.end();
    }
}


void Hud::paintGameOver(QPainter* painter)
{
    QString text = "Game Over";
    QFont font("Helvetica", 50, -1,false);
    painter->setFont(font);
    painter->setPen(QPen(Qt::red,5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawText(m_width/4, m_height/8*3,m_width/2,m_height/4, Qt::AlignCenter , text);
}


void Hud::paintTexts(QPainter* painter)
{
    // Set style
    QFont font("Tahoma", 15, -1,false);
    painter->setFont(font);
    painter->setPen(QPen(*m_colour, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    // POINTS
    std::string s;
    std::stringstream out;
    out << m_score;
    s = out.str();
    QString text(s.c_str());
    painter->drawText(10,10, m_width/5, m_height/10, Qt::AlignLeft, text);



    //LEVEL
    std::stringstream out1;
    out1.clear();
    out1 << "LVL " << m_level;
    s = out1.str();
    QString text2(s.c_str());
    if(m_newLvl > 0)
    {
        painter->setPen(QPen(QColor(100 + m_newLvl,200 - m_newLvl, 0), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        m_newLvl --;
    }
    painter->drawText(m_width - (m_width/5) -10, 10, m_width/5, m_height/10, Qt::AlignRight, text2);

    // CROSS
    painter->setPen(QPen(*m_colour,1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(m_width/2, m_height/2 - m_height/50 , m_width/2, m_height/2 - m_height/100);
    painter->drawLine(m_width/2, m_height/2 + m_height/100 , m_width/2, m_height/2 + m_height/50);
    painter->drawLine(m_width/2 - m_height/100, m_height/2 , m_width/2 - m_height/50, m_height/2);
    painter->drawLine(m_width/2 + m_height/100, m_height/2 , m_width/2 + m_height/50, m_height/2);

    // Change Style
    QFont font1("Tahoma", 10, -1,false);
    painter->setFont(font1);

    // SPEED
    // Line
    int y1 = m_height - m_radius - 10;
    int y2= y1 - m_height/20;
    int x = 20 + m_width/30;
    painter->drawLine(10,y1, m_width/10, y1);
    // Text
    text = "Speed";
    painter->drawText(x, y2, 100, m_height/20, Qt::AlignLeft | Qt::AlignBottom , text);
    // Value
    y2 += m_height/20+10;
    std::stringstream out3;
    out3 <<  int(-(m_speed/m_maxSpeed * 100 ) + 0.5) << " %";
    s = out3.str();
    QString text4(s.c_str());
    painter->drawText(x, y2, 100, m_height/20, Qt::AlignLeft | Qt::AlignTop, text4);

    // WEAPON
    //Line
    painter->drawLine(m_width - m_width/10 - 10, y1, m_width - 10, y1);
    // Text
    y2 = y1 - m_height/20;
    x = m_width - 10 - m_width/30 - 100;
    text = "Weapon";
    painter->drawText(x, y2, 90, m_height/20 , Qt::AlignRight | Qt::AlignBottom , text);
    // Value
    y2 += m_height/20+10;
    std::stringstream out2;
    out2 <<  m_weaponStatus << " %";
    s = out2.str();
    QString text3(s.c_str());
    painter->drawText(x, y2, 90, m_height/20, Qt::AlignRight | Qt::AlignTop, text3);

    //PLAYERNAME
    painter->drawText(10, m_height- 10 - m_height/20, 300, m_height/20, Qt::AlignLeft, m_playerName);
}


void Hud::paintRadar(QPainter* painter)
{
    // Map the positions
    if(m_bodies != NULL)
    {
        mapBodies();
    }

    // The range in which things can be seen
    int maxDist = 30000;

    // The upper left corner of the radar as reference
    int x = m_width/2 - m_radius;
    int y = m_height - m_diameter - 10;

    // Paint the first vertical ellipse
    QRectF rectangleV1(x,y,m_diameter, m_diameter);
    QRadialGradient gradientRad(x + m_radius, y + m_radius, m_radius, m_radius ,m_radius);
    gradientRad.setColorAt(0.0,Qt::transparent);
    gradientRad.setColorAt(1.0,Qt::gray);
    painter->setBrush(gradientRad);
    painter->setPen(QPen(Qt::black,1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawEllipse(rectangleV1);

    //Ellipse
    int yi = y + m_radius;
    int heightEllipse = m_diameter/5;

    // Paint all vectors below the ship
    painter->setBrush(QBrush(QColor(255,150,0), Qt::SolidPattern));
    std::vector<glVector<float> >::iterator it;
    for(it = m_bodiesBelow.begin(); it != m_bodiesBelow.end(); it++)
    {
        // Check the distance
        if( sqrt((*it) * (*it)) < maxDist)
        {
            painter->setPen(QPen(Qt::black,1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            int x1 = x + (m_radius) + ((*it)[1] * (m_radius) /maxDist);
            int y1 = y + m_radius + (*it)[0] * (heightEllipse/2) /maxDist;
            int y2 = y1 - ((*it)[2]*(m_radius)/maxDist);
            painter->drawLine(x1,y1,x1,y2);
            painter->setPen(Qt::NoPen);
            QRectF rectangleP(x1-5,y2-5, 8, 8);
            painter->drawEllipse(rectangleP);
        }
    }

    //Paint the outer horizontal ellipse for the sphere effect
    yi -= heightEllipse/2;
    painter->setPen(QPen(Qt::black,1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(gradientRad);
    QRectF rectangleH1(x,yi,m_diameter, heightEllipse);
    painter->drawEllipse(rectangleH1);

    // Paint the spacecraft as a dot in the middle
    QRectF center(m_width/2 - m_width/140, y + m_radius-2, m_width/70,4);
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(*m_colour, Qt::SolidPattern));
    painter->drawEllipse(center);

    // Lines above
    painter->setPen(QPen(Qt::white,1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(QBrush(QColor(255,255,0), Qt::SolidPattern));
    for(it = m_bodiesAbove.begin(); it != m_bodiesAbove.end(); it++)
    {
        // Check the distance
        if( sqrt((*it) * (*it)) < maxDist)
        {
            painter->setPen(QPen(Qt::black,1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            int x1 = x + (m_radius) + ((*it)[1] * (m_radius) /maxDist);
            int y1 = y + m_radius + (*it)[0] * (heightEllipse/2) /maxDist;
            int y2 = y1 - ((*it)[2]*(m_radius)/maxDist);
            painter->drawLine(x1,y1,x1,y2);
            painter->setPen(Qt::NoPen);
            QRectF rectangleP(x1-5,y2-5, 8, 8);
            painter->drawEllipse(rectangleP);
        }
    }
}


void Hud::paintLife(QPainter* painter)
{
    int x = m_width/2 - m_radius;
    int y = m_height - m_diameter - 10;

    if(m_hitFlashs > 0)
    {
        if(m_flashTime > 0)
        {
            m_flashTime--;
        }
        else
        {
            m_flashTime = 15;
            m_hitFlashs--;
            m_visible = !m_visible;
        }
    }
    else(m_visible = true);

    // The offset for the indention
    int offset = 30;
    // The distane of the bars to one another
    int distance = 20;
    // Width for one healthbar dependent on size of sphere
    int widthHealth = ((m_width/2 - m_radius - 3*distance) /2)/8 ;
    // Scaling factor to make smaller bars
    float scale = 0.1f;
    // Set the filling
    painter->setPen(Qt::NoPen);
    // Set the filling colour according to the lifepoints
    QLinearGradient grad1(0, y, m_width, m_height);
    grad1.setColorAt(0.1, Qt::transparent);
    grad1.setColorAt(0.5, QColor(255-m_lp*1.55, 45 + m_lp*1.55,0,255));
    grad1.setColorAt(0.9, Qt::transparent);
    painter->setBrush(grad1);

    // Make the lifebars if necessary (enough LP)
    if(m_lp > 0 && m_visible)
    {

        QPointF pointsLeft[6] =
        {
            QPointF(x                           , m_height-m_diameter+scale*m_diameter),
            QPointF(x-offset                    , m_height-(m_diameter)/2 -10),
            QPointF(x                           , m_height-20-scale*m_diameter),
            QPointF(x-widthHealth               , m_height-20-scale*m_diameter),
            QPointF(x-offset-widthHealth        , m_height-m_radius -10),
            QPointF(x-widthHealth               , m_height-m_diameter +scale*m_diameter)
        };

        painter->drawPolygon(pointsLeft, 6);

        QPointF pointsRight[6] =
        {
            QPointF(x+m_diameter                    , m_height- m_diameter+scale*m_diameter),
            QPointF(x + m_diameter + offset         , m_height - m_radius -10),
            QPointF(x+ m_diameter                   , m_height-20-scale*m_diameter),
            QPointF(x+m_diameter+widthHealth        , m_height-20-scale*m_diameter),
            QPointF(x+m_diameter+offset+widthHealth , m_height - m_radius -10),
            QPointF(x+m_diameter+widthHealth        , m_height-m_diameter+scale*m_diameter)
        };
        painter->drawPolygon(pointsRight, 6);
    }
    if(m_lp > 25 && m_visible)
    {
        scale = 0.15f;
        x -= widthHealth + distance;
        QPointF pointsLeft[6] =
        {
            QPointF(x                           , m_height- m_diameter + scale*m_diameter),
            QPointF(x-offset                    , m_height-m_radius -10),
            QPointF(x                           , m_height-20 - scale*m_diameter),
            QPointF(x-widthHealth               , m_height-20 - scale*m_diameter),
            QPointF(x-offset-widthHealth        , m_height-m_radius -10),
            QPointF(x-widthHealth               , m_height- m_diameter + scale*m_diameter )
        };
        painter->drawPolygon(pointsLeft, 6);

        x += 2*(widthHealth + distance);
        QPointF pointsRight[6] =
        {
            QPointF(x+m_diameter                    , m_height- m_diameter + scale*m_diameter),
            QPointF(x + m_diameter + offset         , m_height - m_radius -10),
            QPointF(x+ m_diameter                   , m_height-20 - scale*m_diameter),
            QPointF(x+m_diameter+widthHealth        , m_height-20 - scale*m_diameter),
            QPointF(x+m_diameter+offset+widthHealth , m_height - m_radius -10),
            QPointF(x+m_diameter+widthHealth        , m_height-m_diameter +scale*m_diameter)
        };
        painter->drawPolygon(pointsRight, 6);

        x -= widthHealth + distance;
    }

    if(m_lp > 50 && m_visible)
    {
        scale = 0.2f;
        x -= 2*(widthHealth + distance);
        QPointF pointsLeft[6] =
        {

            QPointF(x                           , m_height-m_diameter + scale*m_diameter),
            QPointF(x-offset                    , m_height-(m_diameter)/2 -10),
            QPointF(x                           , m_height-20 - scale*m_diameter),
            QPointF(x-widthHealth               , m_height-20 - scale*m_diameter),
            QPointF(x-offset-widthHealth        , m_height-m_radius -10),
            QPointF(x-widthHealth               , m_height-m_diameter + scale*m_diameter)
        };
        painter->drawPolygon(pointsLeft, 6);

        x += 2 *(2*(widthHealth + distance));
        QPointF pointsRight[6] =
        {
            QPointF(x+m_diameter                    , m_height- m_diameter + scale*m_diameter),
            QPointF(x + m_diameter + offset         , m_height - m_radius -10),
            QPointF(x+ m_diameter                   , m_height-20 - scale*m_diameter),
            QPointF(x+m_diameter+widthHealth        , m_height-20 - scale*m_diameter),
            QPointF(x+m_diameter+offset+widthHealth , m_height - m_radius -10),
            QPointF(x+m_diameter+widthHealth        , m_height-m_diameter + scale*m_diameter)
        };
        painter->drawPolygon(pointsRight, 6);
        x -= 2*(widthHealth + distance);
    }
    if(m_lp > 75 && m_visible)
    {
        scale = 0.25f;
        x -= 3*(widthHealth + distance);
        QPointF pointsLeft[6] =
        {

            QPointF(x                           , m_height-m_diameter + scale*m_diameter),
            QPointF(x-offset                    , m_height-(m_diameter)/2 -10),
            QPointF(x                           , m_height-20-scale*m_diameter),
            QPointF(x-widthHealth               , m_height-20-scale*m_diameter),
            QPointF(x-offset-widthHealth        , m_height-m_radius -10),
            QPointF(x-widthHealth               , m_height-m_diameter +scale*m_diameter)
        };
        painter->drawPolygon(pointsLeft, 6);

        x += 3 *(2*(widthHealth + distance));
        QPointF pointsRight[6] =
        {
            QPointF(x+m_diameter                    , m_height- m_diameter+scale*m_diameter),
            QPointF(x + m_diameter + offset         , m_height - m_radius -10),
            QPointF(x+ m_diameter                   , m_height-20-scale*m_diameter),
            QPointF(x+m_diameter+widthHealth        , m_height-20-scale*m_diameter),
            QPointF(x+m_diameter+offset+widthHealth , m_height - m_radius -10),
            QPointF(x+m_diameter+widthHealth        , m_height-m_diameter+scale*m_diameter)
        };
        painter->drawPolygon(pointsRight, 6);
        x -= 3*(widthHealth + distance);
    }
}


void Hud::paintBars(QPainter* painter)
{
    int y1 = m_height - m_radius - 10;

    // SPEED
    painter->setPen(Qt::NoPen);
    // Set length of the bar
    int speedHeight = -int(m_height/8 * m_speed/m_maxSpeed);
    QLinearGradient grad1(m_width,m_height- m_height/3, m_width,m_height);
    grad1.setColorAt(0.1, Qt::transparent);
    grad1.setColorAt(0.9, *m_colour);
    painter->setBrush(grad1);
    int x =  10;
    int x2 = x + m_width/30;
    int y2 = y1 - speedHeight;

    QPointF speed[4] =
    {
        QPointF(x, y1),
        QPointF(x, y2),
        QPointF(x2, y2),
        QPointF(x2, y1),
    };
    painter->drawPolygon(speed, 4);

    //WEAPON
    // Set the matching colour
    grad1.setColorAt(0.9, QColor(255-m_weaponStatus*1.55, 45 + m_weaponStatus*1.55,0,255));
    painter->setBrush(grad1);
    painter->setPen(Qt::NoPen);
    // Set length of the bar
    int energyHeight = int(m_height/8 * (m_weaponStatus/100.0f));
    x = m_width - 10;
    x2 = x - m_width/30;
    y2 = y1 - energyHeight;

    QPointF weapon[4] =
    {
        QPointF(x, y1),
        QPointF(x, y2),
        QPointF(x2, y2),
        QPointF(x2, y1),
    };
    painter->drawPolygon(weapon, 4);

    //Draw laser symbol
    QImage laser("res/models/laser.png");
    int size = m_height/10 - 10;
    QPointF center(m_width - size/2 - 10, m_height - size/2 -10);
    int sizeLaser = size;
    if(m_activeWeapon != 1)
    {
        sizeLaser /= 2;
    }
    QRectF rect(m_width -sizeLaser -10, m_height - sizeLaser -10, sizeLaser, sizeLaser);
    rect.moveCenter(center);
    painter->drawImage(rect, laser);

    QImage plasma("res/models/plasma.png");
    QPointF center1(m_width - size/3*4 - 20, m_height - size/2 -10);
    int sizePlasma = size;
    if(m_activeWeapon != 2)
    {
        sizePlasma /= 2;
    }
    QRectF rect1(m_width -sizePlasma -10, m_height - sizePlasma -10, sizePlasma, sizePlasma);
    rect1.moveCenter(center1);
    painter->drawImage(rect1, plasma);
}

void Hud::mapBodies()
{
    // Reset the vectors
    m_bodiesAbove.clear();
    m_bodiesBelow.clear();

    std::vector<glVector<float> >::iterator it;
    m_posMutex->lock();
    for(it = m_bodies->begin(); it != m_bodies->end(); it++)
    {
        // Calculate the mapping of the difference vector:
        glVector<float> diff = (*it) - m_fighterPos;
        // Map each axis
        float x = diff * m_fighterDirX;
        float y = diff * m_fighterDirY;
        float z = diff * m_fighterDirZ;

        // Create new relative position
        glVector<float> rel(x,y,z);

        //And add to the relative positions
        if(z<0)
        {
            m_bodiesBelow.push_back(rel);
        }
        else
        {
            m_bodiesAbove.push_back(rel);
        }
    }
    m_posMutex->unlock();
}

void Hud::setBodies(std::vector<glVector<float> > *vec)
{
    m_bodies = vec;
}

void Hud::setFighter(glVector<float> *info)
{
    m_fighterPos  = info[0];
    m_fighterDirX = info[1];
    m_fighterDirY = info[2];
    m_fighterDirZ = info[3];
}

void Hud::setLP(int p)
{
    m_lp = p;
    m_hitFlashs = 5;
    m_visible = false;
}

void Hud::setScore(int p)
{
    m_score = p;
}

void Hud::setWeaponStatus(int v)
{
    m_weaponStatus = v;
}

void Hud::setLvl(int level)
{
    m_level = level;
    m_newLvl = 155;
}

void Hud::setSpeed(double speed)
{
    m_speed = speed;
}

void Hud::setMaxSpeed(double max)
{
    m_maxSpeed = max;
}

void Hud::setActiveWeapon(int type)
{
    m_activeWeapon = type;
}

void Hud::setPosMutex(QMutex* mutex)
{
    m_posMutex = mutex;
}

void Hud::setVisible(bool val)
{
    m_enabled = val;
}

void Hud::reset()
{
    m_level = 1;
    m_lp    = 100;
    m_weaponStatus = 100;
    m_speed = 0;
    m_score = 0;
}

void Hud::setPlayerName(QString name)
{
    m_playerName = name;
}
