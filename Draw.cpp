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

		// Draw Knight
		m_Window.draw(m_Knight.GetSprite());

		m_Window.draw(m_Enemy.GetEnemySprite());
	}
	else
	{
		// Split-screen view is active

		// Switch to background view
		m_Window.setView(m_BgLeftView);

		// Draw the background
		m_Window.draw(m_BackgroundSprite);

		// Switch to m_LeftView
		m_Window.setView(m_LeftView);

		m_Window.draw(m_VaLevel, &m_TextureTiles);
		m_Window.draw(m_Knight.GetSprite());
		m_Window.draw(m_Enemy.GetEnemySprite());
		m_Window.draw(m_Knight.GetSprite());

		// Switch to background view
		m_Window.setView(m_BgRightView);
		m_Window.draw(m_BackgroundSprite);
		m_Window.setView(m_RightView);

		// Draw the Level
		m_Window.draw(m_VaLevel, &m_TextureTiles);

	}

	// Draw the HUD
	// Switch to m_HudView
	m_Window.setView(m_HudView);

	// Show everything we have just drawn
	m_Window.display();
}