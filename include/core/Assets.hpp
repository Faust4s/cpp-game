#pragma once

#include <climits>
#include <string>
#include <filesystem>

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
#else
    #include <unistd.h>
#endif

/* Kept separate from Config.hpp: Config is for *tunable gameplay numbers*,
 * this is for *where things are on disk*. Every constant below is stored
 * bare (no directory prefix); use the path helpers at the bottom of this
 * file to turn one into something loadable. Nobody should be concatenating
 * a path by hand.
*/ 

namespace Assets
{
    // Bare filenames -- resolve with Assets::texturePath().
    namespace Textures
    {
        constexpr char BACKGROUND[] = "cobblestone_bg.png";
        constexpr char MENU_BACKGROUND[] = "mainMenu_bg.png";

        constexpr char PLAYER_ONE[] = "warmsprite.png";
        constexpr char PLAYER_TWO[] = "coldsprite.png";

        constexpr char BUTTON_PRESSED[] = "button_pressed.png";
        constexpr char BUTTON_UNPRESSED[] = "button_unpressed.png";

        constexpr char DOOR_PLAYER_ONE[] = "door_red.png";
        constexpr char DOOR_PLAYER_TWO[] = "door_blue.png";
        constexpr char DOOR_PLAYER_ONE_OPEN[] = "red_opening_doors.png";
        constexpr char DOOR_PLAYER_TWO_OPEN[] = "blue_opening_doors.png";

        constexpr char GEM_RED[] = "firegem.png";
        constexpr char GEM_BLUE[] = "bluegem.png";

        constexpr char HAZARD_PLAYER_ONE[] = "orangeriver.png";
        constexpr char HAZARD_PLAYER_TWO[] = "blueriver.png";
        constexpr char HAZARD_GENERAL[] = "neutralriver.png";

        constexpr char PLATFORM[] = "platform.png";
        constexpr char TILE[] = "tile.png";
    }

    namespace Sounds
    {
    constexpr char GEM[] = "/sounds/gem_sound.wav";
    constexpr char WIN[] = "/sounds/win_sound.wav";
    constexpr char MENU_MUSIC[] = "/sounds/menu_music.wav";
    constexpr char GAME_MUSIC[] = "/sounds/background_music.ogg";
    constexpr char LOSE_MUSIC[] = "/sounds/lose_music.wav";
    }

    namespace Fonts
    {
        constexpr char UI[] = "/font.ttf";
    }

    namespace SaveFiles
    {
    constexpr char SAVE[] = "save.dat";
    constexpr char SETTINGS[] = "settings.dat";
    }

    // Directory the running executable actually lives in, computed once.
    // Deliberately NOT based on argv[0] or the current working directory --
    // both are unreliable (argv[0] can be a bare name found via PATH; cwd
    // depends on how the process was launched, e.g. a desktop shortcut's
    // "start in" folder). Each platform has a proper API for "where am I".
    inline const std::filesystem::path& executableDir()
    {
        static const std::filesystem::path dir = []() -> std::filesystem::path
        {
#if defined(_WIN32)
            char buffer[MAX_PATH];
            DWORD len = GetModuleFileNameA(nullptr, buffer, MAX_PATH);
            if (len > 0 && len < MAX_PATH)
                return std::filesystem::path(buffer).parent_path();
#elif defined(__APPLE__)
            char buffer[PATH_MAX];
            uint32_t size = sizeof(buffer);
            if (_NSGetExecutablePath(buffer, &size) == 0)
                return std::filesystem::canonical(buffer).parent_path();
#else
            char buffer[PATH_MAX];
            ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
            if (len != -1)
            {
                buffer[len] = '\0';
                return std::filesystem::path(buffer).parent_path();
            }
#endif
            // Only reached if the platform call above failed.
            return std::filesystem::current_path();
        }();
        return dir;
    }

    // Path helpers: the single place that knows the on-disk layout.
    // Everything is resolved as <executableDir>/assets/...
    inline std::string texturePath(const std::string& file)
    {
        return (executableDir() / "assets" / "textures" / file).string();
    }

    inline std::string assetPath(const std::string& file)
    {
        // Resolve asset paths relative to the executable.
        std::string relative = file;
        if (!relative.empty() && relative.front() == '/')
            relative.erase(relative.begin());
        return (executableDir() / "assets" / relative).string();
    }

    // Resolve save/settings paths relative to the executable.
    inline std::string savePath(const std::string& file)
    {
        return (executableDir() / file).string();
    }
}