#pragma once
#include <string>
#include <vector>

namespace Core
{
    struct GameItem
    {
        unsigned int id;
        std::string name;
        std::string description;
    };

    struct GameMob
    {
        unsigned int id;
        std::string name;
        std::string level;
    };

    struct GameSkill
    {
        std::string listName;
        std::string name;
        unsigned int id;
    };

    struct GameClass
    {
        unsigned int id;
        std::string nation;
        std::string job;
        std::string levelRange;
        std::string description;
    };

    struct GameRace
    {
        unsigned int id;
        std::string nation;
        std::string name;
    };

    class GameData
    {
    public:
        static GameData& Get()
        {
            static GameData instance;
            return instance;
        }

        void LoadData();

        const std::vector<GameItem>& GetItems() const { return m_items; }
        const std::vector<GameMob>& GetMobs() const { return m_mobs; }
        const std::vector<GameSkill>& GetSkills() const { return m_skills; }
        const std::vector<GameClass>& GetClasses() const { return m_classes; }
        const std::vector<GameRace>& GetRaces() const { return m_races; }

    private:
        GameData() = default;
        ~GameData() = default;
        GameData(const GameData&) = delete;
        GameData& operator=(const GameData&) = delete;

        std::vector<GameItem> m_items;
        std::vector<GameMob> m_mobs;
        std::vector<GameSkill> m_skills;
        std::vector<GameClass> m_classes;
        std::vector<GameRace> m_races;
    };
}
