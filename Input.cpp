

#include "Engine.h"

void Engine::Input()
{
    Event event{};

    while (m_window_.pollEvent(event))
    {
        if (event.type == Event::KeyPressed)
        {
            // Handle the player quitting
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                m_window_.close();
            }
            // Handle the player starting the game
            if (Keyboard::isKeyPressed(Keyboard::Return))
            {
                m_playing_ = true;
            }
            // Switch between Thomas and Bob
            if (Keyboard::isKeyPressed(Keyboard::Q))
            {
                m_character1_ = !m_character1_;
            }
            // Switch between full and split-screen
            if (Keyboard::isKeyPressed(Keyboard::E))
            {
                m_split_screen_ = !m_split_screen_;
            }
        }
    }

    // Handle input specific to Thomas
    if (m_thomas_.HandleInput())
    {
        // Play a jump sound
    }
    // Handle input specific to Bob
    if (m_bob_.HandleInput())
    {
        // Play a jump sound
    }
}
