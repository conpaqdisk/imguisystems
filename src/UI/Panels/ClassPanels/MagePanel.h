#pragma once
#include "../../Interfaces/IPanel.h"

namespace UI
{
    class MagePanel : public IPanel
    {
    public:
        void Render() override;
    };
}
