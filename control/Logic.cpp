#include "Logic.hpp"

Logic::Logic(RenderFrame* rf)
{
    m_renderFrame = rf;
    m_levelReader = new LevelReader(m_renderFrame);

    m_highScore   = new HighScore(QString("res/data/highscore.gda"));

    LevelMaker levelMaker (100, 20, 10, 10);
    levelMaker.makeLevel();

    //set radius of big and small asteroids
    m_radBigAsteroid   = 1700;
    m_radSmallAsteroid = 600;

    QString player("Player");
    m_playerName = player;

    initKeys();
    // Load fighter
    m_fighter = m_renderFrame->getFighter();
    // Load Hud
    m_hud = m_renderFrame->getHud();

    // Load and init Menu
    m_menuset = m_renderFrame->getMenuSet();
    // Menu Start
    m_menu_start = new Menu(m_renderFrame);
    MenuElement* menu_header = new MenuElement(m_renderFrame, new QImage("res/menu/menuheader.png"));
    m_menu_start->addElement(menu_header);
    menu_header->getRect()->translate(0,-50);
    m_menu_start->addButton(new MenuButton(m_renderFrame, std::string("Start Game"),MENU_START));
    m_menu_start->addButton(new MenuButton(m_renderFrame, std::string("Player Name"),MENU_PLAYERNAME));
    m_menuset->addMenu(m_menu_start);
    // Menu Main
    m_menu_main = new Menu(m_renderFrame);
    menu_header = new MenuElement(m_renderFrame, new QImage("res/menu/menuheader.png"));
    m_menu_main->m_nextYButtonPos = -100;
    m_menu_main->addElement(menu_header);

    m_menu_button_continue = new MenuButton(m_renderFrame, std::string("Continue"), MENU_CONTINUE);
    m_menu_main->addButton(m_menu_button_continue);
    m_menu_main->addButton(new MenuButton(m_renderFrame, std::string("New Game"), MENU_NEWGAME));
    m_menu_main->addButton(new MenuButton(m_renderFrame, std::string("Highscore"), MENU_HIGHSCORE));
    m_menu_main->addButton(new MenuButton(m_renderFrame, std::string("Player Name"), MENU_PLAYERNAME));
    menu_score = new MenuElement(m_renderFrame);
    QString score_string("HIGHSCORE: ");
    score_string.append((m_highScore->getNameScore(1)).first);
    std::string score_std_string = score_string.toAscii().data();
    menu_score->setText(score_std_string, 16);
    m_menu_main->addElement(menu_score);
    m_menuset->addMenu(m_menu_main);
    m_menu_newHighScore = new Menu(m_renderFrame);
    m_menu_newHighScore->addElement(new MenuElement(m_renderFrame));
    m_menuset->addMenu(m_menu_newHighScore);
    m_menu_newHighScore->disable();

    m_menu_highscore = new Menu(m_renderFrame);
    m_menuset->addMenu(m_menu_highscore);
    m_menu_scoreImage = new QImage("res/menu/button.png");
    MenuElement* me = new MenuElement(m_renderFrame, "Highscore");
    std::string bla("Highscore");
    me->setText(bla,30);
    m_menu_highscore->addElement(me);

    for(int i = 0; i < 5; i++)
    {
	m_menu_highscores[i] = new MenuElement(m_renderFrame, m_menu_scoreImage);
        m_menu_highscore->addElement(m_menu_highscores[i]);
    }
    m_menu_highscore->addButton(new MenuButton(m_renderFrame, std::string("Back"), MENU_BACKMAIN));



    gameover = true;
    m_playing = false;
    m_menu_start->enable();
    m_hud->setVisible(false);
    msleep(500);
}

Logic::~Logic()
{
    this->stop();
    m_running = false;
    m_actions.clear();
    delete m_menuset;
    delete m_highScore;
    delete m_levelReader;
    delete m_bodies;
}

