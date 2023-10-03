#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class LevelManager
{
private:
    Vector2i m_level_size_;
    Vector2f m_start_position_;

    float m_time_modifier_ = 1;
    float m_base_time_limit_ = 0;

    int m_current_level_ = 0;
    const int num_levels_ = 4;

    // public declarations go here
public:
    const int tile_size = 50;
    const int verts_in_quad = 4;

    float GetTimeLimit() const;
    int GetCurrentLevel() const;
    int** NextLevel(VertexArray& r_va_level);

    Vector2i GetLevelSize() const;
    Vector2f GetStartPosition() const;

};
