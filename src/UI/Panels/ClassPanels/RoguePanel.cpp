#include "RoguePanel.h"
#include <imgui.h>
#include <algorithm>
#include "../../../Core/AppState.h"
#include "../../../Core/GameData.h"
#include "../../Core/UIComponents.h"

namespace UI
{
    void RoguePanel::Render()
    {
        Components::DrawPageTitle("Rogue Skilleri", "Asas ve Okcu (Archer) yetenekleri, minör ve oto-ok ayarlari");
        auto& state = Core::AppState::Get();

        if (ImGui::BeginTable("RogueGrid", 2, ImGuiTableFlags_PadOuterX))
        {
            ImGui::TableNextRow();

            // SOL SUTUN
            ImGui::TableSetColumnIndex(0);
            
            Components::DrawCard("AssassinCard", "ASAS YETENEKLERI", [&]()
            {
                ImGui::Checkbox("Spike/Thrust (Cift Vurus) Aktif", &state.Rogue.useStroke);
                
                static bool autoLightFeet = true;
                static bool autoLupus = false;
                static bool autoStealth = false;

                ImGui::Checkbox("Oto Light Feet", &autoLightFeet);
                ImGui::Checkbox("Oto Lupus/Cure", &autoLupus);
                ImGui::Checkbox("Gorunmezlik (Stealth) Korumasi", &autoStealth);

                ImGui::Separator();
                ImGui::TextDisabled("Asas Yetenekleri:");
                if (ImGui::BeginListBox("##asas_skills", ImVec2(-FLT_MIN, 150)))
                {
                    for (const auto& skill : Core::GameData::Get().GetSkills())
                    {
                        if (skill.listName == "RogueAsasAttackSkillsList" || skill.listName == "RogueSupportSkillsList")
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
            
            Components::DrawCard("ArcherCard", "OKCU YETENEKLERI", [&]()
            {
                ImGui::Checkbox("Okcu Modu (Uzaktan Saldiri)", &state.Rogue.useArchery);
                
                static int archerComboMode = 0;
                const char* combos[] = { "Tekli Ok (3lu/5li Kapali)", "Oto 3'lu Ok", "Oto 5'li Ok", "Karisik (Mesafe Bazli)" };
                ImGui::Combo("Ok Kombo Modu", &archerComboMode, combos, 4);
                
                static bool autoArrow = true;
                ImGui::Checkbox("Otomatik Sonsuz Ok (Infinite Arrow)", &autoArrow);

                ImGui::Separator();
                ImGui::TextDisabled("Okcu Yetenekleri:");
                if (ImGui::BeginListBox("##archer_skills", ImVec2(-FLT_MIN, 150)))
                {
                    for (const auto& skill : Core::GameData::Get().GetSkills())
                    {
                        if (skill.listName == "RogueAttackSkillsList")
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
