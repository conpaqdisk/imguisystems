#pragma once
#include <string>
#include <functional>
#include <imgui.h>
#include "../../Core/AppState.h"
#include <d3d11.h>

namespace UI
{
    namespace Components
    {
        // Simple texture loading
        bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);

        void DrawPageTitle(const char* title, const char* description);
        void DrawSectionHeader(const char* title);
        void DrawTooltip(const char* text);
        bool DrawToggle(const char* label, bool* v);
        void DrawCard(const char* id, const char* title, const std::function<void()>& content);
        void DrawKeyValue(const char* key, const char* value);
        void DrawStatusIndicator(const char* label, Core::AppStatus status);
        void DrawBadge(const char* text, const ImVec4& color);
        bool Spinner(const char* label, float radius, int thickness, const ImU32& color);
        
        bool DrawInputInt(const char* label, int* v, int step = 1, int step_fast = 100);
        bool DrawInputText(const char* label, std::string* str);
        bool DrawCombo(const char* label, int* current_item, const char* const items[], int items_count);
        bool DrawSliderInt(const char* label, int* v, int v_min, int v_max);
    }
}
