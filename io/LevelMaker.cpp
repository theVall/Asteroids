/**
 * @file LevelMaker.cpp
 * @author Gruppe 2
 */

#include "LevelMaker.hpp"

LevelMaker::LevelMaker(int numA, int numP, float densA, float densP) 
	: m_numA(numA), m_numP(numP), m_densA(densA), m_densP(densP) {}

LevelMaker::~LevelMaker() { }

void LevelMaker::makeLevel()
{
    int count  = 0;
    //factor for asteroid density
    int factorA = (-3000) * sqrt(m_densA);
    //Factor for powerup density
    int factorP = (-4000) * sqrt(m_densP);
    
    std::ofstream myfile;
    myfile.open ("res/levels/example.xml");

    
    myfile << "<asteroids>\n";
    for(int i = -3; i < 3; i++)
    {
        for(int j = -3; j < 3; j++)
        {
            for(int k = -1; k < 2; k++)
            {
                if(count++ >= m_numA) break;
                if(i == 0 && j == 0 && k == 0) continue;

                myfile << "    <asteroid posx=\"" << i*factorA << "\"";
                if(i >= 0)
                {
                    myfile << " ";
                    if(i / 1000 < 10) myfile << " ";
                }
                if(i < 0 && i*factorA / 1000 > -10) myfile << " ";

                myfile << " posy=\"" << j*factorA << "\"";
                if(j >= 0)
                {
                    myfile << " ";
                    if(j / 1000 < 10) myfile << " ";
                }
                if(j < 0 && j*factorA / 1000 > -10) myfile << " ";
               
                myfile << " posz=\"" << k*factorA << "\"";
                if(k >= 0)
                {
                    myfile << " ";
                    if(k / 1000 < 10) myfile << " ";
                }
                if(k < 0 && k*factorA / 1000 > -10) myfile << " ";
           
                myfile << " size=\"big\"/>\n";
            }
        }
    }
    count = 0;
    for(int i = -3; i < 3; i++)
    {
        for(int j = -3; j < 3; j++)
        {
            for(int k = -1; k < 2; k++)
            {
                if(count++ >= m_numP) break;
                if(i == 0 && j == 0 && k == 0) continue;

                myfile << "    <powerup posx=\"" << i*factorP << "\"";
                if(i >= 0)
                {
                    myfile << " ";
                    if(i / 1000 < 10) myfile << " ";
                }
                if(i < 0 && i*factorP / 1000 > -10) myfile << " ";

                myfile << " posy=\"" << j*factorP << "\"";
                if(j >= 0)
                {
                    myfile << " ";
                    if(j / 1000 < 10) myfile << " ";
                }
                if(j < 0 && j*factorP / 1000 > -10) myfile << " ";
               
                myfile << " posz=\"" << k*factorP << "\"";
                if(k >= 0)
                {
                    myfile << " ";
                    if(k / 1000 < 10) myfile << " ";
                }
                if(k < 0 && k*factorP / 1000 > -10) myfile << " ";
                myfile << " />\n";
            }
        }
    }

    myfile << "</asteroids>\n";
    myfile.close();
}