void Logic::newGame(QString filename)
{
    m_renderFrame->m_timer->stop();
    sleep(1);

    // Load bodies
    m_bodies = m_levelReader->getLevel(filename);

    // Set BodySet in RenderFrame
    m_renderFrame->setBodySet(m_bodies);
    m_fighter->setPosition(glVector<float>(0,0,0));
    m_fighter->setDirection(glVector<float>(1,0,0));
    m_fighter->setSpeed(0);
    m_fighter->setWeapon(new Laser(100), 1);

    //Important to make sure that the hud does not operate on already deleted asteroids
    m_hud->setPosMutex(&(m_bodies->m_mutex));
    m_hud->setMaxSpeed(m_fighter->getMaxSpeed());

    //set initial view data
    m_level         =   1;
    m_score         =   0;
    m_LP            = 100; // 100%
    m_levelbarrier  =  50;
    m_damage        =  25; //  25%

    Shield* s = new Shield(m_fighter->getPosition(), m_fighter->getXAxis(), m_fighter->getSpeed(), 200);
    m_fighter->setShield(s);
    m_fighter->setShieldStatus(true);

    m_hud->reset();

    m_menu_button_continue->enable();
    gameover = false;
    m_renderFrame->m_timer->start();
    gameContinue();
}


void Logic::run()
{
    m_running = true;
    int i = 0;
    while(m_running)
    {
        m_playerName = m_renderFrame->getPlayerName();
        if(m_playing)
        {
            if(m_score >= m_levelbarrier)
            {
              nextLevel();
            }
            //TODO  Direction muss noch überarbeitet werden
            m_fighter->setDirection(m_fighter->getXAxis());

            m_bodies->updateAllPositions();

            m_renderFrame->getHud()->setBodies(m_bodies->getPositions());

            m_fighter->updatePosition();
            m_hud->setFighter(m_fighter->getInfo());
            (m_fighter->getWeapon())->refresh();
            m_hud->setWeaponStatus((m_fighter->getWeapon())->getWeaponStatus());
            m_hud->setSpeed(m_fighter->getSpeed());
            if (i++ % 4 == 0)
            {
                collisionCheck();
                if(i > 100000)
                {
                    i = 0;
                }
            }
	      }
        doMenuActions();
        doKeyActions();
        usleep(3000);
    }
}

void Logic::nextLevel()
{
    m_level++;
    m_levelbarrier *= 2;
    m_hud->setLvl(m_level);

    boost::ptr_list<Asteroid>* asteroids = m_bodies->getAsteroids();
    boost::ptr_list<Body>::iterator it = asteroids->begin();
    while (it != asteroids->end())
    {
        it->setSpeed(it->getSpeed() * 1.2);
        it++;
    }

    if(m_fighter == 0)
    {
        delete m_fighter;
    }
}

void Logic::initKeys()
{
    m_actions[Qt::Key_W]     = TURNUP;
    m_actions[Qt::Key_S]     = TURNDN;
    m_actions[Qt::Key_A]     = TURNLE;
    m_actions[Qt::Key_D]     = TURNRI;
    m_actions[Qt::Key_Q]     = ROTLEF;
    m_actions[Qt::Key_E]     = ROTRIG;
    m_actions[Qt::Key_Up]    = MOVEUP;
    m_actions[Qt::Key_Down]  = MOVEDN;
    m_actions[Qt::Key_Space] =  SHOOT;
    m_actions[Qt::Key_Tab] = CHANGEWEAPON;
    m_actions[Qt::Key_Escape] = MENUBREAK;
}

void Logic::setKey(Qt::Key k, Logic::Key v)
{
    m_actions[k] = v;
}
void Logic::doMenuActions()
{
    if(m_playing)
    {
        //Joor nech...
    }
    else
    {
	m_renderFrame->m_mouse_mutex.lock();
	  switch(m_menuset->clickedButtonId())
	  {
		//Startbutton
		case MENU_START:
			m_menu_start->disable();
    			newGame("res/levels/example.xml");
			break;
        	case MENU_CONTINUE:
			gameContinue();
			break;
		case MENU_NEWGAME:
    			newGame("res/levels/example.xml");
			break;
        	case MENU_PLAYERNAME:
			    setPlayerName();
			break;
                case MENU_HIGHSCORE:
                        m_menu_highscore->enable();
                        m_menu_start->disable();
                        m_menu_main->disable();
                        m_hud->setVisible(false);
			for(int i=0; i<5; i++)
			{
				QPair<QString, QString> tmp = m_highScore->getNameScore(i);
				m_menu_highscores[i]->setText(tmp.first +"  "+tmp.second);
			}
                        break;
                case MENU_BACKMAIN:
                        	m_menu_highscore->disable();
                        	m_hud->setVisible(false);
                        	m_menu_main->enable();
                        break;
		default:
			break;
	  }
	m_renderFrame->m_mouse_mutex.unlock();
    }
}

