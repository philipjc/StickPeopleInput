#include <iostream>
#include "Engine.h"

void Engine::Input()
{
	Event event{};
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			// Handle player quitting
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				m_Window.close();
			}

			// Handle starting game
			if (Keyboard::isKeyPressed(Keyboard::Return))
			{
				std::cout << "Return pushed" << std::endl;

				m_Playing = true;
			}

			// Switch between split-screen
			if (Keyboard::isKeyPressed(Keyboard::E))
			{
				m_SplitScreen = !m_SplitScreen;
			}
		}
	}

	// Handle input specific to Thomas
	if (m_Thomas.HandleInput())
	{
		// Play a jump sound
	}

	// Handle input specific to Bob
	if (m_Bob.HandleInput())
	{
		// Play a jump sound
	}

}