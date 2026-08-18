#include "CombatPanel.h"
#include <imgui.h>
#include "../../Core/AppState.h"
#include "../../Core/GameData.h"
#include "../Core/UIComponents.h"

namespace UI
{
    void CombatPanel::Render()
    {
        Components::DrawPageTitle("Savas ve Saldiri", "Temel saldiri, hedef secimi ve atak ayarlari");
        auto& state = Core::AppState::Get();

        if (ImGui::BeginTable("CombatGrid", 2, ImGuiTableFlags_PadOuterX))
        {
            ImGui::TableNextRow();

            // SOL SUTUN
            ImGui::TableSetColumnIndex(0);
            
            Components::DrawCard("AttackCard", "SALDIRI AYARLARI", [&]()
            {
                ImGui::Checkbox("Saldiriyi Aktif Et", &state.Combat.attackActive);
                
                ImGui::Separator();
                
                ImGui::TextDisabled("Hedef Secim Modu");
                const char* selectionModes[] = { "Otomatik Secim", "Manuel Secim", "Listeden Secim" };
                ImGui::Combo("##TargetMode", &state.Combat.selectionMode, selectionModes, 3);
                
                ImGui::Spacing();
                
                ImGui::SliderInt("Saldiri Hizi (ms)", &state.Combat.attackSpeed, 10, 1000);
                ImGui::SliderInt("Saldiri Mesafesi", &state.Combat.attackDistance, 1, 100);
                ImGui::SliderInt("Hedef Secim Mesafesi", &state.Combat.targetDistance, 10, 200);
                
                ImGui::Separator();
                ImGui::Checkbox("Kill Steal (KS) Modu", &state.Combat.ksMode);
                Components::DrawTooltip("Baska oyuncularin dalmakta oldugu yaratiklara saldirir.");
            });

            // SAG SUTUN
            ImGui::TableSetColumnIndex(1);
            
            Components::DrawCard("SkillCard", "AKTIF YETENEKLER", [&]()
            {
                auto& skillsData = Core::GameData::Get().GetSkills();
                static std::string searchSkill = "";
                static char searchBufSkill[128] = "";

                ImGui::InputTextWithHint("##searchSkill", "Yetenek Ara...", searchBufSkill, IM_ARRAYSIZE(searchBufSkill));
                searchSkill = searchBufSkill;

                if (ImGui::BeginCombo("Yetenek Ekle", "Yetenek Sec..."))
                {
                    for (const auto& skill : skillsData)
                    {
                        if (!searchSkill.empty() && skill.name.find(searchSkill) == std::string::npos && skill.listName.find(searchSkill) == std::string::npos)
                            continue;

                        std::string displayStr = "[" + skill.listName + "] " + skill.name;
                        if (ImGui::Selectable(displayStr.c_str()))
                        {
                            Core::SkillConfig newSkill;
                            newSkill.id = skill.id;
                            newSkill.name = displayStr;
                            newSkill.enabled = true;
                            newSkill.priority = 1;
                            state.Combat.activeSkills.push_back(newSkill);
                        }
                    }
                    ImGui::EndCombo();
                }

                ImGui::Spacing();

                if (state.Combat.activeSkills.empty())
                {
                    ImGui::TextDisabled("Henuz bir yetenek eklenmedi.");
                }
                else
                {
                    if (ImGui::BeginTable("SkillTable", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
                    {
                        ImGui::TableSetupColumn("Durum", ImGuiTableColumnFlags_WidthFixed, 40.0f);
                        ImGui::TableSetupColumn("Yetenek Adi", ImGuiTableColumnFlags_WidthStretch);
                        ImGui::TableSetupColumn("Oncelik", ImGuiTableColumnFlags_WidthFixed, 60.0f);
                        ImGui::TableSetupColumn("Islem", ImGuiTableColumnFlags_WidthFixed, 50.0f);
                        ImGui::TableHeadersRow();

                        for (size_t i = 0; i < state.Combat.activeSkills.size(); ++i)
                        {
                            auto& skill = state.Combat.activeSkills[i];
                            ImGui::TableNextRow();
                            
                            ImGui::TableSetColumnIndex(0);
                            std::string chkLabel = "##chk" + std::to_string(i);
                            ImGui::Checkbox(chkLabel.c_str(), &skill.enabled);

                            ImGui::TableSetColumnIndex(1);
                            ImGui::TextUnformatted(skill.name.c_str());

                            ImGui::TableSetColumnIndex(2);
                            std::string priLabel = "##pri" + std::to_string(i);
                            ImGui::SetNextItemWidth(50.0f);
                            ImGui::InputInt(priLabel.c_str(), &skill.priority, 0);

                            ImGui::TableSetColumnIndex(3);
                            std::string btnLabel = "Sil##" + std::to_string(i);
                            if (ImGui::Button(btnLabel.c_str()))
                            {
                                state.Combat.activeSkills.erase(state.Combat.activeSkills.begin() + i);
                                i--; // Adjust index after erase
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
