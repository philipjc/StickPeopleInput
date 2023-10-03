#include "Bob.h"
#include "TextureCache.h"

Bob::Bob()
{
    // Associate a texture with the sprite
    m_sprite_ = Sprite(TextureCache::GetTexture(
        "graphics/bob.png"));
    m_jump_duration_ = .25;
}

bool Bob::HandleInput()
{
    m_just_jumped_ = false;

    if (Keyboard::isKeyPressed(Keyboard::Up))
    {
        // Start a jump if not already jumping
        // but only if standing on a block (not falling)
        if (!m_is_jumping_ && !m_is_falling_)
        {
            m_is_jumping_ = true;
            m_time_this_jump_ = 0;
            m_just_jumped_ = true;
        }
    }
    else
    {
        m_is_jumping_ = false;
        m_is_falling_ = true;
    }

    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        m_left_pressed_ = true;
    }
    else
    {
        m_left_pressed_ = false;
    }

    if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        m_right_pressed_ = true;
    }
    else
    {
        m_right_pressed_ = false;
    }

    return m_just_jumped_;
}
