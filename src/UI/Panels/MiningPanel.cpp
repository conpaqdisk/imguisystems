#include "MiningPanel.h"
#include <imgui.h>
#include "../../Core/AppState.h"
#include "../Core/UIComponents.h"

namespace UI
{
    void MiningPanel::Render()
    {
        Components::DrawPageTitle("Maden (Mining)", "Otomatik maden, rpr ve banka ayarlari");
        auto& state = Core::AppState::Get();

        if (ImGui::BeginTable("MiningGrid", 2, ImGuiTableFlags_PadOuterX))
        {
            ImGui::TableNextRow();

            // SOL SUTUN
            ImGui::TableSetColumnIndex(0);
            
            Components::DrawCard("MiningSettings", "MADEN AYARLARI", [&]()
            {
                ImGui::Checkbox("Maden Botunu Aktif Et", &state.Farming.miningActive);
                
                ImGui::Separator();
                
                ImGui::TextDisabled("Mattock (Kazma) Durumu");
                ImGui::Checkbox("Otomatik RPR (Kazma kirilinca)", &state.Inventory.rprActive);
                
                ImGui::Spacing();
                ImGui::TextDisabled("RPR Gidis Yontemi");
                static int rprMode = 0;
                const char* modes[] = { "Yuruyerek", "Town Atarak" };
                ImGui::Combo("Yontem", &rprMode, modes, 2);
            });

            // SAG SUTUN
            ImGui::TableSetColumnIndex(1);
            
            Components::DrawCard("MiningLoot", "TOPLANANLAR", [&]()
            {
                static bool keepGems = true;
                static bool keepFragments = true;
                static bool keepOres = false;
                static bool destroyJunk = true;

                ImGui::Checkbox("Gem'leri Sakla (Bankaya At)", &keepGems);
                ImGui::Checkbox("Fragmentleri Sakla", &keepFragments);
                ImGui::Checkbox("Mysterious Ore Sakla", &keepOres);
                ImGui::Checkbox("Copleri Yok Et (Sil)", &destroyJunk);
            });

            ImGui::EndTable();
        }
    }
}
