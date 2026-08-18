#include "ChatPanel.h"
#include <imgui.h>
#include "../../Core/AppState.h"
#include "../Core/UIComponents.h"

namespace UI
{
    void ChatPanel::Render()
    {
        Components::DrawPageTitle("Chat & Mesajlasma", "Oto mesaj, flood ve filtre ayarları");

        if (ImGui::BeginTable("ChatGrid", 2, ImGuiTableFlags_PadOuterX))
        {
            ImGui::TableNextRow();

            // SOL SUTUN
            ImGui::TableSetColumnIndex(0);
            
            Components::DrawCard("FloodCard", "OTO MESAJ (FLOOD)", [&]()
            {
                static bool floodActive = false;
                static int floodInterval = 5000;
                static int currentChannel = 0;
                const char* channels[] = { "All Chat", "Party", "Clan" };

                ImGui::Checkbox("Flood Aktif", &floodActive);
                ImGui::Combo("Kanal", &currentChannel, channels, 3);
                ImGui::SliderInt("Aralik (ms)", &floodInterval, 1000, 30000);
                
                ImGui::Separator();
                
                static char floodMsg[128] = "";
                ImGui::InputTextMultiline("Mesaj##Flood", floodMsg, IM_ARRAYSIZE(floodMsg), ImVec2(-1, 80));
            });

            // SAG SUTUN
            ImGui::TableSetColumnIndex(1);
            
            Components::DrawCard("KeywordCard", "ANAHTAR KELIME YANIT", [&]()
            {
                static char keyword[64] = "";
                static char replyMsg[128] = "";

                ImGui::InputText("Kelime", keyword, IM_ARRAYSIZE(keyword));
                ImGui::InputText("Yanit", replyMsg, IM_ARRAYSIZE(replyMsg));
                
                if (ImGui::Button("Ekle", ImVec2(-1, 0))) { /* do nothing */ }
                
                ImGui::Separator();
                
                if (ImGui::BeginTable("KeywordTable", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
                {
                    ImGui::TableSetupColumn("Kelime", ImGuiTableColumnFlags_WidthFixed, 60.0f);
                    ImGui::TableSetupColumn("Yanit", ImGuiTableColumnFlags_WidthStretch);
                    ImGui::TableSetupColumn("Islem", ImGuiTableColumnFlags_WidthFixed, 50.0f);
                    ImGui::TableHeadersRow();

                    // Placeholder row
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::Text("selam");
                    ImGui::TableSetColumnIndex(1); ImGui::Text("as bot kardes");
                    ImGui::TableSetColumnIndex(2); ImGui::Button("Sil");

                    ImGui::EndTable();
                }
            });

            ImGui::EndTable();
        }
    }
}
