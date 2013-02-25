/**
 *  SoundOutput.hpp
 *
 * @date 22.02.2012
 * @author Kevin Seidel
 */

#ifndef SOUNDOUTPUT_HPP_
#define SOUNDOUTPUT_HPP_

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

class SoundOutput
{
public:
    typedef enum SoundType{LASER, PLASMA, HIT, EXPLOSION, SHIELD, POWERUP, MENUOVER, MENUSELECT} SoundType;

    SoundOutput();
    ~SoundOutput();
    /**
     *  @brief plays the sound on the given slot
     */
    void getSound(SoundType s);

    /**
     * @biref plays background music
     */
    void playMusic();

private:
    Mix_Chunk *m_laser;
    Mix_Chunk *m_plasma;
    Mix_Chunk *m_explosion;
    Mix_Chunk *m_hit;
    Mix_Chunk *m_powerUp;
    Mix_Chunk *m_shield;
    Mix_Chunk *m_menuOver;
    Mix_Chunk *m_menuSelect;

    Mix_Music *m_music;


};
#endif /*SOUNDOUTPUT_HPP_ */
