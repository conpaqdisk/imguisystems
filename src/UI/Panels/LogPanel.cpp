#include "LogPanel.h"
#include <imgui.h>
#include "../../Core/AppState.h"
#include "../Core/UIComponents.h"

namespace UI
{
    void LogPanel::Render()
    {
        Components::DrawPageTitle("Log Kayitlari", "Sistem, saldiri ve hata kayitlari");

        Components::DrawCard("LogViewer", "SISTEM KAYITLARI", [&]()
        {
            if (ImGui::Button("Temizle")) { /* clear logs */ }
            ImGui::SameLine();
            static bool autoscroll = true;
            ImGui::Checkbox("Oto Kaydir", &autoscroll);
            ImGui::SameLine();
            static char filter[64] = "";
            ImGui::InputText("Filtrele", filter, IM_ARRAYSIZE(filter));
            
            ImGui::Separator();
            
            ImGui::BeginChild("LogRegion", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
            
            ImGui::TextUnformatted("[12:00:00] [INFO] Sistem baslatildi.");
            ImGui::TextUnformatted("[12:00:05] [COMBAT] Saldiri sistemi aktif.");
            ImGui::TextColored(ImVec4(1.0f, 0.4f, 0.4f, 1.0f), "[12:00:10] [ERROR] Hedef bulunamadi!");
            ImGui::TextUnformatted("[12:00:15] [SYSTEM] RPR rotasina geciliyor.");
            
            if (autoscroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                ImGui::SetScrollHereY(1.0f);
                
            ImGui::EndChild();
        });
    }
}
