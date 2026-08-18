#pragma once
#include "../Interfaces/IPanel.h"

namespace UI
{
    class SupplyPanel : public IPanel
    {
    public:
        void Render() override;
    };
}
