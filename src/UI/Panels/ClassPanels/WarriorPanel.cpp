#include "WarriorPanel.h"
#include <imgui.h>
#include <algorithm>
#include "../../../Core/AppState.h"
#include "../../../Core/GameData.h"
#include "../../Core/UIComponents.h"

namespace UI
{
    void WarriorPanel::Render()
    {
        Components::DrawPageTitle("Warrior Skilleri", "Provoke, berserker ve defans ayarlari");
        auto& state = Core::AppState::Get();

        if (ImGui::BeginTable("WarriorGrid", 2, ImGuiTableFlags_PadOuterX))
        {
            ImGui::TableNextRow();

            // SOL SUTUN
            ImGui::TableSetColumnIndex(0);
            
            Components::DrawCard("WarriorSkills", "SALDIRI YETENEKLERI", [&]()
            {
                static bool useProvoke = false;
                static bool useBerserker = false;
                static bool useLegCut = false;

                ImGui::Checkbox("Otomatik Provoke Kullan (Alan Mob Cekme)", &useProvoke);
                ImGui::Checkbox("Berserker (Yuzde Atak) Kullan", &useBerserker);
                ImGui::Checkbox("Kacanlara Leg Cut Vur", &useLegCut);

                ImGui::Separator();
                ImGui::TextDisabled("Warrior Yetenekleri:");
                if (ImGui::BeginListBox("##warrior_skills", ImVec2(-FLT_MIN, 250)))
                {
                    for (const auto& skill : Core::GameData::Get().GetSkills())
                    {
                        if (skill.listName.find("Warrior") != std::string::npos)
                        {
                            bool isSelected = false;
                            for (auto& s : state.Combat.activeSkills) if (s.id == skill.id) isSelected = true;
                            if (ImGui::Checkbox(skill.name.c_str(), &isSelected))
                            {
                                if (isSelected) {
                                    Core::SkillConfig sc; sc.id = skill.id; sc.name = skill.name; sc.enabled = true;
                                    state.Combat.activeSkills.push_back(sc);
                                } else {
                                    state.Combat.activeSkills.erase(std::remove_if(state.Combat.activeSkills.begin(), state.Combat.activeSkills.end(), [&](const Core::SkillConfig& s){ return s.id == skill.id; }), state.Combat.activeSkills.end());
                                }
                            }
                        }
                    }
                    ImGui::EndListBox();
                }
            });

            // SAG SUTUN
            ImGui::TableSetColumnIndex(1);
            
            Components::DrawCard("WarriorDef", "DEFANS & BUFF", [&]()
            {
                static bool autoSprint = false;
                static bool autoDef = false;
                
                ImGui::Checkbox("Otomatik Sprint/Swift", &autoSprint);
                ImGui::Checkbox("Otomatik Defans (Kalkan/Sword Aura)", &autoDef);
            });

            ImGui::EndTable();
        }
    }
}