void Logic::doKeyActions()
{
    m_renderFrame->m_key_mutex.lock();
    for(std::set<Qt::Key>::iterator iter = m_renderFrame->m_pressedKeys.begin();
        iter != m_renderFrame->m_pressedKeys.end(); ++iter)
    {
        if(m_playing)
        {
            switch(m_actions[*iter])
            {
                case(TURNUP) : m_fighter->rotate (PITCH,  0.002); break;
                case(TURNDN) : m_fighter->rotate (PITCH, -0.002); break;
                case(TURNLE) : m_fighter->rotate (ROLL,   0.002); break;
                case(TURNRI) : m_fighter->rotate (ROLL,  -0.002); break;
                case(ROTLEF) : m_fighter->rotate (YAW,    0.006); break;
                case(ROTRIG) : m_fighter->rotate (YAW,   -0.006); break;
                case(MOVEUP) : m_fighter->accelerate     (-0.05); break;
                case(MOVEDN) : m_fighter->accelerate     ( 0.05); break;
                case(CHANGEWEAPON) :
                {
                    switch(m_fighter->getWeaponType())
                    {
                        case 0:
                        {
                            double tmp = m_fighter->getWeapon()->getWeaponStatus();
                            m_fighter->setWeapon(new Laser(tmp),1);
                            m_hud->setActiveWeapon(1);
                        }break;

                        case 1:
                        {
                            double tmp = m_fighter->getWeapon()->getWeaponStatus();
                            m_fighter->setWeapon(new Plasma(tmp),2);
                            m_hud->setActiveWeapon(2);
                        }break;

                        case 2:
                        {
                            double tmp = m_fighter->getWeapon()->getWeaponStatus();
                            m_fighter->setWeapon(new Laser(tmp),1);
                            m_hud->setActiveWeapon(1);
                        }break;
                    }
                    (m_renderFrame->m_pressedKeys).erase(Qt::Key_Tab);
                } break;

                case(SHOOT) :
                {
                    if(m_renderFrame->m_check < 1)
                    {
                        if(m_fighter->shoot())
                        {
                           createBullet();
                        }
                    }
                } break;

                case (MENUBREAK): gameBreak(); break;

                default : break;
            }
        }
        else
        {
            switch(m_actions[*iter])
            {
                case (MENUBREAK): 
                    gameContinue(); break;
                default: break;
            }
        }
    }
    m_renderFrame->m_key_mutex.unlock();
}

void Logic::createBullet()
{
    switch(m_fighter->getWeaponType())
    {
        case 2:
        {
            Bullet* b = RenderFrame::getNewLaserBullet( m_fighter->getPosition(),
                                                    (m_fighter->getXAxis())*(-1),
                                                    (m_fighter->getSpeed() + (m_fighter->getWeapon())->getSpeed()),
                                                    (m_fighter->getWeapon())->getRange(),
                                                    (m_fighter->getWeapon())->getDamage());
            m_bodies->add(b);
            m_hud->setWeaponStatus((m_fighter->getWeapon())->getWeaponStatus());
            sound.getSound(SoundOutput::PLASMA);
        } break;
        default:
        {
            Bullet* b = RenderFrame::getNewBullet( m_fighter->getPosition(),
                                                (m_fighter->getXAxis())*(-1),
                                                (m_fighter->getSpeed() + (m_fighter->getWeapon())->getSpeed()),
                                                (m_fighter->getWeapon())->getRange(),
                                                (m_fighter->getWeapon())->getDamage());
            m_bodies->add(b);
            m_hud->setWeaponStatus((m_fighter->getWeapon())->getWeaponStatus());
            sound.getSound(SoundOutput::LASER);
        } break;
    }
    m_renderFrame->m_check = 5;
}

