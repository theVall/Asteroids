/**
 * @file HighScore.cpp
 * @author Gruppe 2
 */

#include "HighScore.hpp"

HighScore::HighScore(QString filename)
{
    m_filename = filename;
    m_names = new QVector<QString>(10);  
}

HighScore::~HighScore() { /*nothing to do yet */ }

bool HighScore::save()
{
    QDomDocument doc("highscore");
    QDomElement root = doc.createElement("highscore");
    doc.appendChild(root);
    QDomElement cn;
    for ( int i = 0; i < 10; i++)
    {
        cn = doc.createElement( "score" );
        cn.setAttribute( "value", m_score[i]);
        cn.setAttribute( "name", m_names->at(i));
        root.appendChild(cn);
    }
    
    QFile file("res/data/highscore.gda");
    if(!file.open(QIODevice::WriteOnly))
    {
        return false;
    }
    QTextStream ts(&file);
    ts << doc.toString();
    file.close();
    return true;
}

bool HighScore::load()
{
    QDomDocument doc("highscore");
    QFile file (m_filename);
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
    if(root.tagName() != QString("highscore"))
    {
        std::cerr << "tag name fail" << std::endl;
        return false;
    }
    QDomNode n = root.firstChild();
    int i = 0;
    while(!n.isNull() && i < 10)
    {
        QDomElement e = n.toElement();
        if(!e.isNull())
        {
            if(e.tagName() == "score")
            {
                m_score[i] = e.attribute("value", "").toInt();
                m_names->replace(i,e.attribute("name", ""));
                i++;
            }
            n = n.nextSibling();
        }
    }
    return true;
}

bool HighScore::setScore(QString name, int score)
{
    load();
    bool newHighScore = false;    
    int i = 9;
    while (i >= 0 && score > m_score[i])
    {

        if (i == 9)
        {
            m_score[i] = score;
            m_names->replace(i, name);
        }
        else
        {
            m_score[i+1] = m_score[i];
            m_names->replace(i+1, m_names->at(i));
            
	    m_score[i] = score;
            m_names->replace(i, name);
        }
        --i;
	newHighScore = true;
    }
    save();    
    return newHighScore;
}

int* HighScore::getScore()
{
    load();
    return m_score; 
}

/*QString HighScore::getScoreString(int place)
{   
    load();    
    if(place < 0 || place > 9)
    {
        std::cerr << "Wrong Highscore value" << std::endl;
        return NULL;
    }   
    QString out;
    out = out.setNum(m_score[place]);
    return out;
}

QString HighScore::getNameString(int place)
{
    load();
    if(place < 0 || place > 9)
    {
        std::cerr << "Wrong Highscore value" << std::endl;
        return NULL;
    }
    return m_names.at(place);
}*/

QPair<QString, QString> HighScore::getNameScore(int place)
{
    load();
    if(place < 0 || place > 9)
    {
        std::cerr << "Wrong Highscore value" << std::endl;
    }
    if(m_names->size() < place)
    {
        std::cerr << "can't access highscore, it's not there" << std::endl;
    }
    QString out_name, out_score;
    out_name = m_names->at(place);
    out_score = out_score.setNum(m_score[place]);
    return QPair<QString, QString>(out_name, out_score);
    //return QPair<QString, QString>(m_names.at(place), out); 
}

