#include "SaveManager.hpp"
#include "Assets.hpp"
#include <fstream>

void SaveManager::save(int unlockedLevels)
{
    std::ofstream out(Assets::savePath(Assets::SaveFiles::SAVE), std::ios::binary);
    if (out)
        out.write(reinterpret_cast<const char*>(&unlockedLevels), sizeof(int));
}

int SaveManager::load()
{
    std::ifstream in(Assets::savePath(Assets::SaveFiles::SAVE), std::ios::binary);
    if (!in)
        return 1; // default - level 1 is unlocked

    int unlockedLevels = 1;
    in.read(reinterpret_cast<char*>(&unlockedLevels), sizeof(int));
    return unlockedLevels;
}