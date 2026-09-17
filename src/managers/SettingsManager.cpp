#include "SettingsManager.hpp"
#include "Assets.hpp"
#include <fstream>

static const std::string SETTINGS_FILE = Assets::SaveFiles::SETTINGS;

void SettingsManager::save(bool musicMuted, bool soundMuted)
{
    std::ofstream out(Assets::SaveFiles::SETTINGS, std::ios::binary);
    if (out)
    {
        out.write(reinterpret_cast<const char*>(&musicMuted), sizeof(bool));
        out.write(reinterpret_cast<const char*>(&soundMuted), sizeof(bool));
    }
}

void SettingsManager::load(bool &musicMuted, bool &soundMuted)
{
    musicMuted = false;
    soundMuted = false;

    std::ifstream in(Assets::SaveFiles::SETTINGS, std::ios::binary);
    if (!in)
        return;

    in.read(reinterpret_cast<char*>(&musicMuted), sizeof(bool));
    in.read(reinterpret_cast<char*>(&soundMuted), sizeof(bool));
}