#include "MainWindow.h"
#include <imgui.h>
#include <ctime>
#include "../../Core/AppState.h"
#include "../Core/UIComponents.h"

#include "../Panels/DashboardPanel.h"
#include "../Panels/GeneralPanel.h"
#include "../Panels/CombatPanel.h"
#include "../Panels/ClassPanels/WarriorPanel.h"
#include "../Panels/ClassPanels/RoguePanel.h"
#include "../Panels/ClassPanels/MagePanel.h"
#include "../Panels/ClassPanels/PriestPanel.h"
#include "../Panels/PartyPanel.h"
#include "../Panels/InventoryPanel.h"
#include "../Panels/SupplyPanel.h"
#include "../Panels/MiningPanel.h"
#include "../Panels/FishingPanel.h"
#include "../Panels/ChatPanel.h"
#include "../Panels/MobPanel.h"
#include "../Panels/UpgradePanel.h"
#include "../Panels/TimersPanel.h"
#include "../Panels/AutomationPanel.h"
#include "../Panels/LogPanel.h"
#include "../Panels/SettingsPanel.h"
#include "../Panels/DemoPanel.h"

namespace UI
{
    MainWindow::MainWindow()
    {
        m_CurrentTab = ActiveTab::Dashboard;
        
        m_Panels[ActiveTab::Dashboard] = std::make_unique<DashboardPanel>();
        m_Panels[ActiveTab::General] = std::make_unique<GeneralPanel>();
        m_Panels[ActiveTab::Combat] = std::make_unique<CombatPanel>();
        m_Panels[ActiveTab::Warrior] = std::make_unique<WarriorPanel>();
        m_Panels[ActiveTab::Rogue] = std::make_unique<RoguePanel>();
        m_Panels[ActiveTab::Mage] = std::make_unique<MagePanel>();
        m_Panels[ActiveTab::Priest] = std::make_unique<PriestPanel>();
        m_Panels[ActiveTab::Party] = std::make_unique<PartyPanel>();
        m_Panels[ActiveTab::Inventory] = std::make_unique<InventoryPanel>();
        m_Panels[ActiveTab::Supply] = std::make_unique<SupplyPanel>();
        m_Panels[ActiveTab::Mining] = std::make_unique<MiningPanel>();
        m_Panels[ActiveTab::Fishing] = std::make_unique<FishingPanel>();
        m_Panels[ActiveTab::Chat] = std::make_unique<ChatPanel>();
        m_Panels[ActiveTab::MobManager] = std::make_unique<MobPanel>();
        m_Panels[ActiveTab::Upgrade] = std::make_unique<UpgradePanel>();
        m_Panels[ActiveTab::Timers] = std::make_unique<TimersPanel>();
        m_Panels[ActiveTab::Automation] = std::make_unique<AutomationPanel>();
        m_Panels[ActiveTab::Logs] = std::make_unique<LogPanel>();
        m_Panels[ActiveTab::Settings] = std::make_unique<SettingsPanel>();
        m_Panels[ActiveTab::ImGuiDemo] = std::make_unique<DemoPanel>();
    }

    void MainWindow::Render()
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
                                       ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                                       ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus |
                                       ImGuiWindowFlags_NoNavFocus;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        ImGui::Begin("MainWorkspace", nullptr, windowFlags);
        ImGui::PopStyleVar(2);

        RenderTopBar();
        ImGui::Separator();

        // 1. TopBar is full width
        RenderTopBar();
        ImGui::Separator();

        // 2. Navigation Bar (former sidebar) is full width, below TopBar
        RenderNavigationBar();
        ImGui::Separator();

        // 3. Content Region takes the rest of the space
        ImGui::BeginChild("ContentRegion", ImVec2(0, 0), false);
        
        RenderContent();
        ImGui::EndChild();

