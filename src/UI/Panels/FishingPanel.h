#pragma once
#include "../Interfaces/IPanel.h"

namespace UI
{
    class FishingPanel : public IPanel
    {
    public:
        void Render() override;
    };
}
