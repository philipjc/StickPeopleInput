#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::Update(const float dt_as_seconds)
{
    if (m_new_level_required_)
    {
        // Spawn Thomas and Bob
        m_thomas_.Spawn(Vector2f(0, 0), gravity_);
        m_bob_.Spawn(Vector2f(100, 0), gravity_);

        // Make sure spawn is called only once
        m_time_remaining_ = 10;
        m_new_level_required_ = false;
    }

    if (m_playing_)
    {
        // Update Thomas
        m_thomas_.Update(dt_as_seconds);

        // Update Bob
        m_bob_.Update(dt_as_seconds);

        // Count down the time the player has left
        m_time_remaining_ -= dt_as_seconds;

        // Have Thomas and Bob run out of time?
        if (m_time_remaining_ <= 0)
        {
            m_new_level_required_ = true;
        }

    }
	// End if playing

        // Set the appropriate view around the appropriate character
    if (m_split_screen_)
    {
        m_left_view_.setCenter(m_thomas_.GetCenter());
        m_right_view_.setCenter(m_bob_.GetCenter());
    }
    else
    {
        // Centre full screen around appropriate character
        if (m_character1_)
        {
            m_main_view_.setCenter(m_thomas_.GetCenter());
        }
        else
        {
            m_main_view_.setCenter(m_bob_.GetCenter());
        }
    }
}