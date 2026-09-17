#include "SettingsManager.hpp"
#include "Assets.hpp"
#include <fstream>

static const std::string SETTINGS_FILE = Assets::SaveFiles::SETTINGS;

void SettingsManager::save(bool musicMuted)
{
    std::ofstream out(SETTINGS_FILE, std::ios::binary);
    if (out)
        out.write(reinterpret_cast<const char*>(&musicMuted), sizeof(bool));
}

bool SettingsManager::load()
{
    std::ifstream in(SETTINGS_FILE, std::ios::binary);
    if (!in)
        return false; // default - music on

    bool musicMuted = false;
    in.read(reinterpret_cast<char*>(&musicMuted), sizeof(bool));
    return musicMuted;
}