#include "Engine.h"
#include <iostream>
#include "TextureCache.h"


Engine::Engine()
{
	// Get the screen resolution and create an SFML window and View
	sf::Vector2f resolution;
	try
	{
		const sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
		if (desktopMode.isValid())
		{
			resolution.x = static_cast<float>(desktopMode.width);
			resolution.y = static_cast<float>(desktopMode.height);
		}
		else
		{
			// Provide some default values or exit
			std::cerr << "Invalid desktop video mode. Exiting." << std::endl;
			return;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "An exception occurred: " << e.what() << std::endl;
		return;
	}

	m_Window.create(VideoMode(static_cast<float>(resolution.x), static_cast<float>(resolution.y)),
		"Thomas was late",
		Style::Fullscreen);

	// Initialize the full screen view
	m_MainView.setSize(resolution);

	// Two lines below used to create zoomed our screenshots for the book

	//m_BGMainView.zoom(2.5);
	//m_MainView.zoom(2.5);
	m_HudView.reset(
		FloatRect(0, 0, resolution.x, resolution.y));

	// Initialise the split-screen Views
	m_LeftView.setViewport(
		FloatRect(0.001f, 0.001f, 0.498f, 0.998f));

	m_RightView.setViewport(
		FloatRect(0.5f, 0.001f, 0.499f, 0.998f));

	m_BgLeftView.setViewport(
		FloatRect(0.001f, 0.001f, 0.498f, 0.998f));

	m_BgRightView.setViewport(
		FloatRect(0.5f, 0.001f, 0.499f, 0.998f));

	// Can this graphics card use shader GFX?
	if (!sf::Shader::isAvailable())
	{
		// Time to get a new PC
		m_Window.close();
	}

	m_BackgroundTexture = TextureCache::GetTexture(
		"graphics/background.png");

	// Associate the sprite with the texture
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	// Load the texture for the background vertex array
	m_TextureTiles = TextureCache::GetTexture(
		"graphics/tiles_sheet.png");

}

void Engine::Run()
{
	// Timing 	
	Clock clock;

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();

		// Update the total game time
		m_GameTimeTotal += dt;

		// Make a decimal fraction from the delta time
		const float dtAsSeconds = dt.asSeconds();

		Input();
		Update(dtAsSeconds);
		Draw();
	}
}