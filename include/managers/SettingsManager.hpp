#pragma once

class SettingsManager
{
public:
    static void save(bool musicMuted);
    static bool load();
};