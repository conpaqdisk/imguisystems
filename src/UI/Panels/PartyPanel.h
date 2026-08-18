#pragma once
#include "../Interfaces/IPanel.h"

namespace UI
{
    class PartyPanel : public IPanel
    {
    public:
        void Render() override;
    };
}
