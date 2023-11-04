#include "PlayerCharacter.h"
#include "TextureCache.h"
#include "AbilityManager.h"
#include "Slash.h"

#include <iostream>

// ===================== public ======================
constexpr int numberZero = 0;
constexpr int numberOne = 1;
constexpr int numberTwo = 2;

constexpr float feetHeight = 1.0f;
constexpr float feetWidth = 6.0f;
constexpr float headOffset = 0.3f;
constexpr float leftOffset = 0.5f;
constexpr float rightOffset = 0.35f;
constexpr float nextFootOffset = 2.0f;

void PlayerCharacter::UpdateAttackAnimation()
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

			m_PlayerSprite.setTextureRect(sf::IntRect(m_AnimIdleFrameCount * 80, m_Bottom - 10, 80, m_Top));

			m_AnimIdleFrameCount++;

			m_PlayerIdleClock.restart();
		}
	}
}

void PlayerCharacter::UpdateWalkAnimation()
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

void PlayerCharacter::UpdateMoveLeft(const float elapsedTime)
{
	if (m_PlayerLeftPressed)
	{
		m_PlayerPosition.x -= (m_playerSpeed * elapsedTime);
		m_PlayerSprite.setOrigin(m_PlayerSprite.getGlobalBounds().width / numberTwo, numberZero);
		// Flip the sprite
		m_PlayerSprite.setScale(-numberOne, numberOne);
	}
	
}

void PlayerCharacter::UpdateMoveRight(const float elapsedTime)
{
	if (m_PlayerRightPressed)
	{
		m_PlayerPosition.x += m_playerSpeed * elapsedTime;
		m_PlayerSprite.setOrigin(m_PlayerSprite.getGlobalBounds().width / numberTwo, numberZero);
		// Flip the sprite
		m_PlayerSprite.setScale(numberOne, numberOne);
	}
}


void PlayerCharacter::UpdateIdleAnimation()
{
	if (m_IsIdle && !m_PlayerAttacking)
	{
		// Animate idle
		m_PlayerSprite.setTexture(m_IdleTexture);
		m_PlayerSprite.setTextureRect(sf::IntRect(70, m_Bottom, 70, m_Top));
	}
}

void PlayerCharacter::UpdateSkillAnimation()
{
	if (m_PlayerSkillActive)
	{
		m_PlayerSprite.setTexture(m_AttackingSlashTexture);

		// Animate attacking
		m_PlayerSprite.setTextureRect(sf::IntRect(220, m_Bottom, 107, m_Top));
	}

}

void PlayerCharacter::Spawn(const Vector2f startPosition)
{
	m_PlayerPosition.x = startPosition.x;
	m_PlayerPosition.y = startPosition.y;

	// Move the sprite in to position
	m_PlayerSprite.setPosition(m_PlayerPosition);

	// Smart pointer -> Cpp 11+ Garbage collection
	m_AbilityManager.AddAbility(std::make_unique<Slash>());
}

void PlayerCharacter::Update(const float elapsedTime)
{
	UpdateJump(elapsedTime);
	UpdateAttributes(elapsedTime);
	UpdateBody(elapsedTime);
	UpdateGravity(elapsedTime);
	UpdateIdleAnimation();
	UpdateAttackAnimation();
	UpdateWalkAnimation();
	UpdateSkillAnimation();
	UpdateMoveLeft(elapsedTime);
	UpdateMoveRight(elapsedTime);

	m_PlayerSprite.setPosition(m_PlayerPosition);
}

void PlayerCharacter::UpdateFeet(const FloatRect& rect)
{
	m_RectFeet.left = rect.left + feetHeight;
	m_RectFeet.top = rect.top + rect.height - feetHeight;
	m_RectFeet.width = rect.width - feetWidth;
	m_RectFeet.height = feetHeight;
}

void PlayerCharacter::UpdateHead(const FloatRect& rect)
{
	m_RectHead.left = rect.left;
	m_RectHead.top = rect.top + (rect.height * headOffset);
	m_RectHead.width = rect.width;
	m_RectHead.height = feetHeight;
}

void PlayerCharacter::UpdateRight(const FloatRect& rect)
{
	m_RectRight.left = rect.left + rect.width - nextFootOffset;
	m_RectRight.top = rect.top + rect.height * rightOffset;
	m_RectRight.width = feetHeight;
	m_RectRight.height = rect.height * headOffset;
}

