#pragma once

namespace UI
{
    class IPanel
    {
    public:
        virtual ~IPanel() = default;
        virtual void Render() = 0;
    };
}
