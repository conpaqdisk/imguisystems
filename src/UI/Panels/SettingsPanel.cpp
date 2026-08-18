#include "SettingsPanel.h"
#include <imgui.h>
#include "../../Core/AppState.h"
#include "../Core/ThemeManager.h"
#include "../Core/UIComponents.h"
#include "DemoPanel.h"

namespace UI
{
    void SettingsPanel::Render()
    {
        Components::DrawPageTitle("Ayarlar & Profiller", "Arayuz ayarlari, tema ve profil kaydetme/yukleme");
        auto& state = Core::AppState::Get();

        if (ImGui::BeginTable("SettingsGrid", 2, ImGuiTableFlags_PadOuterX))
        {
            ImGui::TableNextRow();

            // SOL SUTUN
            ImGui::TableSetColumnIndex(0);
            
            Components::DrawCard("ThemeCard", "ARAYUZ & TEMA", [&]()
            {
                ImGui::TextDisabled("Tema Secimi");
                const char* themes[] = { "Karanlik (Dark)", "Gece (Midnight)", "Gri (Gray)", "Mavi (Blue)", "Mor (Purple)", "Yesil (Green)" };
                if (ImGui::Combo("##ThemeSelect", &state.Settings.themeId, themes, 6))
                {
                    ThemeManager::ApplyTheme(state.Settings.themeId);
                }
                
                ImGui::Separator();
                
                ImGui::Checkbox("Kompakt Mod", &state.Settings.compactMode);
                Components::DrawTooltip("UI bilesenleri arasindaki bosluklari azaltir.");
                
                ImGui::Checkbox("Animasyonlari Ac", &state.Settings.animations);
                
                ImGui::SliderFloat("Yan Menu Genisligi", &state.Settings.sidebarWidth, 150.0f, 300.0f);

                ImGui::Separator();
                ImGui::TextDisabled("Gelistirici Araclari");
                // Demo artik header icinde
            });

            // SAG SUTUN
            ImGui::TableSetColumnIndex(1);
            
            Components::DrawCard("ProfileCard", "PROFIL YONETIMI", [&]()
            {
                static char profileName[64] = "Varsayilan";
                ImGui::InputText("Profil Adi", profileName, IM_ARRAYSIZE(profileName));
                
                ImGui::Spacing();
                
                if (ImGui::Button("Profili Kaydet", ImVec2(-1, 30)))
                {
                    state.ProfileName = profileName;
                    // Logic to save to JSON would go here
                }
                
                ImGui::Spacing();
                
                if (ImGui::Button("Profili Yukle", ImVec2(-1, 30)))
                {
                    state.ProfileName = profileName;
                    // Logic to load from JSON would go here
                }
                
                ImGui::Separator();
                
                if (ImGui::Button("Varsayilan Ayarlara Don", ImVec2(-1, 30)))
                {
                    // Logic to reset settings
                }
            });

            ImGui::EndTable();
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        if (ImGui::CollapsingHeader("DEAR IMGUI DEMO BİLEŞENLERİ", ImGuiTreeNodeFlags_None))
        {
            static DemoPanel demoPanel;
            demoPanel.Render();
        }
    }
}