void PlayerCharacter::UpdateLeft(const FloatRect& rect)
{
	m_RectLeft.left = rect.left;
	m_RectLeft.top = rect.top + rect.height * leftOffset;
	m_RectLeft.width = feetHeight;
	m_RectLeft.height = rect.height * headOffset;
}

void PlayerCharacter::UpdateBody(float elapsedTime)
{
	// Update the rect for all body parts
	const FloatRect rect = GetPosition();

	UpdateFeet(rect);
	UpdateHead(rect);
	UpdateRight(rect);
	UpdateLeft(rect);
}



void PlayerCharacter::UpdateGravity(const float elapsedTime)
{
	// Apply gravity
	if (m_PlayerIsFalling)
	{
		m_PlayerPosition.y += m_PlayerGravity * elapsedTime;
	}
}

void PlayerCharacter::UpdateAttributes(float elapsedTime)
{
	const sf::Time elapsed = m_PlayerAttributeClock.getElapsedTime();

	if (elapsed.asSeconds() >= 5.0f && m_PlayerStamina <= 8) {
		m_PlayerStamina += 2;
		std::cout << "Stamina increased to: " << m_PlayerStamina << std::endl;
		m_PlayerAttributeClock.restart();
	}
}

void PlayerCharacter::UpdateJump(const float elapsedTime)
{
	if (m_CurrentState == PlayerState::Jumping)
	{
		// Update how long the jump has been going
		m_PlayerTimeJump += elapsedTime;

		// Still moving up?
		if (m_PlayerTimeJump < m_JumpDuration)
		{
			// Move up at twice gravity (force of player jump power)
			m_PlayerPosition.y -= m_PlayerGravity * numberTwo * elapsedTime;
		}
		else
		{
			m_PlayerIsJumping = false;
			m_PlayerIsFalling = true;
		}
	}
}


void PlayerCharacter::StopFalling(const float position)
{
	m_PlayerPosition.y = position - GetPosition().height;
	m_PlayerSprite.setPosition(m_PlayerPosition);
	m_PlayerIsFalling = false;
}

void PlayerCharacter::StopRight(const float position)
{
	m_PlayerPosition.x = position - m_PlayerSprite.getGlobalBounds().width;
	m_PlayerSprite.setPosition(m_PlayerPosition);
}

void PlayerCharacter::StopLeft(const float position)
{
	m_PlayerPosition.x = position + m_PlayerSprite.getGlobalBounds().width;
	m_PlayerSprite.setPosition(m_PlayerPosition);
}

void PlayerCharacter::StopJump()
{
	m_PlayerIsJumping = false;
	m_PlayerIsFalling = true;
}

bool PlayerCharacter::HandleInput()
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

		// Detect a single key press (in this case, the space key)
		if (!m_gPressed && m_PlayerStamina >= 2)
		{

			m_PlayerSkillActive = true;
			m_PlayerStamina -= 2;

			std::cout << "Slash!!!" << std::endl;

			std::cout << "Stamina decreased to: " << m_PlayerStamina << std::endl;

			m_AbilityManager.TriggerAbility(0);
			m_gPressed = true;

		}
	}
	else
	{
		m_gPressed = false;
		m_PlayerSkillActive = false;
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

	return m_PlayerJustJumped;
}

// ===================== private =====================
// ===================== getters =====================
// ===================================================

Sprite PlayerCharacter::GetSprite()
{
	return m_PlayerSprite;
}

FloatRect PlayerCharacter::GetPosition() const
{
	return m_PlayerSprite.getGlobalBounds();
}

Vector2f PlayerCharacter::GetCenter() const
{
	return {
		m_PlayerPosition.x + m_PlayerSprite.getGlobalBounds().width / numberTwo,
		m_PlayerPosition.y + m_PlayerSprite.getGlobalBounds().height / numberTwo
	};
}

FloatRect PlayerCharacter::GetHead() const
{
	return m_RectHead;
}

FloatRect PlayerCharacter::GetFeet() const
{
	return m_RectFeet;
}

FloatRect PlayerCharacter::GetLeft() const
{
	return m_RectLeft;
}

FloatRect PlayerCharacter::GetRight() const
{
	return m_RectRight;
}

