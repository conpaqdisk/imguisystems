#pragma once
#include "../Interfaces/IPanel.h"

namespace UI
{
    class TimersPanel : public IPanel
    {
    public:
        void Render() override;
    };
}
