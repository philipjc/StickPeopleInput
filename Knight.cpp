#include "Knight.h"
#include "TextureCache.h"
#include <iostream>


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
	m_AnimIdleFrameCount = 0;

}

void Knight::UpdateAttackAnimation()
{
	// run super and pass texture when game evolves
	if (!m_IsIdle && m_PlayerAttacking)
	{
		m_PlayerSprite.setTexture(m_AttackingTexture);

		// Animate attacking
		if (m_PlayerIdleClock.getElapsedTime().asSeconds() > 0.1f)
		{
			if (m_AnimIdleFrameCount == m_AttackingFrames)
			{
				m_AnimIdleFrameCount = 0;
			}

			m_PlayerSprite.setTextureRect(sf::IntRect(m_AnimIdleFrameCount * 80, m_Bottom-10, 80, m_Top));

			m_AnimIdleFrameCount++;

			m_PlayerIdleClock.restart();
		}
	}
}

void Knight::UpdateWalkAnimation()
{
	if (!m_IsIdle && !m_PlayerAttacking)
	{
		m_PlayerSprite.setTexture(m_WalkingTexture);

		// Animate walking
		if (m_PlayerIdleClock.getElapsedTime().asSeconds() > 0.1f)
		{
			if (m_AnimIdleFrameCount == m_WalkingFrames)
			{
				m_AnimIdleFrameCount = 0;
			}

			m_PlayerSprite.setTextureRect(sf::IntRect(m_AnimIdleFrameCount * 70, m_Bottom - 20, 70, m_Top));

			m_AnimIdleFrameCount++;

			m_PlayerIdleClock.restart();
		}
	}
}

void Knight::UpdateIdleAnimation()
{
	if (m_IsIdle && !m_PlayerAttacking)
	{
		// Animate idle
		m_PlayerSprite.setTexture(m_IdleTexture);
		m_PlayerSprite.setTextureRect(sf::IntRect(70, m_Bottom, 70, m_Top));
	}
}

bool Knight::HandleInput()
{
	// Event State changes
	// ===================================

	if (Keyboard::isKeyPressed(Keyboard::F))
	{
		m_IsIdle = false;
		m_PlayerAttacking = true;
	}
	else
	{
		m_IsIdle = true;
		m_PlayerAttacking = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::G))
	{
		m_AbilityManager.triggerAbility(0);
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

	if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Right))
	{
		m_IsIdle = false;

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			m_PlayerLeftPressed = true;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			m_PlayerRightPressed = true;
		}
	}
	else
	{
		if (!m_PlayerAttacking)
		{
			m_IsIdle = true;
			m_PlayerLeftPressed = false;
			m_PlayerRightPressed = false;
			m_PlayerAttacking = false;
		}
	}


	// Respond to Event State changes
	// ===================================

	UpdateIdleAnimation();

	UpdateAttackAnimation();

	UpdateWalkAnimation();

	return m_PlayerJustJumped;
}
