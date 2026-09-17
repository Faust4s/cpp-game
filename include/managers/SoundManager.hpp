#pragma once
#include <SFML/Audio.hpp>

class SoundManager
{
public:
    SoundManager();

    // music
    void playMenuMusic();
    void playGameMusic();
    void playDeathMusic();
    void stopMusic();
    void setMusicVolume(float volume);

    // sound effects
    void playGemCollect();
    void playDeath();
    void playWin();

    void stopAllSounds();

    // Option to mute the sound
    void toggleMusicMuted();
    bool isMusicMuted() const { return musicMuted; }

private:
    bool musicMuted = false;

    sf::Music music;

    sf::SoundBuffer gemBuffer;
    sf::SoundBuffer winBuffer;

    sf::Sound gemSound;
    sf::Sound winSound;
};