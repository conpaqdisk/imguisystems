#include "TimersPanel.h"
#include <imgui.h>
#include "../../Core/AppState.h"
#include "../Core/UIComponents.h"

namespace UI
{
    void TimersPanel::Render()
    {
        Components::DrawPageTitle("Zamanlayicilar (Timers)", "Belirli surelerde yapilacak islemler");
        auto& state = Core::AppState::Get();

        if (ImGui::BeginTable("TimersGrid", 2, ImGuiTableFlags_PadOuterX))
        {
            ImGui::TableNextRow();

            // SOL SUTUN
            ImGui::TableSetColumnIndex(0);
            
            Components::DrawCard("TimerSettings", "YENI ZAMANLAYICI", [&]()
            {
                static char timerName[64] = "";
                static int timerInterval = 60;
                static int timerAction = 0;
                const char* actions[] = { "Botu Durdur", "Town At", "Clienti Kapat", "Skill Bas" };

                ImGui::InputText("Zamanlayici Adi", timerName, IM_ARRAYSIZE(timerName));
                ImGui::InputInt("Sure (Saniye)", &timerInterval, 10, 60);
                ImGui::Combo("Islem", &timerAction, actions, 4);
                
                ImGui::Spacing();
                
                if (ImGui::Button("Ekle", ImVec2(-1, 0))) { /* placeholder */ }
            });

            // SAG SUTUN
            ImGui::TableSetColumnIndex(1);
            
            Components::DrawCard("TimerList", "AKTIF ZAMANLAYICILAR", [&]()
            {
                if (ImGui::BeginTable("TimerTable", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
                {
                    ImGui::TableSetupColumn("Durum", ImGuiTableColumnFlags_WidthFixed, 40.0f);
                    ImGui::TableSetupColumn("Ad", ImGuiTableColumnFlags_WidthStretch);
                    ImGui::TableSetupColumn("Kalan", ImGuiTableColumnFlags_WidthFixed, 60.0f);
                    ImGui::TableSetupColumn("Islem", ImGuiTableColumnFlags_WidthFixed, 50.0f);
                    ImGui::TableHeadersRow();

                    // Placeholder rows
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); 
                    static bool t1 = true; ImGui::Checkbox("##t1", &t1);
                    ImGui::TableSetColumnIndex(1); ImGui::Text("Genie Bitiyor");
                    ImGui::TableSetColumnIndex(2); ImGui::Text("45s");
                    ImGui::TableSetColumnIndex(3); ImGui::Button("Sil##t1");

                    ImGui::EndTable();
                }
            });

            ImGui::EndTable();
        }
    }
}
