#include "RenderFrame.hpp"


Asteroid* RenderFrame::m_asteroid = 0;
Bullet*   RenderFrame::m_bullet = 0;
Bullet*    RenderFrame::m_laserBullet = 0;
PowerUp*  RenderFrame::m_powerUp = 0;
Read3DS*  RenderFrame::m_asteroidReader = 0;
Read3DS*  RenderFrame::m_bulletReader = 0;
Read3DS*  RenderFrame::m_laserBulletReader = 0;
Read3DS*  RenderFrame::m_powerupReader = 0;

RenderFrame::RenderFrame(QWidget* parent) : QGLWidget(parent)
{
    // set up animation timer
    m_timer = new QTimer();
    m_timer->setInterval(25);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateGL()), Qt::QueuedConnection);

    m_nameTimer = new QTimer();
    m_nameTimer->setSingleShot(true);
    m_nameTimer->setInterval(1);
    connect(m_nameTimer, SIGNAL(timeout()), this, SLOT(callPlayerName()), Qt::QueuedConnection);
    m_timer->start();

    m_asteroid = 0;
    m_fighter = 0;
    m_bodies = 0;
    m_skybox = 0;
    m_check = 1;
    m_powerUp = 0;
    m_bullet = 0;

    m_inputAccepted = false;
    m_inputDialog = new QInputDialog(this, Qt::FramelessWindowHint);
    m_inputDialog->setLabelText("Please enter your name");
    m_playerName = "Player";
    m_inputDialog->setTextValue(m_playerName);


    setAutoFillBackground(false);
    setMouseTracking(true);

    show();
}

RenderFrame::~RenderFrame()
{
    delete m_timer;
    delete m_asteroid;
    delete m_fighter;
    delete m_skybox;
    delete m_laserBullet;
    delete m_bullet;
}

void RenderFrame::renderAll()
{
    paintGL();
}

