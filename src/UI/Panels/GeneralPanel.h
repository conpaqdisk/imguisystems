#pragma once
#include "../Interfaces/IPanel.h"

namespace UI
{
    class GeneralPanel : public IPanel
    {
    public:
        GeneralPanel() = default;
        ~GeneralPanel() override = default;

        void Render() override;
    };
}
