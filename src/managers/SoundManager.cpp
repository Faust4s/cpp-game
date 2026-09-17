#include "SoundManager.hpp"
#include "SettingsManager.hpp"
#include "Config.hpp"
#include "Assets.hpp"
#include <string>
#include <iostream>

SoundManager::SoundManager()
{
    musicMuted = SettingsManager::load();

    if (gemBuffer.loadFromFile(std::string(GAME_ASSET_DIR) + Assets::Sounds::GEM))
    {
        gemSound.setBuffer(gemBuffer);
        gemSound.setVolume(Config::GEM_SOUND_VOLUME);
    }
    if (winBuffer.loadFromFile(std::string(GAME_ASSET_DIR) + Assets::Sounds::WIN)){
        winSound.setBuffer(winBuffer);
        winSound.setVolume(Config::WIN_SOUND_VOLUME);
    }

    playMenuMusic();
}

void SoundManager::playMenuMusic()
{
    music.stop();
    if (music.openFromFile(std::string(GAME_ASSET_DIR) + Assets::Sounds::MENU_MUSIC))
    {
        music.setLoop(true);
        music.setVolume(musicMuted ? 0.f : Config::MUSIC_VOLUME);
        music.play();
    }
}

void SoundManager::playGameMusic()
{
    music.stop();
    if (music.openFromFile(std::string(GAME_ASSET_DIR) + Assets::Sounds::GAME_MUSIC))
    {
        music.setLoop(true);
        music.setVolume(musicMuted ? 0.f : Config::MUSIC_VOLUME);
        music.play();
    }
}

void SoundManager::playDeathMusic()
{
    music.stop();
    if (music.openFromFile(std::string(GAME_ASSET_DIR) + Assets::Sounds::LOSE_MUSIC))
    {
        music.setLoop(false);
        music.setVolume(musicMuted ? 0.f : Config::MUSIC_VOLUME);
        music.play();
    }
}

void SoundManager::stopAllSounds()
{
    music.stop();
    gemSound.stop();
    winSound.stop();
}

void SoundManager::toggleMusicMuted()
{
    musicMuted = !musicMuted;
    music.setVolume(musicMuted ? 0.f : Config::MUSIC_VOLUME);
    SettingsManager::save(musicMuted);
}

void SoundManager::stopMusic()                  { music.stop(); }
void SoundManager::setMusicVolume(float volume) { music.setVolume(volume); }

void SoundManager::playGemCollect()             { gemSound.play(); }
void SoundManager::playWin()                    { winSound.play(); }