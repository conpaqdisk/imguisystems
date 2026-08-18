#pragma once
#include "../Interfaces/IPanel.h"

namespace UI
{
    class InventoryPanel : public IPanel
    {
    public:
        void Render() override;
    };
}
