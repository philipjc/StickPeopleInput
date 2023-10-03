#pragma once

#include <SFML/Graphics.hpp>
#include "TextureCache.h"
#include "Thomas.h"
#include "Bob.h"

using namespace sf;

class Engine
{
private:
    // The texture holder
    TextureCache th_;

    Thomas m_thomas_;
    Bob m_bob_;

    const int tile_size_ = 50;
    const int quad_verts_qty_ = 4;

    // The force pushing the characters down
    const int gravity_ = 300;

    // A regular RenderWindow
    RenderWindow m_window_;

    // The main Views
    View m_main_view_;
    View m_left_view_;
    View m_right_view_;

    // Three views for the background
    View m_bg_main_view_;
    View m_bg_left_view_;
    View m_bg_right_view_;
    View m_hud_view_;

    // Declare a sprite and a Texture 
    // for the background
    Sprite m_background_sprite_;
    Texture m_background_texture_;

    // Is the game currently playing?
    bool m_playing_ = false;

    // Is character 1 or 2 the current focus?
    bool m_character1_ = true;

    // Start in full screen (not split) mode
    bool m_split_screen_ = false;

    // Time left in the current level (seconds)
    float m_time_remaining_ = 10;
    Time m_game_time_total_;

    // Is it time for a new/first level?
    bool m_new_level_required_ = true;

    // Private functions for internal use only
    void Input();
    void Update(float dt_as_seconds);
    void Draw();

public:
    // The Engine constructor
    Engine();

    // Run will call all the private functions
    void Run();
};
