#pragma once

/* Kept separate from Config.hpp: Config is for *tunable gameplay numbers*,
 * this is for *where things are on disk*. Texture paths here are resolved
 * relative to <GAME_ASSET_DIR>/textures/ by TextureManager, same as before.
*/ 

namespace Assets
{
    namespace Textures
    {
        constexpr char BACKGROUND[] = "cobblestone_bg.png";
        constexpr char MENU_BACKGROUND[] = "mainMenu_bg.png";

        constexpr char PLAYER_ONE[] = "textures/warmsprite.png";
        constexpr char PLAYER_TWO[] = "textures/coldsprite.png";

        constexpr char BUTTON_PRESSED[] = "button_pressed.png";
        constexpr char BUTTON_UNPRESSED[] = "button_unpressed.png";

        constexpr char DOOR_PLAYER_ONE[] = "door_red.png";
        constexpr char DOOR_PLAYER_TWO[] = "door_blue.png";

        constexpr char GEM_RED[] = "firegem.png";
        constexpr char GEM_BLUE[] = "bluegem.png";

        constexpr char HAZARD_PLAYER_ONE[] = "orangeriver.png";
        constexpr char HAZARD_PLAYER_TWO[] = "blueriver.png";
        constexpr char HAZARD_GENERAL[] = "neutralriver.png";

        constexpr char PLATFORM[] = "platform.png";
        constexpr char TILE[] = "tile.png";
    }

    namespace Fonts
    {
        constexpr char UI[] = "/font.ttf";
    }
}