#pragma once
#include "../../Interfaces/IPanel.h"

namespace UI
{
    class PriestPanel : public IPanel
    {
    public:
        void Render() override;
    };
}
