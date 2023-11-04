#include "Engine.h"
#include <iostream>

Engine::Engine()
{

    if (!CheckShaderSupport()) {
        std::cerr << "Failed to initialize window. Exiting." << std::endl;
        return;
    }

	InitializeWindow();
    LoadTextures();

}

bool Engine::InitializeWindow()
{
    sf::Vector2f resolution;
    try {
        const sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
        if (desktopMode.isValid()) {
            resolution.x = static_cast<float>(desktopMode.width);
            resolution.y = static_cast<float>(desktopMode.height);
        }
        else {
            return false;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "An exception occurred: " << e.what() << std::endl;
        return false;
    }

    m_Window.create(VideoMode(static_cast<float>(resolution.x), static_cast<float>(resolution.y)),
        "Infernal Gates",
        Style::Fullscreen);

    // Initialize the full screen view
    m_MainView.setSize(resolution);

    /* Two lines below used to create zoomed our screenshots for the book
    m_BGMainView.zoom(2.5);
    m_MainView.zoom(2.5); */

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

    // Can this gpu use shader GFX?
    if (!sf::Shader::isAvailable())
    {
        m_Window.close();
    }

    return true;
}


void Engine::LoadTextures()
{
    m_BackgroundTexture = TextureCache::GetTexture("graphics/backgrounds/bg_mystic_forest.png");
    m_BackgroundSprite.setTexture(m_BackgroundTexture);

    m_TextureTiles = TextureCache::GetTexture("graphics/tiles_sheet.png");

    // LOAD ALL TEXTURE HERE
}

bool Engine::CheckShaderSupport()
{
    if (!sf::Shader::isAvailable()) {
        m_Window.close();
        return false;
    }
    return true;
}

void Engine::Run()
{
    Clock clock;

    while (m_Window.isOpen())
    {
        Time dt = clock.restart();
        m_GameTimeTotal += dt;
        const float dtAsSeconds = dt.asSeconds();

        Input();
        Update(dtAsSeconds);
        Draw();
    }
}
