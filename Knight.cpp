#include "Knight.h"

#include <iostream>

#include "TextureCache.h"


Knight::Knight()
{
	m_IdleTexture = TextureCache::GetTexture("graphics/knight/idle.png");
	m_WalkingTexture = TextureCache::GetTexture("graphics/knight/walk.png");
	m_AttackingTexture = TextureCache::GetTexture("graphics/knight/attack_1.png");

	// Associate a texture with the sprite
	m_PlayerSprite = Sprite();
	m_PlayerSprite.setTexture(m_IdleTexture);

	m_JumpDuration = .25;

	m_IsIdle = true;
	m_PlayerIdleClock.restart();
	m_IdleFrame = 0;

}

bool Knight::HandleInput()
{
	m_PlayerJustJumped = false;

	if (Keyboard::isKeyPressed(Keyboard::F))
	{
		m_IsIdle = false;
		m_PlayerAttacking = true;
		m_PlayerSprite.setTexture(m_AttackingTexture);
	}
	else
	{
		m_IsIdle = true;
		m_PlayerAttacking = false;
		m_PlayerSprite.setTexture(m_IdleTexture);
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		if (!m_PlayerIsJumping && !m_PlayerIsFalling)
		{
			m_PlayerIsJumping = true;
			m_PlayerTimeJump = 0;
			m_PlayerJustJumped = true;
		}
	}
	else
	{
		if (!m_PlayerAttacking)
		{
			m_PlayerIsJumping = false;
			m_PlayerIsFalling = true;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		m_IsIdle = false;
		m_PlayerLeftPressed = true;
		m_PlayerSprite.setTexture(m_WalkingTexture);
	}
	else
	{
		if (!m_PlayerAttacking)
		{
			m_IsIdle = true;
			m_PlayerLeftPressed = false;
			m_PlayerSprite.setTexture(m_IdleTexture);
		}
	}


	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		m_IsIdle = false;
		m_PlayerRightPressed = true;
		m_PlayerSprite.setTexture(m_WalkingTexture);
	}
	else
	{
		if (!m_PlayerAttacking)
		{
			m_IsIdle = true;
			m_PlayerRightPressed = false;
			m_PlayerSprite.setTexture(m_IdleTexture);
		}
	}

	// Respond to state changes

	if (m_PlayerRightPressed)
	{
		m_PlayerSprite.setScale(1, 1);
	}

	if (m_PlayerLeftPressed)
	{
		m_PlayerSprite.setOrigin(m_PlayerSprite.getGlobalBounds().width, 0);
		m_PlayerSprite.setScale(-1, 1);
	}
	
	if (m_IsIdle && !m_PlayerAttacking)
	{
		// Animate idle
		m_PlayerSprite.setTextureRect(sf::IntRect(70, m_Bottom+20, 70, m_Top));
	}

	if (!m_IsIdle && m_PlayerAttacking)
	{
		// Animate attacking
		if (m_PlayerIdleClock.getElapsedTime().asSeconds() > 0.1f)
		{
			if (m_IdleFrame == m_AttackingFrames)
			{
				m_IdleFrame = 0;
			}

			m_PlayerSprite.setTextureRect(sf::IntRect(m_IdleFrame * 80, m_Bottom+10, 80, m_Top));

			m_IdleFrame++;

			m_PlayerIdleClock.restart();
		}
	}

	if (!m_IsIdle)
	{
		// Animate walking
		if (m_PlayerIdleClock.getElapsedTime().asSeconds() > 0.1f)
		{
			if (m_IdleFrame == m_IdleFrames)
			{
				m_IdleFrame = 0;
			}

			m_PlayerSprite.setTextureRect(sf::IntRect(m_IdleFrame * 70, m_Bottom, 70, m_Top));

			m_IdleFrame++;

			m_PlayerIdleClock.restart();
		}
	}
	

	return m_PlayerJustJumped;
}