void RenderFrame::initializeGlut()
{
	int dummy_argc = 1;
	char *dummy_argv[1];
	dummy_argv[0] = new char[255];
	dummy_argv[0] = (char*)"Main Window";

	// Initialize glut toolkit
	glutInit(&dummy_argc, dummy_argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
}

void RenderFrame::initializeGL()
{
	initializeGlut();

	string names[6];
	names[0] = "res/models/box1.ppm";
	names[1] = "res/models/box2.ppm";
	names[2] = "res/models/box3.ppm";
	names[3] = "res/models/box4.ppm";
	names[4] = "res/models/box5.ppm";
	names[5] = "res/models/box6.ppm";

	m_skybox = new Skybox(2024, names, m_cam);

        m_hud = new Hud(this);

        m_menuset = new MenuSet();

	m_fighter = new Fighter();

	Read3DS reader("res/models/arrow.3ds");
	reader.getMesh(*(static_cast<TexturedMesh*>(m_fighter)));

	// Init the Prototypes for big asteroids
	m_asteroid = new Asteroid();

	m_asteroidReader = new Read3DS("res/models/asteroid.3ds");
        m_asteroidReader->getMesh(*(static_cast<TexturedMesh*>(m_asteroid)));

	// Init the Prototypes for powerups
	m_powerUp = new PowerUp();

	m_powerupReader = new Read3DS("res/models/powerup.3ds");
        m_powerupReader->getMesh(*(static_cast<TexturedMesh*>(m_powerUp)));

	// Init the Prototypes for bullets
	m_bullet = new Bullet();

	m_bulletReader = new Read3DS("res/models/bullet.3ds");
    m_bulletReader->getMesh(*(static_cast<TexturedMesh*>(m_bullet)));
        
    // Init the Prototypes for bullets
	m_laserBullet = new Bullet();

	m_laserBulletReader = new Read3DS("res/models/laser.3ds");
    m_laserBulletReader->getMesh(*(static_cast<TexturedMesh*>(m_laserBullet)));

	m_fighter->setMaxSpeed(50);
	m_fighter->setSpeed(0);

	glMatrixMode(GL_MODELVIEW);
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

	// Setup two light sources
	float light0_position[4];
	float light0_ambient[4];
	float light0_diffuse[4];

	float light1_position[4];
	float light1_ambient[4];
	float light1_diffuse[4];

	light0_position[0] =   1.0f; light0_ambient[0] = 0.8f; light0_diffuse[0] = 0.8f;
	light0_position[1] =   1.0f; light0_ambient[1] = 0.8f; light0_diffuse[1] = 0.8f;
	light0_position[2] =   0.0f; light0_ambient[2] = 0.8f; light0_diffuse[2] = 0.8f;
	light0_position[3] =   1.0f; light0_ambient[3] = 0.1f; light0_diffuse[3] = 1.0f;

	light1_position[0] =   0.0f; light1_ambient[0] = 0.1f; light1_diffuse[0] = 0.5f;
	light1_position[1] =  -1.0f; light1_ambient[1] = 0.1f; light1_diffuse[1] = 0.5f;
	light1_position[2] =   0.0f; light1_ambient[2] = 0.1f; light1_diffuse[2] = 0.5f;
	light1_position[3] =   1.0f; light1_ambient[3] = 1.0f; light1_diffuse[3] = 1.0f;

	// Light 1
	glLightfv(GL_LIGHT0, GL_AMBIENT,  light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glEnable(GL_LIGHT0);

	// Light 2
	glLightfv(GL_LIGHT1, GL_AMBIENT,  light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  light1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glEnable(GL_LIGHT1);

	// Enable lighting
	glEnable(GL_LIGHTING);

	// Enable z buffer and gouroud shading
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glShadeModel (GL_SMOOTH);
	//Enable material specific coloring
//	glEnable(GL_COLOR_MATERIAL);
//	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void RenderFrame::resizeGL(int w, int h)
{
    if(h == 0) h = 1;

    float ratio = 1.0* w / h;

    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45,ratio,1,100000);
    glMatrixMode(GL_MODELVIEW);

    if(m_hud)
    {
       m_hud->resize();
    }
    if(m_menuset)
    {
    	m_menuset->rePos();
    }
    // Set 'LookAt'
    //m_cam.apply();
}

void RenderFrame::paintGL()
{
    setFocus();
    m_check--;

    // Set black background color, clear bg color, enable depth test
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_fighter->m_pos_mutex.lock();
    if(m_skybox)
    {
       // m_skybox->m_p = m_cam.m_realpos;
        m_skybox->m_p = m_cam.m_pos;
        m_skybox->render();
    }
    if(m_bodies)
    {
        m_bodies->renderAll(m_fighter->getInfo()[0], m_fighter->getInfo()[1]);
    }
    if(m_fighter)
    {
        m_cam.setLocation(m_fighter->getPosition(), m_fighter->getDirection(), m_fighter->getZAxis());
        m_fighter->render();
        //m_cam.apply();
    }
    m_fighter->m_pos_mutex.unlock();

    if(m_hud)
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        m_hud->paint();
        glPopAttrib();
        glPopMatrix();
    }

    if(m_menuset)
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        m_menuset->paint();
        glPopAttrib();
        glPopMatrix();
    }

    glFinish();
    swapBuffers();
}


void RenderFrame::keyPressEvent (QKeyEvent  *event)
{
    m_key_mutex.lock();
    m_pressedKeys.insert((Qt::Key)(event->key()));
    m_key_mutex.unlock();
}

void RenderFrame::keyReleaseEvent (QKeyEvent  *event)
{
    m_key_mutex.lock();
    m_pressedKeys.erase((Qt::Key)(event->key()));
    m_key_mutex.unlock();
}
void RenderFrame::mouseReleaseEvent(QMouseEvent* event)
{
    if(m_menuset)
	{
		m_mouse_mutex.lock();
		m_menuset->mouseEvent(event);
		m_mouse_mutex.unlock();
	}
    //m_mouseEvents.push_back(&event);
}
void RenderFrame::mouseMoveEvent (QMouseEvent  *event)
{
//    m_mouseEvents.push_back(&event);
    if(m_menuset)
	{
		m_mouse_mutex.lock();
		m_menuset->mouseEvent(event);
		m_mouse_mutex.unlock();
	}


}

void RenderFrame::moveCamXY(int dx, int dy)
{
    if(fabs(dx) > MOUSE_SENSITY)
    {
        if(dx > 0)
        {
            m_cam.turnRight();
        } else
        {
            m_cam.turnLeft();
        }
    }

/*
    if(fabs(dy) > MOUSE_SENSITY)
    {
        if(dy > 0)
        {
            m_cam.moveBackward();
        } else
        {
            m_cam.moveForward();
        }
    }*/
}

void RenderFrame::moveCamZ(int dy)
{
    if(fabs(dy) > MOUSE_SENSITY)
    {
        if(dy > 0)
        {
            m_cam.moveUp();
        } else
        {
            m_cam.moveDown();
        }
    }
}

void RenderFrame::moveCamHead(int dx, int dy)
{
    if(fabs(dy) > MOUSE_SENSITY)
    {
        if(dy > 0)
        {
            m_cam.turnUp();
        } else
        {
            m_cam.turnDown();
        }
    }

    if(fabs(dx) > MOUSE_SENSITY)
    {
        if(dx > 0)
        {
            m_cam.turnRight();
        } else
        {
            m_cam.turnLeft();
        }
    }
}

Fighter* RenderFrame::getFighter()          { return m_fighter; }

void RenderFrame::setBodySet(BodySet* bs)   { m_bodies = bs; }

BodySet* RenderFrame::getBodySet()          { return m_bodies; }

void RenderFrame::setSkybox(Skybox* sb)     { m_skybox = sb; }

Skybox* RenderFrame::getSkybox()            { return m_skybox; }

void RenderFrame::setHud(Hud* h)            { m_hud = h; }

Hud* RenderFrame::getHud()                  { return m_hud; }

void RenderFrame::setCamera(Camera* c)      { m_cam = *c; }

Camera* RenderFrame::getCamera()            { return &m_cam; }

MenuSet* RenderFrame::getMenuSet()		            { return m_menuset; }

void RenderFrame::setMaterials(Asteroid* a) {
	a->setNormalBuffer(m_asteroid->m_normalBuffer);
	a->setVertexBuffer(m_asteroid->m_vertexBuffer,m_asteroid->m_numVertices);
	a->setIndexBuffer(m_asteroid->m_indexBuffer,m_asteroid->m_numFaces);
	a->setMaterials(*(m_asteroid->getMaterials()));
	a->m_matFaceLists = m_asteroid->m_matFaceLists;
	a->m_textureCoords = m_asteroid->m_textureCoords;
}

void RenderFrame::setMaterials(Bullet* b)   {
	 b->setNormalBuffer(m_bullet->m_normalBuffer);
	 b->setVertexBuffer(m_bullet->m_vertexBuffer,m_bullet->m_numVertices);
	 b->setIndexBuffer(m_bullet->m_indexBuffer,m_bullet->m_numFaces);
	 b->setMaterials(*(m_bullet->getMaterials()));
	 b->m_matFaceLists = m_bullet->m_matFaceLists;
	 b->m_textureCoords = m_bullet->m_textureCoords;
}

void RenderFrame::setLaserMaterials(Bullet* b)   {
	 b->setNormalBuffer(m_laserBullet->m_normalBuffer);
	 b->setVertexBuffer(m_laserBullet->m_vertexBuffer,m_laserBullet->m_numVertices);
	 b->setIndexBuffer(m_laserBullet->m_indexBuffer,m_laserBullet->m_numFaces);
	 b->setMaterials(*(m_laserBullet->getMaterials()));
	 b->m_matFaceLists = m_laserBullet->m_matFaceLists;
	 b->m_textureCoords = m_laserBullet->m_textureCoords;
}

void RenderFrame::setMaterials(PowerUp* p)   {
	p->setMaterials(*(m_powerUp->getMaterials()));
	p->setNormalBuffer(m_powerUp->m_normalBuffer);
	p->setVertexBuffer(m_powerUp->m_vertexBuffer,m_powerUp->m_numVertices);
	p->setIndexBuffer(m_powerUp->m_indexBuffer,m_powerUp->m_numFaces);
	p->m_matFaceLists = m_powerUp->m_matFaceLists;
	p->m_textureCoords = m_powerUp->m_textureCoords;
}

// Factory Methods

Asteroid* RenderFrame::getNewAsteroid(glVector<float> pos, glVector<float> dir, float size, double speed)
{
	Asteroid* ret = new Asteroid(pos, dir, size, speed);
	setMaterials(ret); //Fixes the Textures
	return ret;
}
Asteroid* RenderFrame::getNewAsteroid(glVector<float> pos)
{
	Asteroid* ret = new Asteroid(pos);
	setMaterials(ret); //Fixes the Textures
	return ret;
}
Bullet* RenderFrame::getNewBullet(glVector<float> pos, glVector<float> dir, double speed, int range, int damage)
{
	Bullet* ret = new Bullet(pos, dir, speed, range, damage);
	setMaterials(ret); //Fixes the Textures
	return ret;
}

Bullet* RenderFrame::getNewLaserBullet(glVector<float> pos, glVector<float> dir, double speed, int range, int damage)
{
	Bullet* ret = new Bullet(pos, dir, speed, range, damage);
	setLaserMaterials(ret); //Fixes the Textures
	return ret;
}

PowerUp* RenderFrame::getNewPowerUp(glVector<float> pos, glVector<float> dir, int type, double speed, long lifetime)
{
	PowerUp* ret = new PowerUp(pos, dir, type, speed, lifetime);
	setMaterials(ret); //Fixes the Textures
	return ret;
}

void RenderFrame::setAccepted()
{
    m_inputAccepted = true;
}

void RenderFrame::callPlayerName()
{
    m_inputDialog->show();
}

QString RenderFrame::getPlayerName()
{
    m_playerName = m_inputDialog->textValue();
    return m_playerName;
}

void RenderFrame::stop()                    { m_timer->stop(); }