void Logic::collisionCheck()
{
    //var declaration
    boost::ptr_list<Asteroid>* asteroids = m_bodies->getAsteroids();

    boost::ptr_list<Bullet>* bullets = m_bodies->getBullets();

    boost::ptr_list<PowerUp>* powerups = m_bodies->getPowerUps();

    double diff, rad, speed_as;

    boost::ptr_list<Asteroid>::iterator it_asteroids_out = asteroids->begin();
    boost::ptr_list<PowerUp>::iterator it_powerups = powerups->begin();

    glVector<float> pos_as, pos_bu , pos_in, pos_out, pos_pow, dir_as;
    glVector<float> pos_fighter = m_fighter->getPosition();

    //check every asteroid
    while (it_asteroids_out != asteroids->end())
    {
        boost::ptr_list<Bullet>::iterator it_bullets = bullets->begin();

        pos_as = it_asteroids_out->getPosition();
        dir_as = it_asteroids_out->getDirection();
        speed_as = it_asteroids_out->getSpeed();
        rad = it_asteroids_out->getRadius() + it_bullets->getRadius();

        bool erased = false;
        //check asteroid for collision with bullet
        while (it_bullets != bullets->end() && !erased)
        {
            // calculate difference
            pos_bu = it_bullets->getPosition();
            diff = pos_as.dist(pos_bu);

            if (diff < rad)
            {
                sound.getSound(SoundOutput::HIT);
                it_asteroids_out->decreaseLP(it_bullets->getDamage());

                it_bullets = m_bodies->eraseBullet(it_bullets);

                if (it_asteroids_out->getLP() <= 0)
                {
                    it_asteroids_out = m_bodies->eraseAsteroid(it_asteroids_out);

                    sound.getSound(SoundOutput::EXPLOSION);
                    // check wether big asteroid -> split
                    if(rad >= m_radBigAsteroid)
                    {
                        splitAsteroids(pos_as, dir_as, speed_as);
                    }
                    // if small -> explode
                    else if (rad <= m_radSmallAsteroid)
                    {
                        explodeAsteroid(pos_as, (int)rad);
                    }
                    // set score
                    m_score += (5100 / (int) rad);
                    m_hud->setScore(m_score);
                    erased = true;
                }
            }
            else
            {
                it_bullets++;
            }
        }

        pos_out = it_asteroids_out->getPosition();

        //check asteroid for collision with other asteroid
        boost::ptr_list<Body>::iterator it_asteroids_in = asteroids->begin();
        while (it_asteroids_in != asteroids->end() && !erased)
        {
            if (it_asteroids_in != it_asteroids_out)
            {
                pos_in  = it_asteroids_in->getPosition();
                if(pos_in.dist(pos_out) < (it_asteroids_out->getRadius() + it_asteroids_in->getRadius()))
                {
                    it_asteroids_out->bounceBack(it_asteroids_in->getDirection(), it_asteroids_in->getPosition());
                    it_asteroids_in->bounceBack(it_asteroids_out->getDirection(), it_asteroids_out->getPosition());
                }
            }
            it_asteroids_in++;
        }

        //check asteroid for collision with fighter
        //calculate differece current asteroid - fighter
        pos_as = it_asteroids_out->getPosition();
        diff = pos_as.dist(pos_fighter);

        if ((diff < (m_fighter->getRadius() + it_asteroids_out->getRadius())) && !erased)
        {
            if (!m_fighter->getShieldStatus())
            {
                m_fighter->decreaseLP(m_damage);
                m_hud->setLP(m_fighter->getLP());

                //create shield
                if (m_fighter->getLP() > 0)
                {
                    m_fighter->setShieldStatus(true);
                    sound.getSound(SoundOutput::SHIELD);
                    Shield* s = new Shield(m_fighter->getPosition(), m_fighter->getXAxis(), m_fighter->getSpeed(), 100);
                    m_fighter->setShield(s);
                    it_asteroids_out = m_bodies->eraseAsteroid(it_asteroids_out);
                    erased = true;
                }
                if (m_fighter->getLP() <= 0)
                {
		    m_menu_button_continue->disable();
		    gameover = true;
                    if(m_highScore->setScore(m_playerName, m_score))
                    {
                        m_playing = false;
                        newHighScore();
                    }
                    else
                    {
                        msleep(2000);
                        gameBreak();
                    }
                }
            }
            else
            {
                it_asteroids_out = m_bodies->eraseAsteroid(it_asteroids_out);
                erased = true;
            }
        }

        // check if asteroid is out of reach
        if(diff > 100000 && !erased)
        {
            it_asteroids_out->setPosition(m_fighter->getPosition() * 2 - it_asteroids_out->getPosition());
        }

        if (!erased) it_asteroids_out++;
        else m_bodies->add(m_renderFrame->getNewAsteroid(m_fighter->getPosition() + glVector<float>(10000, 20000, 30000)));
    }

    while(it_powerups != powerups->end())
    {
        bool erased = false;
        pos_pow = it_powerups->getPosition();
        diff = pos_pow.dist(pos_fighter);

        if ((diff < (m_fighter->getRadius() + it_powerups->getRadius())))
        {
            it_powerups->doAction(m_fighter);
            if(m_fighter->getLP() <= 100)
            {
            	m_hud->setLP(m_fighter->getLP());

         	}
            it_powerups = m_bodies->erasePowerUp(it_powerups);
            erased = true;
        }
        else
        {
            it_powerups++;
        }
        if(diff > 100000 && !erased && (m_fighter->getPosition() - it_powerups->getPosition())*m_fighter->getDirection() <= 0)
        {
            it_powerups->setPosition(m_fighter->getPosition() * 2 - it_powerups->getPosition());
        }

    }
}

