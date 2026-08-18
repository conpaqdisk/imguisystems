#include "MagePanel.h"
#include <imgui.h>
#include <algorithm>
#include "../../../Core/AppState.h"
#include "../../../Core/GameData.h"
#include "../../Core/UIComponents.h"

namespace UI
{
    void MagePanel::Render()
    {
        Components::DrawPageTitle("Mage Skilleri", "Alan (AOE) skilleri, tp ayarlari");
        auto& state = Core::AppState::Get();

        if (ImGui::BeginTable("MageGrid", 2, ImGuiTableFlags_PadOuterX))
        {
            ImGui::TableNextRow();

            // SOL SUTUN
            ImGui::TableSetColumnIndex(0);
            
            Components::DrawCard("MageSkills", "SALDIRI YETENEKLERI", [&]()
            {
                static int mageMode = 0;
                const char* modes[] = { "Sadece Secili Mob (Tekli)", "Alan Skilleri (AOE)", "Karisik" };
                ImGui::Combo("Saldiri Tipi", &mageMode, modes, 3);
                
                static bool autoTown = false;
                ImGui::Checkbox("HP %20 Altindaysa Town", &autoTown);

                ImGui::Separator();
                ImGui::TextDisabled("Mage Yetenekleri:");
                if (ImGui::BeginListBox("##mage_skills", ImVec2(-FLT_MIN, 250)))
                {
                    for (const auto& skill : Core::GameData::Get().GetSkills())
                    {
                        if (skill.listName.find("Mage") != std::string::npos)
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
            
            Components::DrawCard("MageSupport", "DESTEK & TP", [&]()
            {
                static bool autoTP = false;
                static bool tpToTown = false;
                
                ImGui::Checkbox("Otomatik Party TP (Gelenleri Cek)", &autoTP);
                ImGui::Checkbox("Olenleri Town Cek", &tpToTown);
                
                ImGui::Separator();
                
                static bool autoResist = false;
                static bool autoArmor = false;
                
                ImGui::Checkbox("Oto Resist Buff (Lightning/Glacier/Fire)", &autoResist);
                ImGui::Checkbox("Oto Armor Buff (Absolute Power/Def)", &autoArmor);
            });

            ImGui::EndTable();
        }
    }
}
