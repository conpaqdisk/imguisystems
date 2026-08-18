#pragma once
#include "../Interfaces/IPanel.h"

namespace UI
{
    class DashboardPanel : public IPanel
    {
    public:
        DashboardPanel() = default;
        ~DashboardPanel() override = default;

        void Render() override;
    };
}