void Logic::splitAsteroids(glVector<float> pos, glVector<float> dir, double speed)
{
    //positive
    float dirX = (-1) * sqrt(dir.x * dir.x);
    float dirY = (-1) * sqrt(dir.y * dir.y);
    float dirZ = (-1) * sqrt(dir.z * dir.z);

    //negative
    speed = (-1)* sqrt(speed * speed);

    // 0.3 = small type
    Asteroid* a = m_renderFrame->getNewAsteroid(pos + glVector<float>(500.0, 0.0, 0.0), glVector<float>(dirX, 0.0, 0.0), 0.3, speed);
    Asteroid* b = m_renderFrame->getNewAsteroid(pos + glVector<float>(0.0, 0.0, 500.0), glVector<float>(0.0, 0.0, dirZ), 0.3, speed);
    Asteroid* c = m_renderFrame->getNewAsteroid(pos + glVector<float>(0.0, 500.0, 0.0), glVector<float>(0.0, dirY, 0.0), 0.3, speed);

    m_bodies->add(a);
    m_bodies->add(b);
    m_bodies->add(c);
}

void Logic::explodeAsteroid(glVector<float> pos, int rad)
{
    // for (int i = 0; i < (rad / 10); i++)
    // {
    //     // new particle with postition and lifetime
    //     Particle* p = new Particle(pos, 5000);
    //     m_bodies->add(p);
    // }
}

void Logic::gameBreak()
{
    QString score_string("HIGHSCORE: ");
    score_string.append((m_highScore->getNameScore(1)).first);
    std::string score_std_string = score_string.toAscii().data();
    menu_score->setText(score_std_string, 16);
    m_playing = false;
    m_menu_main->enable();
    m_hud->setVisible(false);
    msleep(500);
}

void Logic::gameContinue()
{
    if(gameover) return;   
    m_playing = true;
    m_menu_main->disable();
    m_menu_highscore->disable();
    m_hud->setPlayerName(m_playerName);
    m_hud->setVisible(true);
    msleep(500);
}

void Logic::stop()
{
    m_renderFrame->stop();
    delete m_renderFrame;
    m_running = false;
    sleep(1);
}

void Logic::newHighScore()
{
    m_menu_main->enable();
    //m_menu_newHighScore->enable();
}

void Logic::setPlayerName()
{
    m_renderFrame->m_nameTimer->start();
    m_playerName = m_renderFrame->getPlayerName();
}

