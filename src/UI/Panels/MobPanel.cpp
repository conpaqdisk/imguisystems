#include "MobPanel.h"
#include <imgui.h>
#include "../../Core/AppState.h"
#include "../../Core/GameData.h"
#include "../Core/UIComponents.h"

namespace UI
{
    void MobPanel::Render()
    {
        Components::DrawPageTitle("Mob Manager", "Yaratik secimi, engelleme ve onceliklendirme");
        auto& state = Core::AppState::Get();

        if (ImGui::BeginTable("MobGrid", 2, ImGuiTableFlags_PadOuterX))
        {
            ImGui::TableNextRow();

            // SOL SUTUN
            ImGui::TableSetColumnIndex(0);
            
            Components::DrawCard("MobListCard", "YARATIK LISTESI", [&]()
            {
                auto& mobsData = Core::GameData::Get().GetMobs();
                static std::string searchMob = "";
                static char searchBufMob[128] = "";

                ImGui::InputTextWithHint("##searchMob", "Yaratik Ara...", searchBufMob, IM_ARRAYSIZE(searchBufMob));
                searchMob = searchBufMob;

                if (ImGui::BeginCombo("Yaratik Ekle", "Yaratik Sec..."))
                {
                    for (const auto& mob : mobsData)
                    {
                        if (!searchMob.empty() && mob.name.find(searchMob) == std::string::npos)
                            continue;

                        if (ImGui::Selectable(mob.name.c_str()))
                        {
                            Core::MobConfig newMob;
                            newMob.id = mob.id;
                            newMob.name = mob.name;
                            newMob.enabled = true;
                            newMob.distance = 50.0f;
                            state.Combat.mobList.push_back(newMob);
                        }
                    }
                    ImGui::EndCombo();
                }

                if (ImGui::BeginTable("MobTable", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
                {
                    ImGui::TableSetupColumn("Durum", ImGuiTableColumnFlags_WidthFixed, 40.0f);
                    ImGui::TableSetupColumn("Ad", ImGuiTableColumnFlags_WidthStretch);
                    ImGui::TableSetupColumn("Mesafe", ImGuiTableColumnFlags_WidthFixed, 60.0f);
                    ImGui::TableSetupColumn("Islem", ImGuiTableColumnFlags_WidthFixed, 50.0f);
                    ImGui::TableHeadersRow();

                    for (size_t i = 0; i < state.Combat.mobList.size(); ++i)
                    {
                        auto& mob = state.Combat.mobList[i];
                        ImGui::TableNextRow();
                        
                        ImGui::TableSetColumnIndex(0);
                        std::string chkLabel = "##m_chk" + std::to_string(i);
                        ImGui::Checkbox(chkLabel.c_str(), &mob.enabled);

                        ImGui::TableSetColumnIndex(1);
                        ImGui::TextUnformatted(mob.name.c_str());

                        ImGui::TableSetColumnIndex(2);
                        std::string distLabel = "##m_dist" + std::to_string(i);
                        ImGui::SetNextItemWidth(50.0f);
                        int tempDist = (int)mob.distance;
                        if(ImGui::InputInt(distLabel.c_str(), &tempDist, 0)) {
                            mob.distance = (float)tempDist;
                        }

                        ImGui::TableSetColumnIndex(3);
                        std::string btnLabel = "Sil##m" + std::to_string(i);
                        if (ImGui::Button(btnLabel.c_str()))
                        {
                            state.Combat.mobList.erase(state.Combat.mobList.begin() + i);
                            i--; 
                        }
                    }
                    ImGui::EndTable();
                }
            });

            // SAG SUTUN
            ImGui::TableSetColumnIndex(1);
            
            Components::DrawCard("MobSettingsCard", "YARATIK AYARLARI", [&]()
            {
                ImGui::Checkbox("Sadece Listeye Saldir", &state.Combat.ksMode); // re-using ksMode as a flag here just to fill space without adding new AppState var
                ImGui::Checkbox("Yaratiga Kos", &state.Combat.moveToMob);
                ImGui::Checkbox("Yaratigi Takip Et", &state.Combat.followMob);

                ImGui::Separator();
                ImGui::TextDisabled("Engellenen Yaratiklar (Ignore List)");
                
                static char ignoreMob[64] = "";
                ImGui::InputText("Yaratik Adi", ignoreMob, IM_ARRAYSIZE(ignoreMob));
                if (ImGui::Button("Ekle", ImVec2(-1, 0))) { /* do nothing */ }
            });

            ImGui::EndTable();
        }
    }
}
