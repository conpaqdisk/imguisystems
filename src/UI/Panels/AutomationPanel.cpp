#include "AutomationPanel.h"
#include <imgui.h>
#include "../../Core/AppState.h"
#include "../Core/UIComponents.h"

namespace UI
{
    void AutomationPanel::Render()
    {
        Components::DrawPageTitle("Otomasyon (Makro/Kural)", "Eger [X] olursa [Y] yap kural motoru");
        auto& state = Core::AppState::Get();

        if (ImGui::BeginTable("AutoGrid", 2, ImGuiTableFlags_PadOuterX))
        {
            ImGui::TableNextRow();

            // SOL SUTUN
            ImGui::TableSetColumnIndex(0);
            
            Components::DrawCard("RuleBuilder", "KURAL OLUSTURUCU", [&]()
            {
                ImGui::Checkbox("Otomasyon Motoru Aktif", &state.Automation.active);
                
                ImGui::Separator();
                
                ImGui::TextDisabled("Eger (KOSUL)");
                static int conditionType = 0;
                const char* conditions[] = { "HP %50 altina duserse", "MP %20 altina duserse", "Karakter olurse", "Biri PM atarsa", "Silah patlarsa" };
                ImGui::Combo("##Cond", &conditionType, conditions, 5);
                
                ImGui::Spacing();
                
                ImGui::TextDisabled("O zaman (EYLEM)");
                static int actionType = 0;
                const char* actions[] = { "Town at", "Botu durdur", "Oyundan cik", "Sese uyari ver", "RPR'ye git" };
                ImGui::Combo("##Action", &actionType, actions, 5);
                
                ImGui::Spacing();
                
                if (ImGui::Button("Kurali Ekle", ImVec2(-1, 0)))
                {
                    state.Automation.rules.push_back(std::string(conditions[conditionType]) + " -> " + std::string(actions[actionType]));
                }
            });

            // SAG SUTUN
            ImGui::TableSetColumnIndex(1);
            
            Components::DrawCard("RuleList", "AKTIF KURALLAR", [&]()
            {
                if (state.Automation.rules.empty())
                {
                    ImGui::TextDisabled("Henuz bir kural eklenmedi.");
                }
                else
                {
                    if (ImGui::BeginTable("RuleTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
                    {
                        ImGui::TableSetupColumn("Kural", ImGuiTableColumnFlags_WidthStretch);
                        ImGui::TableSetupColumn("Islem", ImGuiTableColumnFlags_WidthFixed, 50.0f);
                        ImGui::TableHeadersRow();

                        for (size_t i = 0; i < state.Automation.rules.size(); ++i)
                        {
                            ImGui::TableNextRow();
                            
                            ImGui::TableSetColumnIndex(0);
                            ImGui::TextUnformatted(state.Automation.rules[i].c_str());

                            ImGui::TableSetColumnIndex(1);
                            std::string btnLabel = "Sil##r" + std::to_string(i);
                            if (ImGui::Button(btnLabel.c_str()))
                            {
                                state.Automation.rules.erase(state.Automation.rules.begin() + i);
                                i--; 
                            }
                        }
                        ImGui::EndTable();
                    }
                }
            });

            ImGui::EndTable();
        }
    }
}
