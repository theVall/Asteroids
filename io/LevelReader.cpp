/*
 * @file LevelReader.cpp
 * @author Kevin Seidel
 * @date 12.02.20.
 */

#include "LevelReader.hpp"


LevelReader::LevelReader(RenderFrame* rf)
	: m_renderFrame(rf)
{
}

LevelReader::~LevelReader(){}

BodySet* LevelReader::getLevel(QString filename)
{
    BodySet* bodyset = new BodySet();
    if(!parse(filename, bodyset))
    {
        std::cerr << "unvalid xml file!" << std::endl;
        // throw Exception "unvalid_file"
    }
    return bodyset;
}

bool LevelReader::parse(QString filename, BodySet* bodyset)
{
    QDomDocument doc("asteroids");
    //QDomElement root = doc.documentElement();
    QFile file (filename);
    if(!file.open(QIODevice::ReadOnly) )
    {
        std::cerr << "Open XML failed" << std::endl;
        return false;
    }
    if(!doc.setContent(&file))
    {
        std::cerr << "setContent fail" << std::endl;
        file.close();
        return false;
    }
    file.close();

    QDomElement root = doc.documentElement();
    if(root.tagName() != QString("asteroids"))
    {
        std::cerr << "tag name fail" << std::endl;
        return false;
    }
    QDomNode n = root.firstChild();
    int i = 1;
    while(!n.isNull())
    {
        QDomElement e = n.toElement();
        if(!e.isNull())
        {
            if(e.tagName() == "asteroid")
            {
                bodyset->add(m_renderFrame->getNewAsteroid(glVector<float>(e.attribute("posx", "").toFloat(),
                                                          e.attribute("posy", "").toFloat(),
                                                          e.attribute("posz", "").toFloat())));
            }
            else if(e.tagName() == "powerup")
            {
                bodyset->add(m_renderFrame->getNewPowerUp(glVector<float>(e.attribute("posx", "").toFloat(),
                                                          e.attribute("posy", "").toFloat(),
                                                          e.attribute("posz", "").toFloat()), glVector<float>(1.0, 1.0, 1.0), i, 1, 20000));
            }
            n = n.nextSibling();
        }
        if(i == 1) i =2;
        else i = 1;
    }
    return true;
}


