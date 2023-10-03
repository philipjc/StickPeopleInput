#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::Update(const float dt_as_seconds)
{
    if (m_character1_)
    {
        // Count down the time the player has left
        m_time_remaining_ -= dt_as_seconds;

        // Have Thomas and Bob run out of time?
        if (m_time_remaining_ <= 0)
        {
            m_new_level_required_ = true;
        }

    }// End if playing

}