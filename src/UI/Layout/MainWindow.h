#pragma once
#include <memory>
#include <map>
#include "../Interfaces/IPanel.h"

namespace UI
{
    enum class ActiveTab
    {
        Dashboard, General, Combat, Warrior, Rogue, Mage, Priest, 
        MobManager, Party, Chat, Inventory, Supply, Upgrade, Mining, Fishing, 
        Timers, Automation, Logs, Settings, ImGuiDemo
    };

    class MainWindow
    {
    public:
        MainWindow();
        ~MainWindow() = default;

        void Render();

    private:
        void RenderTopBar();
        void RenderNavigationBar();
        void RenderContent();

        bool DrawSidebarButton(const char* label, ActiveTab tab);

    private:
        ActiveTab m_CurrentTab;
        std::map<ActiveTab, std::unique_ptr<IPanel>> m_Panels;
    };
}
