#include "InventoryPanel.h"
#include <imgui.h>
#include "../../Core/AppState.h"
#include "../../Core/GameData.h"
#include "../Core/UIComponents.h"

namespace UI
{
    void InventoryPanel::Render()
    {
        Components::DrawPageTitle("Inventory & Tedarik", "Otomatik alisveris, satis, ve canta koruma");
        auto& state = Core::AppState::Get();

        if (ImGui::BeginTable("InvGrid", 2, ImGuiTableFlags_PadOuterX))
        {
            ImGui::TableNextRow();
            
            // SOL SUTUN
            ImGui::TableSetColumnIndex(0);
            
            Components::DrawCard("SettingsCard", "OTOMATIK ISLEMLER", [&]()
            {
                ImGui::Checkbox("Otomatik Sat (Auto Sell)", &state.Inventory.autoSell);
                Components::DrawTooltip("Belirlenen cop/satilabilir itemleri otomatik NPC'ye satar.");
                
                ImGui::Checkbox("Otomatik Al (Auto Buy)", &state.Inventory.autoBuy);
                
                ImGui::Separator();
                ImGui::Checkbox("Otomatik Tamir (RPR)", &state.Inventory.rprActive);
                if (state.Inventory.rprActive)
                {
                    ImGui::Indent();
                    ImGui::SliderInt("Dayaniklilik (Durability) Siniri", &state.Inventory.rprThreshold, 1, 100);
                    ImGui::Unindent();
                }
            });

            ImGui::Spacing();
            
            Components::DrawCard("ProtectedCard", "SATILMAYACAKLAR (KORUNANLAR)", [&]()
            {
                auto& itemsData = Core::GameData::Get().GetItems();
                static std::string searchProtected = "";
                static char searchBufProtected[128] = "";
                
                ImGui::InputTextWithHint("##searchProtected", "Item Ara (Korunan)...", searchBufProtected, IM_ARRAYSIZE(searchBufProtected));
                searchProtected = searchBufProtected;
                
                if (ImGui::BeginCombo("Korunan Ekle", "Item Sec..."))
                {
                    for (const auto& item : itemsData)
                    {
                        if (!searchProtected.empty() && item.name.find(searchProtected) == std::string::npos)
                            continue;
                            
                        if (ImGui::Selectable(item.name.c_str()))
                        {
                            Core::ItemConfig newItem;
                            newItem.id = item.id;
                            newItem.name = item.name;
                            newItem.protectedItem = true;
                            state.Inventory.protectedItems.push_back(newItem);
                        }
                    }
                    ImGui::EndCombo();
                }

                if (ImGui::BeginTable("ProtectedTable", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
                {
                    ImGui::TableSetupColumn("Durum", ImGuiTableColumnFlags_WidthFixed, 40.0f);
                    ImGui::TableSetupColumn("Item Adi", ImGuiTableColumnFlags_WidthStretch);
                    ImGui::TableSetupColumn("Islem", ImGuiTableColumnFlags_WidthFixed, 50.0f);
                    ImGui::TableHeadersRow();

                    for (size_t i = 0; i < state.Inventory.protectedItems.size(); ++i)
                    {
                        auto& item = state.Inventory.protectedItems[i];
                        ImGui::TableNextRow();
                        
                        ImGui::TableSetColumnIndex(0);
                        std::string chkLabel = "##p_chk" + std::to_string(i);
                        ImGui::Checkbox(chkLabel.c_str(), &item.protectedItem);

                        ImGui::TableSetColumnIndex(1);
                        ImGui::TextUnformatted(item.name.c_str());

                        ImGui::TableSetColumnIndex(2);
                        std::string btnLabel = "Sil##p" + std::to_string(i);
                        if (ImGui::Button(btnLabel.c_str()))
                        {
                            state.Inventory.protectedItems.erase(state.Inventory.protectedItems.begin() + i);
                            i--; 
                        }
                    }
                    ImGui::EndTable();
                }
            });

            // SAG SUTUN
            ImGui::TableSetColumnIndex(1);
            
            Components::DrawCard("SellCard", "SATILACAKLAR (COP)", [&]()
            {
                auto& itemsData = Core::GameData::Get().GetItems();
                static std::string searchSell = "";
                static char searchBufSell[128] = "";
                
                ImGui::InputTextWithHint("##searchSell", "Item Ara (Cop)...", searchBufSell, IM_ARRAYSIZE(searchBufSell));
                searchSell = searchBufSell;
                
                if (ImGui::BeginCombo("Cop Ekle", "Item Sec..."))
                {
                    for (const auto& item : itemsData)
                    {
                        if (!searchSell.empty() && item.name.find(searchSell) == std::string::npos)
                            continue;
                            
                        if (ImGui::Selectable(item.name.c_str()))
                        {
                            Core::ItemConfig newItem;
                            newItem.id = item.id;
                            newItem.name = item.name;
                            newItem.sellable = true;
                            state.Inventory.sellItems.push_back(newItem);
                        }
                    }
                    ImGui::EndCombo();
                }

                if (ImGui::BeginTable("SellTable", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
                {
                    ImGui::TableSetupColumn("Durum", ImGuiTableColumnFlags_WidthFixed, 40.0f);
                    ImGui::TableSetupColumn("Item Adi", ImGuiTableColumnFlags_WidthStretch);
                    ImGui::TableSetupColumn("Islem", ImGuiTableColumnFlags_WidthFixed, 50.0f);
                    ImGui::TableHeadersRow();

                    for (size_t i = 0; i < state.Inventory.sellItems.size(); ++i)
                    {
                        auto& item = state.Inventory.sellItems[i];
                        ImGui::TableNextRow();
                        
                        ImGui::TableSetColumnIndex(0);
                        std::string chkLabel = "##s_chk" + std::to_string(i);
                        ImGui::Checkbox(chkLabel.c_str(), &item.sellable);

                        ImGui::TableSetColumnIndex(1);
                        ImGui::TextUnformatted(item.name.c_str());

                        ImGui::TableSetColumnIndex(2);
                        std::string btnLabel = "Sil##s" + std::to_string(i);
                        if (ImGui::Button(btnLabel.c_str()))
                        {
                            state.Inventory.sellItems.erase(state.Inventory.sellItems.begin() + i);
                            i--; 
                        }
                    }
                    ImGui::EndTable();
                }
            });

            ImGui::EndTable();
        }
    }
}
