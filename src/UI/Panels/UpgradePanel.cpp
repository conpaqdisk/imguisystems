#include "UpgradePanel.h"
#include <imgui.h>
#include "../../Core/AppState.h"
#include "../Core/UIComponents.h"

namespace UI
{
    void UpgradePanel::Render()
    {
        Components::DrawPageTitle("Upgrade & RPR", "Otomatik esya basma ve tamir rotalari");
        auto& state = Core::AppState::Get();

        if (ImGui::BeginTable("UpgradeGrid", 2, ImGuiTableFlags_PadOuterX))
        {
            ImGui::TableNextRow();

            // SOL SUTUN
            ImGui::TableSetColumnIndex(0);
            
            Components::DrawCard("UpgradeCard", "OTO UPGRADE", [&]()
            {
                static bool upgradeActive = false;
                ImGui::Checkbox("Oto Upgrade Aktif", &upgradeActive);

                ImGui::Separator();
                
                static char upgItem[64] = "";
                static int upgFrom = 1;
                static int upgTo = 8;
                static int upgScroll = 0; // 0=BUS, 1=BES
                const char* scrolls[] = { "Blessed Upgrade Scroll", "Blessed Elemental Scroll", "Middle Class" };

                ImGui::InputText("Item Adi", upgItem, IM_ARRAYSIZE(upgItem));
                ImGui::InputInt("Nereden (+)", &upgFrom, 1, 1);
                ImGui::InputInt("Nereye (+)", &upgTo, 1, 1);
                ImGui::Combo("Scroll", &upgScroll, scrolls, 3);
                
                if (ImGui::Button("Listeye Ekle", ImVec2(-1, 0))) { /* placeholder */ }
                
                ImGui::Spacing();
                
                if (ImGui::BeginTable("UpgTable", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
                {
                    ImGui::TableSetupColumn("Item", ImGuiTableColumnFlags_WidthStretch);
                    ImGui::TableSetupColumn("Baslangic", ImGuiTableColumnFlags_WidthFixed, 40.0f);
                    ImGui::TableSetupColumn("Hedef", ImGuiTableColumnFlags_WidthFixed, 40.0f);
                    ImGui::TableSetupColumn("Islem", ImGuiTableColumnFlags_WidthFixed, 50.0f);
                    ImGui::TableHeadersRow();

                    // Placeholder
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::Text("Raptor");
                    ImGui::TableSetColumnIndex(1); ImGui::Text("+1");
                    ImGui::TableSetColumnIndex(2); ImGui::Text("+8");
                    ImGui::TableSetColumnIndex(3); ImGui::Button("Sil");

                    ImGui::EndTable();
                }
            });

            // SAG SUTUN
            ImGui::TableSetColumnIndex(1);
            
            Components::DrawCard("RPRCard", "RPR & ROTA AYARLARI", [&]()
            {
                ImGui::Checkbox("RPR Islemi Aktif", &state.Inventory.rprActive);
                ImGui::SliderInt("Durability (Dayaniklilik) <", &state.Inventory.rprThreshold, 1, 1000);
                
                ImGui::Separator();
                ImGui::TextDisabled("Gidilecek Rota / Yontem");
                static int rprMethod = 0;
                const char* methods[] = { "Yuruyerek", "Town Atarak", "Magic Hammer" };
                ImGui::Combo("Yontem", &rprMethod, methods, 3);
            });

            ImGui::EndTable();
        }
    }
}
