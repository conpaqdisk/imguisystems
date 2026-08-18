#pragma once
#include "../../Interfaces/IPanel.h"

namespace UI
{
    class WarriorPanel : public IPanel
    {
    public:
        WarriorPanel() = default;
        ~WarriorPanel() override = default;

        void Render() override;
    };
}
