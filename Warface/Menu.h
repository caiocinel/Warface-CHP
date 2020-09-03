#pragma once

constexpr auto windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;




void DrawMenu() {
    if (bShow) {
        ImGui::SetNextWindowSize({ 0.0f, 0.0f });
        ImGui::Begin(XorString("BRCheats"), &bShow, windowFlags);
        if (ImGui::BeginTabBar(XorString("TabBar"), ImGuiTabBarFlags_NoTooltip)) {
            if (ImGui::BeginTabItem(XorString("Aimbot"))) {
                if (ImGui::Combo(XorString("Aimbot"), &mAimbot, "Desligado\0Vector\0Silent\0"))
                {
                    switch (mAimbot)
                    {
                    case 0: MvectorAim = false; mSilent = false; break;
                    case 1: mSilent = false; MvectorAim = true; break;
                    case 2: MvectorAim = false;mSilent = true; break;
                    }
                }
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem(XorString("Wallhack"))) {
                ImGui::Checkbox(XorString("Skeleton"), &skeleton);
                ImGui::Checkbox(XorString("Glow"), &MGlow);
                if (MGlow) {
                    ImGui::SameLine();
                    ImGui::Checkbox(XorString("Health Based"), &MGlowHB);
                    ImGui::Checkbox(XorString("Show Visible"), &glowVisible);
                    if (glowVisible) { ImGui::ColorEdit3(XorString("Color Visible"), GlowColor, ImGuiColorEditFlags_NoInputs); };
                    ImGui::Checkbox(XorString("Show Hidden"), &glowHidden);
                    if (glowHidden) { ImGui::ColorEdit3(XorString("Color Hidden"), GlowColorHide, ImGuiColorEditFlags_NoInputs); };
                }
               
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem(XorString("Weapons"))) {
                ImGui::Checkbox(XorString("No Recoil/Spread"), &Mprecisao);
                ImGui::Checkbox(XorString("Rapid Fire"), &mShutter);
                ImGui::Checkbox(XorString("Infinite Ammo"), &mAmmo);
                ImGui::Checkbox(XorString("Extra Damage"), &Mdamage);
                if (Mdamage) {
                    ImGui::SameLine();
                    ImGui::SliderInt(XorString("Extra Count"), &damagecount, 1, 30);
                    if (ImGui::IsItemHovered()) {
                        ImGui::SetTooltip("Se maior que 10 pode causar lag, nao use com Rocket");
                    }
                }
                ImGui::Checkbox(XorString("Pickup Range"), &mPickup);
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem(XorString("Visuais"))) {
                ImGui::Checkbox(XorString("No Flash"), &Mnoflash);
                ImGui::Checkbox(XorString("Detect Claymore"), &Mclaymore);
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem(XorString("Outros"))) {
                ImGui::Checkbox(XorString("Long Sprint"), &mSprint);
                ImGui::Checkbox(XorString("No Minimap Spot"), &Mminimap);
                ImGui::Checkbox(XorString("Auto Climb"), &mClimb);
                ImGui::Checkbox(XorString("Ultra Slide"), &Mslide);
                ImGui::Checkbox(XorString("No Sound"), &mNosound);
                ImGui::Checkbox(XorString("Rotate Machine&Shield (Coop)"), &mRotate);
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
        ImGui::End();
    }

}

