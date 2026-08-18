#include "SupplyPanel.h"
#include <imgui.h>
#include "../../Core/AppState.h"
#include "../Core/UIComponents.h"

namespace UI
{
    void SupplyPanel::Render()
    {
        Components::DrawPageTitle("Tedarik (Supply)", "Sundries uzerinden otomatik esya alimi");
        auto& state = Core::AppState::Get();

        if (ImGui::BeginTable("SupplyGrid", 2, ImGuiTableFlags_PadOuterX))
        {
            ImGui::TableNextRow();

            // SOL SUTUN
            ImGui::TableSetColumnIndex(0);
            
            Components::DrawCard("SupplySettings", "TEDARIK AYARLARI", [&]()
            {
                ImGui::Checkbox("Tedarik Sistemini Aktif Et", &state.Supply.enabled);
                
                ImGui::Separator();
                ImGui::TextDisabled("NPC Ayari");
                static char npcIdStr[64] = "";
                ImGui::InputText("Sundries NPC ID", npcIdStr, IM_ARRAYSIZE(npcIdStr));
                state.Supply.npcId = npcIdStr;
            });

            ImGui::Spacing();
            
            Components::DrawCard("SupplyLimits", "TEDARIK LIMITLERI", [&]()
            {
                ImGui::TextDisabled("HP Potion (Weight/Miktar)");
                ImGui::InputInt("Min HP Pot", &state.Supply.minHpPotions, 10, 100);
                ImGui::InputInt("Max HP Pot", &state.Supply.maxHpPotions, 10, 100);
                
                ImGui::Separator();
                ImGui::TextDisabled("MP Potion (Weight/Miktar)");
                ImGui::InputInt("Min MP Pot", &state.Supply.minMpPotions, 10, 100);
                ImGui::InputInt("Max MP Pot", &state.Supply.maxMpPotions, 10, 100);
                
                ImGui::Separator();
                ImGui::TextDisabled("Ok (Arrow)");
                ImGui::InputInt("Min Ok", &state.Supply.minArrows, 100, 1000);
                ImGui::InputInt("Max Ok", &state.Supply.maxArrows, 100, 1000);
            });

            // SAG SUTUN
            ImGui::TableSetColumnIndex(1);
            
            Components::DrawCard("SupplyOther", "EKSTRALAR", [&]()
            {
                static bool buyWolf = false;
                static bool buyTS = false;
                static bool buyGem = false;

                ImGui::Checkbox("Oto Wolf (Scroll) Al", &buyWolf);
                ImGui::Checkbox("Oto TS (Transformation Scroll) Al", &buyTS);
                ImGui::Checkbox("Oto Gem/Fragment Al", &buyGem);
            });

            ImGui::EndTable();
        }
    }
}
