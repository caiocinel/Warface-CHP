#pragma once

#include <string>

    struct Aimbot {
        bool enabled { false };
        int aimbot { 0 };
        int bone { 1 };
        int FOV { 45 };
    }aimbot;

    struct Wallhack {
        bool glowEnabled{ false };
        bool glowHealthbased{ false };
        bool glowHidden{ true };
        bool glowVisible{ true };
        float glowColor[3]{ 0,1,0 };
        float glowColorHide[3]{ 1,0,0 };

    };



    