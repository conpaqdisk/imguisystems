#pragma once
#include "../Interfaces/IPanel.h"

namespace UI
{
    class ChatPanel : public IPanel
    {
    public:
        void Render() override;
    };
}
