#pragma once
#include "../Interfaces/IPanel.h"

namespace UI
{
    class DemoPanel : public IPanel
    {
    public:
        void Render() override;
    };
}
