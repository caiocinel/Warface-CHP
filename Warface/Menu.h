#pragma once
constexpr auto windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar;
struct {
	bool aimbot = false;
	bool wallhack = false;
	bool visuais = false;
	bool outros = false;
} window;
constexpr auto windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar;

void DrawMenu() {

	ImGui::SetNextWindowSize({ 100.0f, 0.0f });
	ImGui::Begin(XorString("BRCheats"), nullptr, windowFlags);
	ImGui::TextUnformatted(XorString("BRCheats"));
	ImGui::PushItemWidth(80.0f);
	if (ImGui::Button(XorString("Aimbot"), { 80.0f, 20.0f })) {
		window.aimbot = !window.aimbot;
	}
	if (ImGui::Button(XorString("Wallhack"), { 80.0f, 20.0f })) {
		window.wallhack = !window.wallhack;
	}
	if (ImGui::Button(XorString("Visuais"), { 80.0f, 20.0f })) {
		window.visuais = !window.visuais;
	}
	if (ImGui::Button(XorString("Outros"), { 80.0f, 20.0f })) {
		window.outros = !window.outros;
	}
	ImGui::PopItemWidth();

}

