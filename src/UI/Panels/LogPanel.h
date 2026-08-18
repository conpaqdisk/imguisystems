#pragma once
#include "../Interfaces/IPanel.h"

namespace UI
{
    class LogPanel : public IPanel
    {
    public:
        void Render() override;
    private:
        bool showInfo = true;
        bool showSuccess = true;
        bool showWarning = true;
        bool showError = true;
        bool autoScroll = true;
    };
}
