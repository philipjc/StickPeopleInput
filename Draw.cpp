#include "Engine.h"

void Engine::Draw()
{
    // Rub out the last frame
    m_window_.clear(Color::White);

    if (!m_split_screen_)
    {
        // Switch to background view
        m_window_.setView(m_bg_main_view_);

        // Draw the background
        m_window_.draw(m_background_sprite_);

        // Switch to m_MainView
        m_window_.setView(m_main_view_);

        // Draw thomas
        m_window_.draw(m_thomas_.GetSprite());

        // Draw bob
        m_window_.draw(m_bob_.GetSprite());
    }
    else
    {
        // Split-screen view is active
        // First draw Thomas' side of the screen

        // Switch to background view
        m_window_.setView(m_bg_left_view_);

        // Draw the background
        m_window_.draw(m_background_sprite_);

        // Switch to m_LeftView
        m_window_.setView(m_left_view_);

        // Draw bob
        m_window_.draw(m_bob_.GetSprite());

        // Draw thomas
        m_window_.draw(m_thomas_.GetSprite());

        // Now draw Bob's side of the screen

        // Switch to background view
        m_window_.setView(m_bg_right_view_);

        // Draw the background
        m_window_.draw(m_background_sprite_);

        // Switch to m_RightView
        m_window_.setView(m_right_view_);

        // Draw Level
        m_window_.draw(m_va_level_, &m_texture_tiles_);

        // Draw thomas
        m_window_.draw(m_thomas_.GetSprite());

        // Draw bob
        m_window_.draw(m_bob_.GetSprite());

    }
    // Draw the HUD
    // Switch to m_HudView
    m_window_.setView(m_hud_view_);


    // Show everything we have just drawn
    m_window_.display();
}