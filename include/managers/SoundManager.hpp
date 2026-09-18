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

    // sound effects
    void playGemCollect();
    void playWin();

    void stopAllSounds(); // for player death

    // Option to mute music
    void toggleMusicMuted();
    bool isMusicMuted() const { return musicMuted; }

    // Option to mute sound
    void toggleSoundMuted();
    bool isSoundMuted() const { return soundMuted; }

private:
    bool musicMuted = false;
    bool soundMuted = false;

    sf::Music music;

    sf::SoundBuffer gemBuffer;
    sf::SoundBuffer winBuffer;

    sf::Sound gemSound;
    sf::Sound winSound;
};