#pragma once

class SettingsManager
{
public:

    static void save(bool musicMuted, bool soundMuted);
    static void load(bool &musicMuted, bool &soundMuted);
};