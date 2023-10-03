#include "Engine.h"

Engine::Engine()
{
    // Get the screen resolution 
    // and create an SFML window and View
    Vector2f resolution;

    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    m_window_.create(VideoMode(resolution.x, resolution.y),
        "Thomas was late",
        Style::Fullscreen);

    // Initialize the full screen view
    m_main_view_.setSize(resolution);
    m_hud_view_.reset(
        FloatRect(0, 0, resolution.x, resolution.y));

    // Initialize the split-screen Views
    m_left_view_.setViewport(
        FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
    m_right_view_.setViewport(
        FloatRect(0.5f, 0.001f, 0.499f, 0.998f));
    m_bg_left_view_.setViewport(
        FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
    m_bg_right_view_.setViewport(
        FloatRect(0.5f, 0.001f, 0.499f, 0.998f));

    m_background_texture_ = TextureCache::GetTexture(
        "graphics/background.png");

    // Associate the sprite with the texture
    m_background_sprite_.setTexture(m_background_texture_);

    // Load texture for background vertex array
    m_texture_tiles_ = TextureCache::GetTexture(
        "graphics/tiles_sheet.png");
}

void Engine::Run()
{
    // Timing     
    Clock clock;
    while (m_window_.isOpen())
    {
        Time dt = clock.restart();

        // Update the total game time
        m_game_time_total_ += dt;

        // Make a decimal fraction from the delta time
        const float dt_as_seconds = dt.asSeconds();

        // Call each part of the game loop in turn
        Input();
        Update(dt_as_seconds);
        Draw();
    }
}
