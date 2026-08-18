#pragma once
#include "../../Interfaces/IPanel.h"

namespace UI
{
    class RoguePanel : public IPanel
    {
    public:
        void Render() override;
    };
}
