#pragma once
#include "../Interfaces/IPanel.h"

namespace UI
{
    class UpgradePanel : public IPanel
    {
    public:
        void Render() override;
    };
}
