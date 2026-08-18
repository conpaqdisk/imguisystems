#pragma once

namespace UI
{
    class ThemeManager
    {
    public:
        static void ApplyTheme(int themeIndex);
        static void InitializeFonts(float scale = 1.0f);

    private:
        static void ApplyDark();
        static void ApplyMidnight();
        static void ApplyBlue();
        static void ApplyBaseStyle();
        static void ApplyGray();
        static void ApplyPurple();
        static void ApplyGreen();
    };
}
