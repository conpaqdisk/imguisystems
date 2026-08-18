#pragma once
#include "../Interfaces/IPanel.h"

namespace UI
{
    class CombatPanel : public IPanel
    {
    public:
        CombatPanel() = default;
        ~CombatPanel() override = default;

        void Render() override;

    private:
        void RenderSkillListTable();
    };
}
