#include "DashboardPanel.h"
#include <imgui.h>
#include "../../Core/AppState.h"
#include "../Core/UIComponents.h"
#include <implot.h>

struct ScrollingBuffer {
    int MaxSize;
    int Offset;
    ImVector<ImVec2> Data;
    ScrollingBuffer(int max_size = 2000) {
        MaxSize = max_size;
        Offset  = 0;
        Data.reserve(MaxSize);
    }
    void AddPoint(float x, float y) {
        if (Data.size() < MaxSize)
            Data.push_back(ImVec2(x,y));
        else {
            Data[Offset] = ImVec2(x,y);
            Offset =  (Offset + 1) % MaxSize;
        }
    }
    void Erase() {
        if (Data.size() > 0) {
            Data.shrink(0);
            Offset  = 0;
        }
    }
};

namespace UI
{
    void DashboardPanel::Render()
    {
        Components::DrawPageTitle("Dashboard", "Sistem durumu ve aktif islemler");
        auto& state = Core::AppState::Get();

        if (ImGui::BeginTable("DashboardGrid", 2, ImGuiTableFlags_PadOuterX))
        {
            ImGui::TableNextRow();

            // SOL SUTUN
            ImGui::TableSetColumnIndex(0);
            
            Components::DrawCard("CharCard", "KARAKTER DURUMU", [&]()
            {
                Components::DrawKeyValue("Karakter Adi", state.CharacterName.c_str());
                Components::DrawKeyValue("Seviye", std::to_string(state.Level).c_str());

                std::string hpStr = std::to_string(state.CurrentHP) + " / " + std::to_string(state.MaxHP);
                Components::DrawKeyValue("HP", hpStr.c_str());
                
                float hpRatio = (state.MaxHP > 0) ? (float)state.CurrentHP / state.MaxHP : 0.0f;
                ImGui::ProgressBar(hpRatio, ImVec2(-1.0f, 4.0f), "");

                std::string mpStr = std::to_string(state.CurrentMP) + " / " + std::to_string(state.MaxMP);
                Components::DrawKeyValue("MP", mpStr.c_str());

                float mpRatio = (state.MaxMP > 0) ? (float)state.CurrentMP / state.MaxMP : 0.0f;
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.2f, 0.4f, 0.8f, 1.0f));
                ImGui::ProgressBar(mpRatio, ImVec2(-1.0f, 4.0f), "");
                ImGui::PopStyleColor();

                ImGui::Spacing();
                std::string posStr = "X: " + std::to_string((int)state.PosX) + " Y: " + std::to_string((int)state.PosY);
                Components::DrawKeyValue("Konum", posStr.c_str());
            });

            ImGui::Spacing();
            
            Components::DrawCard("CombatCard", "SAVAS SISTEMI", [&]()
            {
                Components::DrawKeyValue("Saldiri Durumu", state.Combat.attackActive ? "Aktif" : "Pasif");
                Components::DrawKeyValue("Hedef Secimi", state.Combat.autoSelectTarget ? "Otomatik" : "Manuel");
                Components::DrawKeyValue("KS Modu", state.Combat.ksMode ? "Aktif" : "Kapali");

                ImGui::Separator();
                ImGui::TextDisabled("Aktif Yetenekler:");
                if (state.Combat.activeSkills.empty())
                {
                    ImGui::Text("Atak listesi bos.");
                }
                else
                {
                    for (const auto& skill : state.Combat.activeSkills)
                    {
                        ImGui::BulletText("%s", skill.name.c_str());
                    }
                }
            });

            // SAG SUTUN
            ImGui::TableSetColumnIndex(1);
            
            Components::DrawCard("SystemCard", "SISTEM OZETI", [&]()
            {
                Components::DrawKeyValue("Aktif Profil", state.ProfileName.c_str());
                Components::DrawKeyValue("Calisma Suresi", (std::to_string(state.UptimeSeconds) + " saniye").c_str());
                Components::DrawKeyValue("RPR Durumu", state.Inventory.rprActive ? "Aktif" : "Pasif");
                Components::DrawKeyValue("Maden/Balik", (state.Farming.miningActive || state.Farming.fishingActive) ? "Aktif" : "Pasif");

                ImGui::Separator();

                if (ImGui::Button("Sistemi Baslat", ImVec2(ImGui::GetContentRegionAvail().x * 0.48f, 30.0f)))
                {
                    state.CurrentStatus = Core::AppStatus::Running;
                    state.Combat.attackActive = true;
                }
                ImGui::SameLine();
                if (ImGui::Button("Durdur", ImVec2(ImGui::GetContentRegionAvail().x, 30.0f)))
                {
                    state.CurrentStatus = Core::AppStatus::Paused;
                    state.Combat.attackActive = false;
                }
            });

            ImGui::Spacing();
            
            Components::DrawCard("PerfGraph", "SISTEM PERFORMANSI", [&]()
            {
                static ScrollingBuffer fpsBuffer;
                static float t = 0;
                t += ImGui::GetIO().DeltaTime;
                fpsBuffer.AddPoint(t, ImGui::GetIO().Framerate);

                if (ImPlot::BeginPlot("##FpsPlot", ImVec2(-1, 150))) {
                    ImPlot::SetupAxes("Zaman (s)", "FPS", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
                    ImPlot::SetupAxisLimits(ImAxis_X1, t - 10.0f, t, ImGuiCond_Always);
                    ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 150);
                    ImPlot::PlotLine("FPS", &fpsBuffer.Data[0].x, &fpsBuffer.Data[0].y, fpsBuffer.Data.size(), {ImPlotProp_Offset, fpsBuffer.Offset, ImPlotProp_Stride, sizeof(ImVec2)});
                    ImPlot::EndPlot();
                }
            });

            ImGui::EndTable();
        }
    }
}
