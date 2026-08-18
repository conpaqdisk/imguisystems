#include "GameData.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace Core
{
    void GameData::LoadData()
    {
        m_items.clear();
        m_mobs.clear();

        // Load Items
        std::ifstream itemFile("assets/items.csv");
        if (itemFile.is_open())
        {
            std::string line;
            std::getline(itemFile, line); // header
            while (std::getline(itemFile, line))
            {
                std::stringstream ss(line);
                std::string idStr, name, desc;
                if (std::getline(ss, idStr, ',') && std::getline(ss, name, ',') && std::getline(ss, desc, ','))
                {
                    try {
                        GameItem item;
                        item.id = std::stoul(idStr);
                        item.name = name;
                        item.description = desc;
                        m_items.push_back(item);
                    } catch(...) {}
                }
            }
        }

        // Load Mobs
        std::ifstream mobFile("assets/mobs.csv");
        if (mobFile.is_open())
        {
            std::string line;
            std::getline(mobFile, line); // header
            while (std::getline(mobFile, line))
            {
                std::stringstream ss(line);
                std::string idStr, name, lvlStr;
                if (std::getline(ss, idStr, ',') && std::getline(ss, name, ',') && std::getline(ss, lvlStr, ','))
                {
                    try {
                        GameMob mob;
                        mob.id = std::stoul(idStr);
                        mob.name = name;
                        mob.level = lvlStr;
                        m_mobs.push_back(mob);
                    } catch(...) {}
                }
            }
        }

        // Load Skills
        std::ifstream skillFile("assets/skills.csv");
        if (skillFile.is_open())
        {
            std::string line;
            std::getline(skillFile, line); // header
            while (std::getline(skillFile, line))
            {
                std::stringstream ss(line);
                std::string listName, name, idStr;
                if (std::getline(ss, listName, ',') && std::getline(ss, name, ',') && std::getline(ss, idStr, ','))
                {
                    try {
                        GameSkill skill;
                        skill.listName = listName;
                        skill.name = name;
                        skill.id = std::stoul(idStr);
                        m_skills.push_back(skill);
                    } catch(...) {}
                }
            }
        }

        // Load Classes
        std::ifstream classFile("assets/classes.csv");
        if (classFile.is_open())
        {
            std::string line;
            std::getline(classFile, line); // header
            while (std::getline(classFile, line))
            {
                std::stringstream ss(line);
                std::string idStr, nation, job, range, desc;
                if (std::getline(ss, idStr, ',') && std::getline(ss, nation, ',') && 
                    std::getline(ss, job, ',') && std::getline(ss, range, ',') && std::getline(ss, desc, ','))
                {
                    try {
                        GameClass cls;
                        cls.id = std::stoul(idStr);
                        cls.nation = nation;
                        cls.job = job;
                        cls.levelRange = range;
                        cls.description = desc;
                        m_classes.push_back(cls);
                    } catch(...) {}
                }
            }
        }

        // Load Races
        std::ifstream raceFile("assets/races.csv");
        if (raceFile.is_open())
        {
            std::string line;
            std::getline(raceFile, line); // header
            while (std::getline(raceFile, line))
            {
                std::stringstream ss(line);
                std::string idStr, nation, name;
                if (std::getline(ss, idStr, ',') && std::getline(ss, nation, ',') && std::getline(ss, name, ','))
                {
                    try {
                        GameRace race;
                        race.id = std::stoul(idStr);
                        race.nation = nation;
                        race.name = name;
                        m_races.push_back(race);
                    } catch(...) {}
                }
            }
        }
    }
}
