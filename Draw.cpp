#include "Engine.h"

void Engine::Draw()
{
	// Rub out the last frame
	m_Window.clear(Color::White);

	if (!m_SplitScreen)
	{
		// Switch to background view
		m_Window.setView(m_BgMainView);

		// Draw the background
		m_Window.draw(m_BackgroundSprite);

		// Switch to m_MainView
		m_Window.setView(m_MainView);

		// Draw the Level
		m_Window.draw(m_VaLevel, &m_TextureTiles);

		// Draw thomas
		// m_Window.draw(m_Thomas.getSprite());

		// Draw bob
		m_Window.draw(m_Bob.GetSprite());
	}
	else
	{
		// Split-screen view is active

		// First draw Thomas' side of the screen

		// Switch to background view
		m_Window.setView(m_BgLeftView);

		// Draw the background
		m_Window.draw(m_BackgroundSprite);

		// Switch to m_LeftView
		m_Window.setView(m_LeftView);

		// Draw the Level
		m_Window.draw(m_VaLevel, &m_TextureTiles);

		// Draw bob
		m_Window.draw(m_Bob.GetSprite());

		// Draw thomas
		// m_Window.draw(m_Thomas.getSprite());

		// Now draw Bob's side of the screen

		// Switch to background view
		m_Window.setView(m_BgRightView);

		// Draw the background
		m_Window.draw(m_BackgroundSprite);

		// Switch to m_RightView
		m_Window.setView(m_RightView);

		// Draw the Level
		m_Window.draw(m_VaLevel, &m_TextureTiles);

		// Draw thomas
		m_Window.draw(m_Thomas.GetSprite());

		// Draw bob
		m_Window.draw(m_Bob.GetSprite());

	}

	// Draw the HUD
	// Switch to m_HudView
	m_Window.setView(m_HudView);


	// Show everything we have just drawn
	m_Window.display();
}