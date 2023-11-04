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

