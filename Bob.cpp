#include "Bob.h"

#include <iostream>

#include "TextureCache.h"


Bob::Bob()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureCache::GetTexture(
		"graphics/knight/walk2.png"));

	m_WalkingSprite = Sprite(TextureCache::GetTexture(
		"graphics/knight/walk2.png"));

	
	//m_Sprite.setTextureRect(sf::IntRect(left, bottom, right, top));

	m_JumpDuration = .25;

	m_IsIdle = true;
	m_IdleClock.restart();
	m_IdleFrame = 0;

}

bool Bob::handleInput()
{

	m_JustJumped = false;

	
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{

		// Start a jump if not already jumping
		// but only if standing on a block (not falling)
		if (!m_IsJumping && !m_IsFalling)
		{
			m_IsJumping = true;
			m_TimeThisJump = 0;
			m_JustJumped = true;
		}

	}
	else
	{
		m_IsJumping = false;
		m_IsFalling = true;

	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		m_IsIdle = false;
		m_LeftPressed = true;

	}
	else
	{
		m_IsIdle = true;
		m_LeftPressed = false;
	}


	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		m_IsIdle = false;
		m_RightPressed = true;
	}
	else
	{
		m_IsIdle = true;
		m_RightPressed = false;
	}

	
	
	if (m_IsIdle)
	{

		// Animate idle
		m_Sprite.setTextureRect(sf::IntRect(0, bottom, 70, top));
	}

	else
	{
		// Animate walking
		if (m_IdleClock.getElapsedTime().asSeconds() > 0.1f)
		{
			if (m_IdleFrame == idle_frames)
			{
				m_IdleFrame = 0;
			}

			m_Sprite.setTextureRect(sf::IntRect(m_IdleFrame * 70, bottom, 70, top));

			m_IdleFrame++;

			m_IdleClock.restart();
		}
	}
	

	return m_JustJumped;
}