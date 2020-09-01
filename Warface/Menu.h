#pragma once

constexpr auto windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar;

void DrawMenu() {

    ImGui::SetNextWindowSize({ 0.0f, 0.0f });
    ImGui::Begin(XorString("BRCheats"), nullptr, windowFlags);
    ImGui::TextUnformatted(XorString("BRCheats Warface"));
if (ImGui::BeginTabBar(XorString("TabBar"), ImGuiTabBarFlags_NoTooltip)) {
    if (ImGui::BeginTabItem(XorString("Aimbot"))) {
        ImGui::Checkbox(XorString("Aimbot Vector"), &MvectorAim);
        ImGui::Checkbox(XorString("Aimbot Silent"), &mSilent);
        ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem(XorString("Wallhack"))) {
        ImGui::Checkbox(XorString("Glow"), &MGlow);
        if (MGlow){
            ImGui::SameLine();
            ImGui::Checkbox(XorString("Health Based"), &MGlowHB);
        }
        ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem(XorString("Weapons"))) {
        ImGui::Checkbox(XorString("No Recoil/Spread"), &Mprecisao);
        ImGui::Checkbox(XorString("Rapid Fire"), &mShutter);
        ImGui::Checkbox(XorString("Infinite Ammo"), &mAmmo);
        ImGui::Checkbox(XorString("Extra Damage"), &Mdamage);
        if (Mdamage){
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

