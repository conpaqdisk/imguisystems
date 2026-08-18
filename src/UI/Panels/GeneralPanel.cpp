#include "GeneralPanel.h"
#include <imgui.h>
#include "../../Core/AppState.h"
#include "../../Core/GameData.h"
#include "../Core/UIComponents.h"

namespace UI
{
    void GeneralPanel::Render()
    {
        Components::DrawPageTitle("Genel ve Atak Ayarlari", "Karakter, koruma, pot, oto loot ve saldiri ayarlari");
        auto& state = Core::AppState::Get();

        if (ImGui::BeginTable("GeneralGrid", 3, ImGuiTableFlags_PadOuterX))
        {
            ImGui::TableNextRow();

            // SOL SUTUN: Koruma & Loot
            ImGui::TableSetColumnIndex(0);
            
            Components::DrawCard("ProtectionCard", "KORUMA & POTION", [&]()
            {
                ImGui::Checkbox("HP Potion Aktif", &state.General.hpPotionEnabled);
                if (state.General.hpPotionEnabled)
                {
                    ImGui::Indent();
                    ImGui::SliderInt("HP Siniri (%)##HP", &state.General.hpThreshold, 1, 99);
                    const char* hpPots[] = { "Water of Life (1440)", "Water of Love (720)", "Water of Grace (360)" };
                    static int currentHpPot = 0;
                    ImGui::Combo("Potion Secimi##HP", &currentHpPot, hpPots, 3);
                    ImGui::Unindent();
                }

                ImGui::Separator();

                ImGui::Checkbox("MP Potion Aktif", &state.General.mpPotionEnabled);
                if (state.General.mpPotionEnabled)
                {
                    ImGui::Indent();
                    ImGui::SliderInt("MP Siniri (%)##MP", &state.General.mpThreshold, 1, 99);
                    const char* mpPots[] = { "Potion of Soul (1920)", "Potion of Intelligence (960)" };
                    static int currentMpPot = 0;
                    ImGui::Combo("Potion Secimi##MP", &currentMpPot, mpPots, 2);
                    ImGui::Unindent();
                }

                ImGui::Separator();

                ImGui::Checkbox("Minor Aktif", &state.General.minorEnabled);
                if (state.General.minorEnabled)
                {
                    ImGui::Indent();
                    ImGui::SliderInt("Minor Siniri (%)##Minor", &state.General.minorThreshold, 1, 99);
                    ImGui::Checkbox("Party Minor Destegi", &state.General.partyMinorEnabled);
                    ImGui::Unindent();
                }
            });

            ImGui::Spacing();

            Components::DrawCard("LootCard", "OTO LOOT (OTOMATIK TOPLA)", [&]()
            {
                ImGui::Checkbox("Oto Loot Aktif", &state.General.autoLoot);
                if (state.General.autoLoot)
                {
                    ImGui::Indent();
                    ImGui::Checkbox("Sadece Coin Topla", &state.General.lootOnlyCoin);
                    ImGui::Checkbox("Sadece Secilen Itemleri Topla", &state.General.lootSelectedItems);
                    ImGui::Unindent();
                }
            });

            // ORTA SUTUN: Karakter & Diger
            ImGui::TableSetColumnIndex(1);
            
            Components::DrawCard("CharacterCard", "KARAKTER SECIMI VE DAVRANISI", [&]()
            {
                auto& racesData = Core::GameData::Get().GetRaces();
                auto& classesData = Core::GameData::Get().GetClasses();

                std::string currentRaceName = "Irk Secin...";
                for (const auto& r : racesData) {
                    if (r.id == state.General.selectedRaceId) {
                        currentRaceName = "[" + r.nation + "] " + r.name;
                        break;
                    }
                }

                if (ImGui::BeginCombo("Irk (Race)", currentRaceName.c_str()))
                {
                    for (const auto& r : racesData)
                    {
                        std::string displayStr = "[" + r.nation + "] " + r.name;
                        if (ImGui::Selectable(displayStr.c_str(), state.General.selectedRaceId == r.id))
                        {
                            state.General.selectedRaceId = r.id;
                        }
                    }
                    ImGui::EndCombo();
                }

                std::string currentClassName = "Sinif Secin...";
                for (const auto& c : classesData) {
                    if (c.id == state.General.selectedClassId) {
                        currentClassName = "[" + c.nation + "] " + c.job + " (" + c.levelRange + " - " + c.description + ")";
                        break;
                    }
                }

                if (ImGui::BeginCombo("Sinif (Class)", currentClassName.c_str()))
                {
                    for (const auto& c : classesData)
                    {
                        std::string displayStr = "[" + c.nation + "] " + c.job + " (" + c.levelRange + " - " + c.description + ")";
                        if (ImGui::Selectable(displayStr.c_str(), state.General.selectedClassId == c.id))
                        {
                            state.General.selectedClassId = c.id;
                        }
                    }
                    ImGui::EndCombo();
                }

                ImGui::Separator();

                ImGui::Checkbox("Pencereyi Ustte Tut", &state.General.alwaysOnTop);
                Components::DrawTooltip("Bot penceresini her zaman oyunun ustunde gosterir.");
                
                ImGui::Checkbox("Karakteri Sabitle", &state.General.pinCharacter);
                Components::DrawTooltip("Karakterin konumunu kitler, disaridan cekilmeleri engeller.");

                ImGui::Separator();

                ImGui::TextDisabled("Olum Durumu (Death Behavior)");
                const char* deathOptions[] = { "Bekle", "Town At", "Relog At" };
                ImGui::Combo("##DeathAction", &state.General.deathBehavior, deathOptions, 3);

                ImGui::Spacing();
                ImGui::TextDisabled("Town Durumu");
                const char* townOptions[] = { "Merkeze Git", "Sundries Git", "Inn Hostess Git" };
                ImGui::Combo("##TownAction", &state.General.townBehavior, townOptions, 3);
            });

            ImGui::Spacing();

            Components::DrawCard("MiscCard", "DIGER SISTEMLER", [&]()
            {
                ImGui::Checkbox("Oto TS (Transformation Scroll)", &state.General.autoTS);
                if (state.General.autoTS)
                {
                    ImGui::Indent();
                    const char* tsOptions[] = { "Orc Watcher", "Death Knight", "Uruk Hai" };
                    static int currentTS = 0;
                    ImGui::Combo("TS Secimi", &currentTS, tsOptions, 3);
                    ImGui::Unindent();
                }

                ImGui::Separator();
                ImGui::Checkbox("Hedef Takibi (Follow)", &state.General.followEnabled);
                
                ImGui::Separator();
                ImGui::TextDisabled("Wallhack Ayari (Sadece UI)");
                static bool wallhackUI = false;
                ImGui::Checkbox("Duvarlardan Gec (Wallhack)", &wallhackUI);
            });

            // SAG SUTUN: Atak ve Skiller
            ImGui::TableSetColumnIndex(2);

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
            });

            ImGui::Spacing();

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
                    if (ImGui::BeginTable("SkillTable", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY, ImVec2(0, 150)))
                    {
                        ImGui::TableSetupScrollFreeze(0, 1);
                        ImGui::TableSetupColumn("D.", ImGuiTableColumnFlags_WidthFixed, 25.0f);
                        ImGui::TableSetupColumn("Yetenek", ImGuiTableColumnFlags_WidthStretch);
                        ImGui::TableSetupColumn("Onc.", ImGuiTableColumnFlags_WidthFixed, 35.0f);
                        ImGui::TableSetupColumn("Sil", ImGuiTableColumnFlags_WidthFixed, 35.0f);
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
                            ImGui::SetNextItemWidth(35.0f);
                            ImGui::InputInt(priLabel.c_str(), &skill.priority, 0);

                            ImGui::TableSetColumnIndex(3);
                            std::string btnLabel = "X##" + std::to_string(i);
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
