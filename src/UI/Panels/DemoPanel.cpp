#include "DemoPanel.h"
#include <imgui.h>
#include "../Core/UIComponents.h"

namespace UI
{
    void DemoPanel::Render()
    {
        Components::DrawPageTitle("Dear ImGui Demo (Gomulu)", "ImGui bilesenlerinin arayuz icine gomulmus hali.");

        if (ImGui::BeginTable("DemoGrid", 2, ImGuiTableFlags_PadOuterX))
        {
            ImGui::TableNextRow();

            // SOL SUTUN
            ImGui::TableSetColumnIndex(0);
            
            Components::DrawCard("BasicWidgets", "TEMEL BILESENLER", [&]()
            {
                static bool b1 = false, b2 = true;
                ImGui::Checkbox("Onay Kutusu 1", &b1);
                ImGui::Checkbox("Onay Kutusu 2", &b2);

                static int i1 = 50;
                ImGui::SliderInt("Kaydirici (Slider)", &i1, 0, 100);

                static float f1 = 0.5f;
                ImGui::SliderFloat("Float Kaydirici", &f1, 0.0f, 1.0f);

                static int combo_item = 0;
                const char* items[] = { "Elma", "Armut", "Muz", "Cilek" };
                ImGui::Combo("Secim (Combo)", &combo_item, items, IM_ARRAYSIZE(items));

                if (ImGui::Button("Ornek Buton")) {
                    // Do nothing
                }
            });

            ImGui::Spacing();

            Components::DrawCard("TextWidgets", "METIN BILESENLERI", [&]()
            {
                ImGui::Text("Standart Metin");
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Renkli Metin (Pembe)");
                ImGui::TextDisabled("Pasif (Disabled) Metin");
                ImGui::BulletText("Madde imli metin");
            });

            // SAG SUTUN
            ImGui::TableSetColumnIndex(1);
            
            Components::DrawCard("ColorWidgets", "RENK BILESENLERI", [&]()
            {
                static float col1[3] = { 1.0f, 0.0f, 0.2f };
                static float col2[4] = { 0.4f, 0.7f, 0.0f, 0.5f };

                ImGui::ColorEdit3("Renk 1", col1);
                ImGui::ColorEdit4("Renk 2", col2);
            });

            ImGui::Spacing();

            Components::DrawCard("TreeWidgets", "AGAC VE YARDIM", [&]()
            {
                if (ImGui::TreeNode("Agac Duzeyi 1"))
                {
                    ImGui::Text("Agac icerigi burada...");
                    if (ImGui::TreeNode("Agac Duzeyi 2"))
                    {
                        ImGui::Text("Ikinci seviye icerik.");
                        ImGui::TreePop();
                    }
                    ImGui::TreePop();
                }

                ImGui::Separator();
                ImGui::TextDisabled("Uzerine gelince bilgi cikar:");
                ImGui::SameLine();
                Components::DrawTooltip("Bu bir ipucu mesajidir (Tooltip).");
            });

            ImGui::EndTable();
        }
    }
}
