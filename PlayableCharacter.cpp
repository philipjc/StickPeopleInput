#include "PlayableCharacter.h"

void PlayableCharacter::Spawn(
	const Vector2f start_position, const float gravity)
{
    // Place the player at the starting point
    m_position_.x = start_position.x;
    m_position_.y = start_position.y;

    // Initialize the gravity
    m_gravity_ = gravity;

    // Move the sprite in to position
    m_sprite_.setPosition(m_position_);
}


void PlayableCharacter::Update(const float elapsed_time)
{
    if (m_right_pressed_)
    {
        m_position_.x += m_speed_ * elapsed_time;
    }
    if (m_left_pressed_)
    {
        m_position_.x -= m_speed_ * elapsed_time;
    }
    // Handle Jumping
    if (m_is_jumping_)
    {
        // Update how long the jump has been going
        m_time_this_jump_ += elapsed_time;
        // Is the jump going upwards
        if (m_time_this_jump_ < m_jump_duration_)
        {
            // Move up at twice gravity
            m_position_.y -= m_gravity_ * 2 * elapsed_time;
        }
        else
        {
            m_is_jumping_ = false;
            m_is_falling_ = true;
        }
    }
    // Apply gravity
    if (m_is_falling_)
    {
        m_position_.y += m_gravity_ * elapsed_time;
    }
    // Update the rect for all body parts
    const FloatRect r = GetPosition();

    // Feet
    m_feet_.left = r.left + 3;
    m_feet_.top = r.top + r.height - 1;
    m_feet_.width = r.width - 6;
    m_feet_.height = 1;

    // Head
    m_head_.left = r.left;
    m_head_.top = r.top + (r.height * .3);
    m_head_.width = r.width;
    m_head_.height = 1;

    // Right
    m_right_.left = r.left + r.width - 2;
    m_right_.top = r.top + r.height * .35;
    m_right_.width = 1;
    m_right_.height = r.height * .3;

    // Left
    m_left_.left = r.left;
    m_left_.top = r.top + r.height * .5;
    m_left_.width = 1;
    m_left_.height = r.height * .3;

    // Move the sprite into position
    m_sprite_.setPosition(m_position_);
}


FloatRect PlayableCharacter::GetPosition() const
{
    return m_sprite_.getGlobalBounds();
}

FloatRect PlayableCharacter::GetFeet() const
{
    return m_feet_;
}

FloatRect PlayableCharacter::GetHead() const
{
    return m_head_;
}

FloatRect PlayableCharacter::GetRight() const
{
    return m_right_;
}

FloatRect PlayableCharacter::GetLeft() const
{
    return m_left_;
}

Sprite PlayableCharacter::GetSprite()
{
    return m_sprite_;
}

Vector2f PlayableCharacter::GetCenter() const
{
    return Vector2f(
        m_position_.x + m_sprite_.getGlobalBounds().width / 2,
        m_position_.y + m_sprite_.getGlobalBounds().height / 2
    );
}

void PlayableCharacter::StopFalling(const float position)
{
    m_position_.y = position - GetPosition().height;
    m_sprite_.setPosition(m_position_);
    m_is_falling_ = false;
}

void PlayableCharacter::StopRight(const float position)
{

    m_position_.x = position - m_sprite_.getGlobalBounds().width;
    m_sprite_.setPosition(m_position_);
}

void PlayableCharacter::StopLeft(const float position)
{
    m_position_.x = position + m_sprite_.getGlobalBounds().width;
    m_sprite_.setPosition(m_position_);
}

void PlayableCharacter::StopJump()
{
    // Stop a jump early 
    m_is_jumping_ = false;
    m_is_falling_ = true;
}