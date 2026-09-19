#include "SoundManager.hpp"
#include "SettingsManager.hpp"
#include "Config.hpp"
#include "Assets.hpp"
#include <string>

SoundManager::SoundManager()
{
    SettingsManager::load(musicMuted, soundMuted);

    if (gemBuffer.loadFromFile(Assets::assetPath(Assets::Sounds::GEM)))
    {
        gemSound.setBuffer(gemBuffer);
        gemSound.setVolume(Config::GEM_SOUND_VOLUME);
    }
    if (winBuffer.loadFromFile(Assets::assetPath(Assets::Sounds::WIN))){
        winSound.setBuffer(winBuffer);
        winSound.setVolume(Config::WIN_SOUND_VOLUME);
    }

    playMenuMusic();
}

void SoundManager::playMenuMusic()
{
    music.stop();
    if (music.openFromFile(Assets::assetPath(Assets::Sounds::MENU_MUSIC)))
    {
        music.setLoop(true);
        music.setVolume(musicMuted ? 0.f : Config::MUSIC_VOLUME);
        music.play();
    }
}

void SoundManager::playGameMusic()
{
    music.stop();
    if (music.openFromFile(Assets::assetPath(Assets::Sounds::GAME_MUSIC)))
    {
        music.setLoop(true);
        music.setVolume(musicMuted ? 0.f : Config::MUSIC_VOLUME);
        music.play();
    }
}

void SoundManager::playDeathMusic()
{
    music.stop();
    if (music.openFromFile(Assets::assetPath(Assets::Sounds::LOSE_MUSIC)))
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
    SettingsManager::save(musicMuted, soundMuted);
}

void SoundManager::toggleSoundMuted()
{
    soundMuted = !soundMuted;
    SettingsManager::save(musicMuted, soundMuted);
}

void SoundManager::stopMusic(){ music.stop(); }

void SoundManager::playGemCollect()
{
    if (!soundMuted)
        gemSound.play();
}

void SoundManager::playWin()
{
    if (!soundMuted)
        winSound.play();
}