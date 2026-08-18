#include "PriestPanel.h"
#include <imgui.h>
#include <algorithm>
#include "../../../Core/AppState.h"
#include "../../../Core/GameData.h"
#include "../../Core/UIComponents.h"

namespace UI
{
    void PriestPanel::Render()
    {
        Components::DrawPageTitle("Priest Skilleri", "Oto Heal, Buff, AC, Cure ve Rez ayarlari");
        auto& state = Core::AppState::Get();

        if (ImGui::BeginTable("PriestGrid", 2, ImGuiTableFlags_PadOuterX))
        {
            ImGui::TableNextRow();

            // SOL SUTUN
            ImGui::TableSetColumnIndex(0);
            
            Components::DrawCard("HealCard", "HEAL (IYILESTIRME)", [&]()
            {
                ImGui::Checkbox("Kendini Iyilestir (Heal)", &state.Priest.healSelfEnabled);
                if (state.Priest.healSelfEnabled)
                {
                    ImGui::Indent();
                    ImGui::SliderInt("HP Siniri (%)##HealSelf", &state.Priest.healSelfThreshold, 1, 99);
                    ImGui::Unindent();
                }

                ImGui::Separator();
                
                ImGui::Checkbox("Party'yi Iyilestir", &state.Priest.healPartyEnabled);
                if (state.Priest.healPartyEnabled)
                {
                    ImGui::Indent();
                    ImGui::SliderInt("HP Siniri (%)##HealParty", &state.Priest.healPartyThreshold, 1, 99);
                    ImGui::Unindent();
                }

                ImGui::Separator();
                
                ImGui::Checkbox("Hasara Gore Otomatik Heal Sec (1920/10k)", &state.Priest.autoHeal);
            });
            
            ImGui::Spacing();
            
            Components::DrawCard("CureCard", "CURE & REZ", [&]()
            {
                ImGui::Checkbox("Oto Kendine Cure (Cure Curse/Disease)", &state.Priest.autoCure);
                ImGui::Checkbox("Oto Party Cure", &state.Priest.partyCure);
                ImGui::Checkbox("Oto Rez (Oleni Kaldir)", &state.Priest.autoRez);
            });

            // SAG SUTUN
            ImGui::TableSetColumnIndex(1);
            
            Components::DrawCard("BuffCard", "BUFF & AC", [&]()
            {
                ImGui::Checkbox("Oto Buff/AC Aktif", &state.Priest.buffActive);
                
                ImGui::Separator();
                
                ImGui::TextDisabled("Buff Yetenegi");
                static char buffStr[64] = "";
                ImGui::InputText("Buff (HP)", buffStr, IM_ARRAYSIZE(buffStr));
                state.Priest.buffSkill = buffStr;
                
                ImGui::TextDisabled("AC (Defans) Yetenegi");
                static char acStr[64] = "";
                ImGui::InputText("AC", acStr, IM_ARRAYSIZE(acStr));
                state.Priest.acSkill = acStr;
                
                ImGui::TextDisabled("Mind (Str/Dex/HP) Yetenegi");
                static char mindStr[64] = "";
                ImGui::InputText("Mind", mindStr, IM_ARRAYSIZE(mindStr));
                state.Priest.mindSkill = mindStr;
                
                ImGui::Separator();
                
                static bool buffParty = true;
                ImGui::Checkbox("Party Uyelerine Buff At", &buffParty);

                ImGui::Separator();
                ImGui::TextDisabled("Priest Yetenekleri (DB/Heal/Buff vb.):");
                if (ImGui::BeginListBox("##priest_skills", ImVec2(-FLT_MIN, 250)))
                {
                    for (const auto& skill : Core::GameData::Get().GetSkills())
                    {
                        if (skill.listName.find("Priest") != std::string::npos)
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

            ImGui::EndTable();
        }
    }
}
