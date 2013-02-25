/**
 * @file HighScore.hpp
 * @author Gruppe 2
 */

#ifndef HIGHSCORE_HPP_
#define HIGHSCORE_HPP_

#include <iostream>

#include <QtXml>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDomText>
#include <QFile>
#include <QString>
#include <QVector>
#include <QVectorIterator>
#include <QPair>

/**
 * @brief class to read and write the highscore file
 */
class HighScore
{
    public:
        
        /**
         * @brief Ctor - constructs a highscore object with a given filename
         */
        HighScore(QString filename);
        
        /**
         * @brief Dtor
         */
        ~HighScore();
        
        /**
         * @brief returns the sorted highscore
         * @return score soreted int array with scores 
         */
        int* getScore();
        
        /**
         * @brief set the score if it is within the best 10
         * @param score score to be set
         * @return true if set properly, false either
         */
        bool setScore(QString name, int score);
        
        /**
         * @brief load highscore from xml file
         * @return true if loaded properly, false either
         */
        bool load();
        
        /**
         * @brief save highscore to xml file
         * @return true if saved properly, false either
         */
        bool save();
        /**
         * @brief gets value of given place
         * @return value as qstring
         */
        QString getScoreString(int place);
        /**
         * @brief gets name of given place
         * @return name as qstring
         */
        QString getNameString(int place);
        
        QPair<QString, QString> getNameScore(int place);
    
    private:
        
        // name of xml file
        QString m_filename;

        // array with 10 best scores
        int m_score[10];

        // array with the names of 10 best    
        QVector<QString>* m_names;
        
     
};



#endif
