#include "FishingPanel.h"
#include <imgui.h>
#include "../../Core/AppState.h"
#include "../Core/UIComponents.h"

namespace UI
{
    void FishingPanel::Render()
    {
        Components::DrawPageTitle("Balikcilik (Fishing)", "Otomatik balik tutma ve rpr ayarlari");
        auto& state = Core::AppState::Get();

        if (ImGui::BeginTable("FishingGrid", 2, ImGuiTableFlags_PadOuterX))
        {
            ImGui::TableNextRow();

            // SOL SUTUN
            ImGui::TableSetColumnIndex(0);
            
            Components::DrawCard("FishingSettings", "BALIKCILIK AYARLARI", [&]()
            {
                ImGui::Checkbox("Balik Botunu Aktif Et", &state.Farming.fishingActive);
                
                ImGui::Separator();
                
                ImGui::TextDisabled("Olta / Solucan Durumu");
                ImGui::Checkbox("Otomatik Solucan (Worm) Al", &state.Supply.enabled);
                ImGui::Checkbox("Olta RPR (Kirilinca)", &state.Inventory.rprActive);
                
                ImGui::Spacing();
                static char fishingNpc[64] = "";
                ImGui::InputText("Sundries (Solucan) NPC", fishingNpc, IM_ARRAYSIZE(fishingNpc));
            });

            // SAG SUTUN
            ImGui::TableSetColumnIndex(1);
            
            Components::DrawCard("FishingLoot", "TOPLANANLAR", [&]()
            {
                static bool keepFlash = true;
                static bool keepFish = false;
                static bool destroyJunk = true;

                ImGui::Checkbox("Flash'lari Sakla (Exp, DC, War)", &keepFlash);
                ImGui::Checkbox("Baliklari Sakla (HP/MP Pot yerine)", &keepFish);
                ImGui::Checkbox("Copleri Yok Et (Sil)", &destroyJunk);
            });

            ImGui::EndTable();
        }
    }
}