        ImGui::End();
    }

    void MainWindow::RenderTopBar()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
        if (ImGui::BeginChild("TopBar", ImVec2(0, 45), false, ImGuiWindowFlags_NoScrollbar))
        {
            static ID3D11ShaderResourceView* texFlag = nullptr;
            static ID3D11ShaderResourceView* texWolf = nullptr;
            static ID3D11ShaderResourceView* texSig = nullptr;
            static int tw=0, th=0;
            static bool loaded = false;
            if (!loaded)
            {
                Components::LoadTextureFromFile("assets/flag.jpg", &texFlag, &tw, &th);
                Components::LoadTextureFromFile("assets/wolf.jpg", &texWolf, &tw, &th);
                Components::LoadTextureFromFile("assets/signature.jpg", &texSig, &tw, &th);
                loaded = true;
            }

            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.0f);
            ImGui::SetCursorPosX(15.0f);

            if (texFlag) { ImGui::Image((void*)texFlag, ImVec2(30, 20)); ImGui::SameLine(); }
            if (texWolf) { ImGui::Image((void*)texWolf, ImVec2(25, 25)); ImGui::SameLine(); }

            // [steellbox]
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 6.0f);
            ImGui::BeginGroup();
            ImGui::TextColored(ImVec4(1.0f, 0.6f, 0.2f, 1.0f), "STEEL");
            ImGui::SameLine(0, 0);
            ImGui::TextUnformatted("BOT");
            ImGui::EndGroup();

            ImGui::SameLine(0, 20.0f);

            // [Atak Baslat]
            Core::AppStatus currentStatus = Core::AppState::Get().CurrentStatus;
            auto& state = Core::AppState::Get();

            ImGui::SetCursorPosY(7.5f);
            if (currentStatus == Core::AppStatus::Running) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.3f, 0.3f, 1.0f));
                if (ImGui::Button("Atak Durdur", ImVec2(100, 30))) {
                    state.CurrentStatus = Core::AppStatus::Ready;
                }
                ImGui::PopStyleColor(2);
            } else {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.6f, 0.2f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.7f, 0.3f, 1.0f));
                if (ImGui::Button("Atak Baslat", ImVec2(100, 30))) {
                    state.CurrentStatus = Core::AppStatus::Running;
                }
                ImGui::PopStyleColor(2);
            }

            ImGui::SameLine(0, 20.0f);

            // [hazir]
            ImGui::SetCursorPosY(15.0f);
            const char* statusText = (currentStatus == Core::AppStatus::Running) ? "Calisiyor" :
                                     (currentStatus == Core::AppStatus::Ready) ? "Hazir" :
                                     (currentStatus == Core::AppStatus::Error) ? "Hata" : "Durduruldu";
            if (currentStatus == Core::AppStatus::Running) {
                Components::Spinner("##status_spin", 6.0f, 2, ImGui::GetColorU32(ImVec4(0.2f, 0.8f, 0.2f, 1.0f)));
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(0.2f, 0.8f, 0.2f, 1.0f), "Calisiyor");
            } else {
                Components::DrawStatusIndicator(statusText, currentStatus);
            }

            // Sag tarafa FPS, Saat ve Imza yerlestir
            time_t now = time(0);
            tm* ltm = localtime(&now);
            char timeBuf[64];
            strftime(timeBuf, sizeof(timeBuf), "%H:%M:%S - %d/%m/%Y", ltm);

            std::string perfText = "FPS: " + std::to_string(static_cast<int>(ImGui::GetIO().Framerate));
            
            float infoWidth = ImGui::CalcTextSize(timeBuf).x;
            float sigWidth = texSig ? 160.0f : 0.0f;
            float rightAlign = ImGui::GetWindowWidth() - infoWidth - sigWidth - 20.0f;
            
            ImGui::SameLine(rightAlign);
            ImGui::SetCursorPosY(7.5f);
            
            ImGui::BeginGroup();
            ImGui::TextDisabled("%s", perfText.c_str());
            ImGui::TextDisabled("%s", timeBuf);
            ImGui::EndGroup();

            if (texSig) {
                ImGui::SameLine();
                ImGui::SetCursorPosY(5.0f);
                ImGui::Image((void*)texSig, ImVec2(150, 30));
            }
        }
        ImGui::EndChild();
        ImGui::PopStyleVar();
    }

    bool MainWindow::DrawSidebarButton(const char* label, ActiveTab tab)
    {
        bool isSelected = (m_CurrentTab == tab);
        if (isSelected)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
        }
        else
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        }

        ImVec2 size = ImVec2(ImGui::GetContentRegionAvail().x, 30.0f);
        bool clicked = ImGui::Button(label, size);
        ImGui::PopStyleColor();

        if (clicked)
        {
            m_CurrentTab = tab;
        }

        return clicked;
    }

    void MainWindow::RenderNavigationBar()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5, 5));
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyle().Colors[ImGuiCol_WindowBg]);
        
        if (ImGui::BeginChild("NavigationContent", ImVec2(0, 45), false, ImGuiWindowFlags_NoScrollbar))
        {
            ImGui::SetCursorPosY(7.5f); // Center vertically
            ImGui::SetCursorPosX(15.0f);
            
            // We use inline drawing instead of full width buttons
            auto drawNavBtn = [&](const char* label, ActiveTab tab) {
                bool isSelected = (m_CurrentTab == tab);
                if (isSelected) {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
                } else {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
                }
                if (ImGui::Button(label, ImVec2(0, 30))) {
                    m_CurrentTab = tab;
                }
                ImGui::PopStyleColor();
                ImGui::SameLine();
            };

            // Gorsellerdeki gibi sade bir sekme siralamasi:
            drawNavBtn("Genel & Atak", ActiveTab::General);
            drawNavBtn("Warrior", ActiveTab::Warrior);
            drawNavBtn("Rogue", ActiveTab::Rogue);
            drawNavBtn("Mage", ActiveTab::Mage);
            drawNavBtn("Priest", ActiveTab::Priest);
            drawNavBtn("Party", ActiveTab::Party);
            drawNavBtn("Chat", ActiveTab::Chat);
            drawNavBtn("Envanter", ActiveTab::Inventory);
            drawNavBtn("Tedarik", ActiveTab::Supply);
            drawNavBtn("Upgrade", ActiveTab::Upgrade);
            drawNavBtn("Maden", ActiveTab::Mining);
            drawNavBtn("Balik", ActiveTab::Fishing);
            drawNavBtn("Mob Ynt.", ActiveTab::MobManager);
            drawNavBtn("Ekstra", ActiveTab::Automation);
            drawNavBtn("Ayarlar", ActiveTab::Settings);
            drawNavBtn("Log", ActiveTab::Logs);
        }
        ImGui::EndChild();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
    }

    void MainWindow::RenderContent()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(15.0f, 15.0f));
        if (ImGui::BeginChild("MainContentArea", ImVec2(0, 0), false, ImGuiWindowFlags_None))
        {
            auto it = m_Panels.find(m_CurrentTab);
            if (it != m_Panels.end() && it->second)
            {
                it->second->Render();
            }
            else
            {
                ImGui::TextDisabled("Bu modul henuz yapilandirilmadi.");
            }
        }
        ImGui::EndChild();
        ImGui::PopStyleVar();
    }
}
