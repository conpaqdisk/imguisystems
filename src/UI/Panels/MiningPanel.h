#pragma once
#include "../Interfaces/IPanel.h"

namespace UI
{
    class MiningPanel : public IPanel
    {
    public:
        void Render() override;
    };
}
