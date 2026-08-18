#include "UIComponents.h"
#include <imgui.h>
#include <imgui_internal.h>
#include <math.h>
#include <d3d11.h>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

extern ID3D11Device* g_pd3dDevice;

namespace UI
{
    namespace Components
    {
        void DrawPageTitle(const char* title, const char* description)
        {
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]); 
            ImGui::TextUnformatted(title);
            ImGui::PopFont();
            if (description && description[0] != '\0')
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_TextDisabled]);
                ImGui::TextWrapped("%s", description);
                ImGui::PopStyleColor();
            }
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();
        }

        void DrawSectionHeader(const char* title)
        {
            ImGui::Spacing();
            ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
            ImGui::TextUnformatted(title);
            ImGui::PopStyleColor();
            ImGui::Separator();
            ImGui::Spacing();
        }

        void DrawTooltip(const char* text)
        {
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
            {
                ImGui::BeginTooltip();
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                ImGui::TextUnformatted(text);
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }
        }

        bool DrawToggle(const char* label, bool* v)
        {
            ImVec2 p = ImGui::GetCursorScreenPos();
            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            float height = ImGui::GetFrameHeight();
            float width = height * 1.55f;
            float radius = height * 0.5f;

            ImGui::InvisibleButton(label, ImVec2(width, height));
            bool changed = false;
            if (ImGui::IsItemClicked())
            {
                *v = !*v;
                changed = true;
            }

            ImGuiContext& g = *GImGui;
            float t = *v ? 1.0f : 0.0f;
            float ANIM_SPEED = 0.08f;
            if (g.LastActiveId == g.CurrentWindow->GetID(label))
            {
                float t_anim = ImGui::GetStateStorage()->GetFloat(ImGui::GetID(label), t);
                t_anim = t_anim + (t - t_anim) * ANIM_SPEED;
                ImGui::GetStateStorage()->SetFloat(ImGui::GetID(label), t_anim);
                t = t_anim;
            }

            ImU32 col_bg;
            if (ImGui::IsItemHovered())
                col_bg = ImGui::GetColorU32(*v ? ImGuiCol_ButtonActive : ImGuiCol_ButtonHovered);
            else
                col_bg = ImGui::GetColorU32(*v ? ImGuiCol_ButtonActive : ImGuiCol_FrameBg);

            draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
            draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));

            ImGui::SameLine();
            ImGui::TextUnformatted(label);
            return changed;
        }

        void DrawCard(const char* id, const char* title, const std::function<void()>& content)
        {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyle().Colors[ImGuiCol_FrameBg]);
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 6.0f);
            
            ImGui::BeginChild(id, ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysAutoResize);
            if (title && title[0] != '\0')
            {
                ImGui::TextDisabled("%s", title);
                ImGui::Separator();
                ImGui::Spacing();
            }
            content();
            ImGui::EndChild();
            ImGui::PopStyleVar();
            ImGui::PopStyleColor();
        }

        void DrawKeyValue(const char* key, const char* value)
        {
            ImGui::TextDisabled("%s", key);
            ImGui::SameLine(ImGui::GetWindowWidth() * 0.5f);
            ImGui::TextUnformatted(value);
        }

        void DrawStatusIndicator(const char* label, Core::AppStatus status)
        {
            ImVec4 color;
            switch (status)
            {
                case Core::AppStatus::Ready:   color = ImVec4(0.2f, 0.8f, 0.2f, 1.0f); break;
                case Core::AppStatus::Running: color = ImVec4(0.2f, 0.6f, 1.0f, 1.0f); break;
                case Core::AppStatus::Paused:  color = ImVec4(0.8f, 0.8f, 0.2f, 1.0f); break;
                case Core::AppStatus::Error:   color = ImVec4(0.9f, 0.2f, 0.2f, 1.0f); break;
                default:                       color = ImVec4(0.5f, 0.5f, 0.5f, 1.0f); break;
            }

            ImVec2 p = ImGui::GetCursorScreenPos();
            float size = ImGui::GetTextLineHeight() * 0.5f;
            ImGui::GetWindowDrawList()->AddCircleFilled(ImVec2(p.x + size, p.y + size), size, ImGui::GetColorU32(color));
            
            ImGui::Dummy(ImVec2(size * 2.5f, 0));
            ImGui::SameLine();
            ImGui::TextUnformatted(label);
        }

        void DrawBadge(const char* text, const ImVec4& color)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, color);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, color);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, color);
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
            
            ImGui::Button(text); 
            ImGui::PopStyleColor(4);
        }

        bool Spinner(const char* label, float radius, int thickness, const ImU32& color) {
            ImGuiWindow* window = ImGui::GetCurrentWindow();
            if (window->SkipItems)
                return false;
            
            ImGuiContext& g = *GImGui;
            const ImGuiStyle& style = g.Style;
            const ImGuiID id = window->GetID(label);
            
            ImVec2 pos = window->DC.CursorPos;
            ImVec2 size((radius )*2, (radius + style.FramePadding.y)*2);
            
            const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
            ImGui::ItemSize(bb, style.FramePadding.y);
            if (!ImGui::ItemAdd(bb, id))
                return false;
            
            window->DrawList->PathClear();
            
            int num_segments = 30;
            int start = (int)abs(ImSin(g.Time*1.8f)*(num_segments-5));
            
            const float a_min = IM_PI*2.0f * ((float)start) / (float)num_segments;
            const float a_max = IM_PI*2.0f * ((float)num_segments-3) / (float)num_segments;
            const ImVec2 centre = ImVec2(pos.x+radius, pos.y+radius+style.FramePadding.y);
            
            for (int i = 0; i < num_segments; i++) {
                const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
                window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(a+g.Time*8) * radius,
                                                    centre.y + ImSin(a+g.Time*8) * radius));
            }
            window->DrawList->PathStroke(color, ImDrawFlags_None, (float)thickness);
            
            return true;
        }

        bool DrawInputInt(const char* label, int* v, int step, int step_fast)
        {
            return ImGui::InputInt(label, v, step, step_fast);
        }

        bool DrawInputText(const char* label, std::string* str)
        {
            char buffer[256];
            strncpy_s(buffer, str->c_str(), sizeof(buffer));
            buffer[sizeof(buffer) - 1] = 0;
            if (ImGui::InputText(label, buffer, sizeof(buffer)))
            {
                *str = buffer;
                return true;
            }
            return false;
        }

        bool DrawCombo(const char* label, int* current_item, const char* const items[], int items_count)
        {
            return ImGui::Combo(label, current_item, items, items_count);
        }

        bool DrawSliderInt(const char* label, int* v, int v_min, int v_max)
        {
            ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.2f, 0.3f, 0.5f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.3f, 0.4f, 0.6f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.4f, 0.5f, 0.7f, 1.0f));
            bool changed = ImGui::SliderInt(label, v, v_min, v_max, "%d %%", ImGuiSliderFlags_AlwaysClamp);
            ImGui::PopStyleColor(3);
            return changed;
        }

        bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
        {
            if (!g_pd3dDevice) return false;

            // Load from disk into a raw RGBA buffer
            int image_width = 0;
            int image_height = 0;
            unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
            if (image_data == NULL)
                return false;

            // Create texture
            D3D11_TEXTURE2D_DESC desc;
            ZeroMemory(&desc, sizeof(desc));
            desc.Width = image_width;
            desc.Height = image_height;
            desc.MipLevels = 1;
            desc.ArraySize = 1;
            desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            desc.SampleDesc.Count = 1;
            desc.Usage = D3D11_USAGE_DEFAULT;
            desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            desc.CPUAccessFlags = 0;

            ID3D11Texture2D* pTexture = NULL;
            D3D11_SUBRESOURCE_DATA subResource;
            subResource.pSysMem = image_data;
            subResource.SysMemPitch = desc.Width * 4;
            subResource.SysMemSlicePitch = 0;
            g_pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

            // Create texture view
            D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
            ZeroMemory(&srvDesc, sizeof(srvDesc));
            srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
            srvDesc.Texture2D.MipLevels = desc.MipLevels;
            srvDesc.Texture2D.MostDetailedMip = 0;
            g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
            pTexture->Release();

            *out_width = image_width;
            *out_height = image_height;
            stbi_image_free(image_data);

            return true;
        }
    }
}
