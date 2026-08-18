#pragma once
#include "../Interfaces/IPanel.h"

namespace UI
{
    class SettingsPanel : public IPanel
    {
    public:
        void Render() override;
    };
}
