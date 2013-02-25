/**
 * @file LevelMaker.hpp
 * @author Gruppe 2
 */

#include <iostream>
#include <fstream>
#include <cmath>

class LevelMaker
{
    public:
        /**
         * @ Ctor
         */
        LevelMaker(int numA, int numP, float densA, float densP);
        
        /**
         * @ Dtor
         */
        ~LevelMaker();

        /**
         * @brief writes a level file with specified number of asteroids and density
         * @numA number of asteroids (min should be about 20, max should be about 150)
         * @density density (scale from 1 to 10, 1 being high density, 10 being los density)
        */
        void makeLevel();

    private:
        int   m_numA;
        int   m_numP;
        float m_densA;
        float m_densP;
};
