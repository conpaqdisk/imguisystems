#pragma once
#include <string>
#include <vector>
#include <map>

namespace Core
{
    enum class AppStatus
    {
        Ready,
        Running,
        Paused,
        Error
    };

    struct SkillConfig
    {
        int id = 0;
        std::string name;
        bool enabled = false;
        int priority = 0;
        float cooldown = 0.0f;
    };

    struct ItemConfig
    {
        int id = 0;
        std::string name;
        bool protectedItem = false;
        bool sellable = false;
        bool discardable = false;
        int amount = 0;
    };

    struct MobConfig
    {
        int id = 0;
        std::string name;
        bool enabled = false;
        float distance = 0.0f;
    };

    class AppState
    {
    public:
        static AppState& Get()
        {
            static AppState instance;
            return instance;
        }

        // Global State
        AppStatus CurrentStatus = AppStatus::Ready;
        std::string ProfileName = "Default";
        int UptimeSeconds = 0;
        int Level = 1;
        std::string CharacterName = "Unknown";
        int CurrentHP = 100, MaxHP = 100;
        int CurrentMP = 100, MaxMP = 100;
        float PosX = 0.0f, PosY = 0.0f;

        // --- Categories matching user spec ---
        
        struct {
            bool hpPotionEnabled = false;
            int hpThreshold = 50;
            std::string selectedHpPotion = "";
            bool mpPotionEnabled = false;
            int mpThreshold = 50;
            std::string selectedMpPotion = "";
            bool minorEnabled = false;
            int minorThreshold = 50;
            bool partyMinorEnabled = false;
            bool alwaysOnTop = false;
            bool pinCharacter = false;
            int deathBehavior = 0; // 0=Wait, 1=Town, 2=Relog
            int townBehavior = 0;
            bool autoTS = false;
            std::string selectedTS = "";
            bool autoLoot = false;
            bool lootOnlyCoin = false;
            bool lootSelectedItems = true;
            bool followEnabled = false;
            int selectedClassId = 0;
            int selectedRaceId = 0;
        } General;

        struct {
            bool attackActive = false;
            bool autoSelectTarget = false;
            int selectionMode = 0; // 0=Auto, 1=Manual, 2=List
            int attackSpeed = 100;
            int attackDistance = 50;
            int targetDistance = 50;
            bool ksMode = false;
            bool moveToMob = false;
            bool followMob = false;
            std::vector<SkillConfig> activeSkills;
            std::vector<SkillConfig> timedSkills;
            std::vector<MobConfig> mobList;
        } Combat;

        // Class Specifics
        struct {
            bool useStroke = false;
            bool useArchery = false;
        } Rogue;

        struct {
            bool healSelfEnabled = false;
            int healSelfThreshold = 50;
            bool healPartyEnabled = false;
            int healPartyThreshold = 50;
            bool autoHeal = false;
            bool buffActive = false;
            std::string buffSkill = "";
            std::string acSkill = "";
            std::string mindSkill = "";
            bool autoCure = false;
            bool partyCure = false;
            bool autoRez = false;
        } Priest;

        struct {
            bool autoAccept = false;
            bool autoLeave = false;
            int memberLimit = 8;
            int onAcceptBehavior = 0;
            int onBreakBehavior = 0;
        } Party;

        struct {
            bool autoBuy = false;
            bool autoSell = false;
            bool rprActive = false;
            int rprThreshold = 100;
            std::vector<ItemConfig> protectedItems;
            std::vector<ItemConfig> sellItems;
        } Inventory;

        struct {
            bool enabled = false;
            int minHpPotions = 0;
            int maxHpPotions = 0;
            int minMpPotions = 0;
            int maxMpPotions = 0;
            int minArrows = 0;
            int maxArrows = 0;
            std::string npcId = "";
        } Supply;

        struct {
            bool miningActive = false;
            bool fishingActive = false;
            std::string sundriesNpc = "";
            float slotX = 0.0f;
            float slotY = 0.0f;
            bool wallhackUI = false;
        } Farming;

        struct {
            bool active = false;
            std::vector<std::string> rules;
        } Automation;

        struct {
            int themeId = 4; // Default to Purple
            float sidebarWidth = 200.0f;
            bool compactMode = false;
            bool animations = true;
            bool showDemoWindow = false;
        } Settings;

    private:
        AppState() = default;
    };
}
