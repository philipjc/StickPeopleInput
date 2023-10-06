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

void Bob::SetIdle()
{
	m_IsIdle = true;
	m_Sprite.setTexture(m_IdleTexture);
}

void Bob::SetFalling()
{
	m_IsIdle = false;
	m_IsFalling = true;
	m_Sprite.setTexture(m_FallingTexture);
}

void Bob::SetJumping()
{
	m_IsIdle = false;
	m_TimeThisJump = 0;
	m_IsJumping = true;
	m_Sprite.setTexture(m_JumpingTexture);
}

void Bob::SetAttacking()
{
	m_IsIdle = false;
	m_Attacking = true;
	m_Sprite.setTexture(m_AttackingTexture);
}

void Bob::SetWalking(const std::string& direction)
{
	m_IsIdle = false;

	if (direction == "right")
	{
		m_RightPressed = true;
	}
		
	if (direction == "left")
	{
		m_LeftPressed = true;
	}

	m_Sprite.setTexture(m_WalkingTexture);
}

bool Bob::HandleInput()
{
	m_JustJumped = false;

	if (Keyboard::isKeyPressed(Keyboard::F))
	{
		SetAttacking();
	}
	else
	{
		m_Attacking = false;
		SetIdle();
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		if (!m_IsJumping && !m_IsFalling)
		{
			SetJumping();
		}
	}
	else
	{
		if (!m_Attacking)
		{
			SetIdle();
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		if (m_Attacking) return false;
		SetWalking("left");
	}
	else
	{
		if (!m_Attacking)
		{
			m_LeftPressed = false;
			SetIdle();
		}
	}


	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		if (m_Attacking) return false;
		SetWalking("right");
	}
	else
	{
		if (!m_Attacking)
		{
			m_RightPressed = false;
			SetIdle();
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