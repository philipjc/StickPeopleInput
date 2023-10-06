#include "Bob.h"

#include <iostream>

#include "TextureCache.h"


Bob::Bob()
{
	m_IdleTexture = TextureCache::GetTexture("graphics/knight/idle.png");
	m_WalkingTexture = TextureCache::GetTexture("graphics/knight/walk.png");
	m_AttackingTexture = TextureCache::GetTexture("graphics/knight/attack_1.png");

	// Associate a texture with the sprite
	m_Sprite = Sprite();
	m_Sprite.setTexture(m_IdleTexture);

	m_JumpDuration = .25;

	m_IsIdle = true;
	m_IdleClock.restart();
	m_IdleFrame = 0;

}

bool Bob::HandleInput()
{

	m_JustJumped = false;

	if (Keyboard::isKeyPressed(Keyboard::F))
	{
		m_IsIdle = false;
		m_Attacking = true;
		m_Sprite.setTexture(m_AttackingTexture);
	}
	else
	{
		m_IsIdle = true;
		m_Attacking = false;
		m_Sprite.setTexture(m_IdleTexture);
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		// Start a jump if not falling
		if (!m_IsJumping && !m_IsFalling)
		{
			m_IsJumping = true;
			m_TimeThisJump = 0;
			m_JustJumped = true;
		}
	}
	else
	{
		if (!m_Attacking)
		{
			m_IsJumping = false;
			m_IsFalling = true;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		m_IsIdle = false;
		m_LeftPressed = true;
		m_Sprite.setTexture(m_WalkingTexture);
	}
	else
	{
		if (!m_Attacking)
		{
			m_IsIdle = true;
			m_LeftPressed = false;
			m_Sprite.setTexture(m_IdleTexture);
		}
	}


	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		m_IsIdle = false;
		m_RightPressed = true;
		m_Sprite.setTexture(m_WalkingTexture);
	}
	else
	{
		if (!m_Attacking)
		{
			m_IsIdle = true;
			m_RightPressed = false;
			m_Sprite.setTexture(m_IdleTexture);
		}
	}

	// Respond to state changes

	if (m_RightPressed)
	{
		m_Sprite.setScale(1, 1);
	}

	if (m_LeftPressed)
	{
		m_Sprite.setOrigin(m_Sprite.getGlobalBounds().width, 0);
		m_Sprite.setScale(-1, 1);
	}
	
	if (m_IsIdle && !m_Attacking)
	{
		std::cout << "Idling" << std::endl;

		// Animate idle
		m_Sprite.setTextureRect(sf::IntRect(70, bottom+20, 70, top));
	}

	if (!m_IsIdle && m_Attacking)
	{
		std::cout << "Attacking" << std::endl;

		// Animate attacking
		// Animate walking
		if (m_IdleClock.getElapsedTime().asSeconds() > 0.1f)
		{
			if (m_IdleFrame == attacking_Frames)
			{
				m_IdleFrame = 0;
			}

			m_Sprite.setTextureRect(sf::IntRect(m_IdleFrame * 70, bottom+10, 70, top));

			m_IdleFrame++;

			m_IdleClock.restart();
		}
	}

	if (!m_IsIdle)
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