#pragma once
#include "../Interfaces/IPanel.h"

namespace UI
{
    class AutomationPanel : public IPanel
    {
    public:
        void Render() override;
    };
}
