#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TextureCache.h"
#include <sstream>
#include <fstream>
#include "LevelManager.h"

using namespace sf;
using namespace std;

int** LevelManager::NextLevel(VertexArray& r_va_level)
{
    m_level_size_.x = 0;
    m_level_size_.y = 0;

    // Get the next level
    m_current_level_++;

    if (m_current_level_ > num_levels_)
    {
        m_current_level_ = 1;
        m_time_modifier_ -= .1f;
    }

    // Load the appropriate level from a text file
    string level_to_load;

    switch (m_current_level_)
    {
    case 1:
        level_to_load = "levels/level1.txt";
        m_start_position_.x = 100;
        m_start_position_.y = 100;
        m_base_time_limit_ = 30.0f;
        break;
    case 2:
        level_to_load = "levels/level2.txt";
        m_start_position_.x = 100;
        m_start_position_.y = 3600;
        m_base_time_limit_ = 100.0f;
        break;
    case 3:
        level_to_load = "levels/level3.txt";
        m_start_position_.x = 1250;
        m_start_position_.y = 0;
        m_base_time_limit_ = 30.0f;
        break;
    case 4:
        level_to_load = "levels/level4.txt";
        m_start_position_.x = 50;
        m_start_position_.y = 200;
        m_base_time_limit_ = 50.0f;
        break;
default: ;
    }
    return nullptr;
};