#include "PartyPanel.h"
#include <imgui.h>
#include "../../Core/AppState.h"
#include "../Core/UIComponents.h"

namespace UI
{
    void PartyPanel::Render()
    {
        Components::DrawPageTitle("Party", "Party yonetimi, oto kabul ve sinirlar");
        auto& state = Core::AppState::Get();

        if (ImGui::BeginTable("PartyGrid", 2, ImGuiTableFlags_PadOuterX))
        {
            ImGui::TableNextRow();

            // SOL SUTUN
            ImGui::TableSetColumnIndex(0);
            
            Components::DrawCard("PartySettings", "PARTY AYARLARI", [&]()
            {
                ImGui::Checkbox("Oto Party Kabul Et", &state.Party.autoAccept);
                ImGui::Checkbox("Partiden Oto Cik", &state.Party.autoLeave);
                
                ImGui::Separator();
                
                ImGui::SliderInt("Party Uye Limiti", &state.Party.memberLimit, 2, 8);
                
                ImGui::Spacing();
                ImGui::TextDisabled("Party Kabul Edilince Islem");
                const char* acceptActions[] = { "Hicbir Sey Yapma", "Slota Git", "Buff At" };
                ImGui::Combo("##AcceptAction", &state.Party.onAcceptBehavior, acceptActions, 3);
                
                ImGui::Spacing();
                ImGui::TextDisabled("Party Bozulunca Islem");
                const char* breakActions[] = { "Hicbir Sey Yapma", "Town At", "Botu Durdur" };
                ImGui::Combo("##BreakAction", &state.Party.onBreakBehavior, breakActions, 3);
            });

            // SAG SUTUN
            ImGui::TableSetColumnIndex(1);
            
            Components::DrawCard("PartyMembers", "PARTY UYELERI", [&]()
            {
                // Placeholder member list since we don't have a real list in state yet
                if (ImGui::BeginTable("MembersTable", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
                {
                    ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, 30.0f);
                    ImGui::TableSetupColumn("Nick", ImGuiTableColumnFlags_WidthStretch);
                    ImGui::TableSetupColumn("Lvl", ImGuiTableColumnFlags_WidthFixed, 40.0f);
                    ImGui::TableSetupColumn("HP", ImGuiTableColumnFlags_WidthFixed, 60.0f);
                    ImGui::TableHeadersRow();

                    for (int i = 0; i < 3; ++i) // Fake data
                    {
                        ImGui::TableNextRow();
                        ImGui::TableSetColumnIndex(0);
                        ImGui::Text("%d", i+1);
                        ImGui::TableSetColumnIndex(1);
                        ImGui::Text("Member_%d", i);
                        ImGui::TableSetColumnIndex(2);
                        ImGui::Text("80");
                        ImGui::TableSetColumnIndex(3);
                        ImGui::Text("100%%");
                    }
                    ImGui::EndTable();
                }

                ImGui::Separator();
                
                if (ImGui::Button("Party Kur", ImVec2(ImGui::GetContentRegionAvail().x * 0.48f, 0))) { /* do nothing */ }
                ImGui::SameLine();
                if (ImGui::Button("Party Boz", ImVec2(ImGui::GetContentRegionAvail().x, 0))) { /* do nothing */ }
            });

            ImGui::EndTable();
        }
    }
}
