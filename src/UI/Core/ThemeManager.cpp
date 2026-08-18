#include "ThemeManager.h"
#include <imgui.h>

namespace UI
{
    void ThemeManager::ApplyTheme(int themeIndex)
    {
        ApplyBaseStyle();

        switch (themeIndex)
        {
            case 0: ApplyDark(); break;
            case 1: ApplyMidnight(); break;
            case 2: ApplyGray(); break;
            case 3: ApplyBlue(); break;
            case 4: ApplyPurple(); break;
            case 5: ApplyGreen(); break;
            default: ApplyDark(); break;
        }
    }

    void ThemeManager::ApplyBaseStyle()
    {
        ImGuiStyle& style = ImGui::GetStyle();

        style.WindowPadding = ImVec2(10.0f, 10.0f);
        style.FramePadding = ImVec2(8.0f, 4.0f);
        style.CellPadding = ImVec2(6.0f, 4.0f);
        style.ItemSpacing = ImVec2(8.0f, 6.0f);
        style.ItemInnerSpacing = ImVec2(6.0f, 4.0f);
        style.ScrollbarSize = 12.0f;
        style.GrabMinSize = 10.0f;

        style.WindowRounding = 6.0f;
        style.ChildRounding = 6.0f;
        style.FrameRounding = 4.0f;
        style.PopupRounding = 6.0f;
        style.ScrollbarRounding = 6.0f;
        style.GrabRounding = 4.0f;
        style.TabRounding = 4.0f;

        style.WindowBorderSize = 1.0f;
        style.ChildBorderSize = 1.0f;
        style.PopupBorderSize = 1.0f;
        style.FrameBorderSize = 0.0f;
        style.TabBorderSize = 0.0f;
    }

    void ThemeManager::ApplyDark()
    {
        ImGui::StyleColorsDark();
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;

        colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.98f, 0.40f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
        colors[ImGuiCol_Text] = ImVec4(0.90f, 0.95f, 1.00f, 1.00f);
    }

    void ThemeManager::ApplyMidnight()
    {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;

        colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.08f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.08f, 0.08f, 0.12f, 1.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.12f, 1.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.12f, 0.18f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.18f, 0.18f, 0.25f, 1.00f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.25f, 0.25f, 0.35f, 1.00f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.03f, 0.03f, 0.05f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.03f, 0.03f, 0.05f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.40f, 0.70f, 1.00f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(0.12f, 0.12f, 0.18f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.18f, 0.18f, 0.25f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.25f, 0.25f, 0.35f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.12f, 0.12f, 0.18f, 1.00f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.18f, 0.18f, 0.25f, 1.00f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.25f, 0.25f, 0.35f, 1.00f);
        colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.95f, 1.00f);
    }

    void ThemeManager::ApplyBlue()
    {
        ImGui::StyleColorsClassic();
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;

        colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.12f, 0.20f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.12f, 0.16f, 0.25f, 1.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.16f, 0.25f, 1.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.18f, 0.24f, 0.35f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.32f, 0.45f, 1.00f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.35f, 0.45f, 0.60f, 1.00f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.05f, 0.08f, 0.15f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.12f, 0.20f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.90f, 1.00f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(0.20f, 0.35f, 0.60f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.45f, 0.75f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.40f, 0.55f, 0.90f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.18f, 0.24f, 0.35f, 1.00f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.32f, 0.45f, 1.00f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.35f, 0.45f, 0.60f, 1.00f);
        colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    }

    void ThemeManager::InitializeFonts(float scale)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImFontConfig fontConfig;
        fontConfig.OversampleH = 2;
        fontConfig.OversampleV = 2;
        io.Fonts->AddFontDefault(&fontConfig);
        io.FontGlobalScale = scale;
    }

    void ThemeManager::ApplyGray()
    {
        ImGui::StyleColorsDark();
        ImVec4* colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
    }

    void ThemeManager::ApplyPurple()
    {
        ImGui::StyleColorsDark();
        ImVec4* colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.08f, 0.12f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.12f, 0.10f, 0.15f, 1.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.15f, 0.25f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(0.30f, 0.20f, 0.40f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.40f, 0.30f, 0.55f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.50f, 0.40f, 0.70f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.30f, 0.20f, 0.40f, 1.00f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.40f, 0.30f, 0.55f, 1.00f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.50f, 0.40f, 0.70f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.60f, 1.00f, 1.00f);
    }

    void ThemeManager::ApplyGreen()
    {
        ImGui::StyleColorsDark();
        ImVec4* colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.12f, 0.08f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.10f, 0.15f, 0.10f, 1.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.25f, 0.15f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(0.20f, 0.40f, 0.20f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.55f, 0.30f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.40f, 0.70f, 0.40f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.20f, 0.40f, 0.20f, 1.00f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.30f, 0.55f, 0.30f, 1.00f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.40f, 0.70f, 0.40f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.60f, 1.00f, 0.60f, 1.00f);
    }
}
