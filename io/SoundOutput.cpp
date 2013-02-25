/**
 * @file SoundOutput.cpp
 * @author Kevin Seidel
 */

#include "SoundOutput.hpp"
#include <iostream>

SoundOutput::SoundOutput()
{
    //sound = NULL;
    //music = NULL;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
    }

    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;

    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
        fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
        exit(1);
    }

    m_laser = Mix_LoadWAV("res/sounds/laser.wav");
    m_plasma = Mix_LoadWAV("res/sounds/plasma.wav");
    m_hit = Mix_LoadWAV("res/sounds/hit.wav");
    m_explosion = Mix_LoadWAV("res/sounds/explosion.wav");
    m_shield = Mix_LoadWAV("res/sounds/shield.wav");
    m_powerUp = Mix_LoadWAV("res/sounds/powerUp.wav");
    m_menuOver = Mix_LoadWAV("res/sounds/menuOver.wav");
    m_menuSelect = Mix_LoadWAV("res/sounds/menuSelect.wav");


}
SoundOutput::~SoundOutput()
{
    if(m_music != NULL)
    {
	    Mix_FreeMusic(m_music);
    }
    Mix_CloseAudio();
}

void SoundOutput::getSound(SoundType  s)
{
    int channel = 0;
    switch(s)
    {
	    case LASER:
            channel = Mix_PlayChannel(-1, m_laser, 0);
	    break;
        case PLASMA:
            channel = Mix_PlayChannel(-1, m_plasma, 0);
        break;
        case HIT:
            channel = Mix_PlayChannel(-1, m_hit, 0);
        break;
	    case EXPLOSION:

	        channel = Mix_PlayChannel(-1, m_explosion, 0);
	    break;
        case SHIELD:
            channel = Mix_PlayChannel(-1, m_shield, 0);
        break;
        case POWERUP:
            channel = Mix_PlayChannel(-1, m_powerUp, 0);
        break;
        case MENUOVER:
            channel = Mix_PlayChannel(-1, m_menuOver, 0);
        break;
        case MENUSELECT:
            channel = Mix_PlayChannel(-1, m_menuSelect, 0);
        break;
    }
    if(channel == -1)
    {
        //fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError());
    }

}
void SoundOutput::playMusic()
{
    m_music = Mix_LoadMUS("res/sounds/asteroids.ogg");
    if(!m_music)
    {
	std::cerr << "Konnte OGG-Datei nicht laden! Fehler: " << Mix_GetError() << std::endl;
    }

    Mix_PlayMusic(m_music, -1);
}
