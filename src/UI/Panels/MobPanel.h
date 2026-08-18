#pragma once
#include "../Interfaces/IPanel.h"

namespace UI
{
    class MobPanel : public IPanel
    {
    public:
        void Render() override;
    };
}
