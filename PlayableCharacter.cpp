// ReSharper disable CppClangTidyBugProneNarrowingConversions
// ReSharper disable CppClangTidyClangDiagnosticDoublePromotion
// ReSharper disable CppClangTidyClangDiagnosticImplicitFloatConversion
#include "PlayableCharacter.h"
#include "TextureCache.h"

constexpr float feetHeight = 1.0f;
constexpr float nextFootOffset = 2.0f;
constexpr float feetOffset = 3.0f;
constexpr float feetWidth = 6.0f;
constexpr float headOffset = 0.3f;
constexpr float leftOffset = 0.5f;
constexpr float rightOffset = 0.35f;

constexpr int numberZero = 0;
constexpr int numberOne = 1;
constexpr int numberTwo = 2;
constexpr int numberTwenty = 20;

void PlayableCharacter::Spawn(const Vector2f startPosition)
{
	m_PlayerPosition.x = startPosition.x;
	m_PlayerPosition.y = startPosition.y;

	// Move the sprite in to position
	m_PlayerSprite.setPosition(m_PlayerPosition);
}

void PlayableCharacter::Update(const float elapsedTime)
{
	UpdateJump(elapsedTime);
	UpdateBody(elapsedTime);
	UpdateGravity(elapsedTime);
	UpdateMoveDirection(elapsedTime);

	m_PlayerSprite.setPosition(m_PlayerPosition);
}

void PlayableCharacter::UpdateFeet(const FloatRect& rect)
{
	m_RectFeet.left = rect.left + feetHeight;
	m_RectFeet.top = rect.top + rect.height - feetHeight;
	m_RectFeet.width = rect.width - feetWidth;
	m_RectFeet.height = feetHeight;
}

void PlayableCharacter::UpdateHead(const FloatRect& rect)
{
	m_RectHead.left = rect.left;
	m_RectHead.top = rect.top + (rect.height * headOffset);
	m_RectHead.width = rect.width;
	m_RectHead.height = feetHeight;
}

void PlayableCharacter::UpdateRight(const FloatRect& rect)
{
	m_RectRight.left = rect.left + rect.width - nextFootOffset;
	m_RectRight.top = rect.top + rect.height * rightOffset;
	m_RectRight.width = feetHeight;
	m_RectRight.height = rect.height * headOffset;
}

void PlayableCharacter::UpdateLeft(const FloatRect& rect)
{
	m_RectLeft.left = rect.left;
	m_RectLeft.top = rect.top + rect.height * leftOffset;
	m_RectLeft.width = feetHeight;
	m_RectLeft.height = rect.height * headOffset;
}

void PlayableCharacter::UpdateBody(float elapsedTime)
{
	// Update the rect for all body parts
	const FloatRect rect = GetPosition();

	UpdateFeet(rect);
	UpdateHead(rect);
	UpdateRight(rect);
	UpdateLeft(rect);
}

void PlayableCharacter::UpdateGravity(const float elapsedTime)
{
	// Apply gravity
	if (m_PlayerIsFalling)
	{
		m_PlayerPosition.y += m_PlayerGravity * elapsedTime;
	}
}

// ===================== move direction =====================
// ==========================================================

void PlayableCharacter::UpdateState()
{
	if (m_PlayerIsJumping)
	{
		m_CurrentState = PlayerState::Jumping;
	}
	else if (m_PlayerIsFalling)
	{
		m_CurrentState = PlayerState::Falling;
	}
	else if (m_PlayerRightPressed || m_PlayerLeftPressed)
	{
		m_CurrentState = PlayerState::Walking;
	}
	else
	{
		m_CurrentState = PlayerState::Standing;
	}
}

void PlayableCharacter::UpdateJump(const float elapsedTime)
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

void PlayableCharacter::UpdateMoveDirection(const float elapsedTime)
{
	if (m_PlayerRightPressed)
	{
		UpdateMoveRight(elapsedTime);
	}

	if (m_PlayerLeftPressed)
	{
		UpdateMoveLeft(elapsedTime);
	}
}

void PlayableCharacter::UpdateMoveLeft(const float elapsedTime)
{
	m_PlayerPosition.x -= m_KnightSpeed * elapsedTime;
	m_PlayerSprite.setOrigin(m_PlayerSprite.getGlobalBounds().width + numberTwenty, numberZero);
	m_PlayerSprite.setScale(-numberOne, numberOne);
}

void PlayableCharacter::UpdateMoveRight(const float elapsedTime)
{
	if (m_PlayerRightPressed)
	{
		m_PlayerPosition.x += m_KnightSpeed * elapsedTime;
		m_PlayerSprite.setOrigin(m_PlayerSprite.getGlobalBounds().width - numberTwenty, numberZero);
		m_PlayerSprite.setScale(numberOne, numberOne);
	}
}

void PlayableCharacter::StopFalling(const float position)
{
	m_PlayerPosition.y = position - GetPosition().height;
	m_PlayerSprite.setPosition(m_PlayerPosition);
	m_PlayerIsFalling = false;
}

void PlayableCharacter::StopRight(const float position)
{
	m_PlayerPosition.x = position - m_PlayerSprite.getGlobalBounds().width;
	m_PlayerSprite.setPosition(m_PlayerPosition);
}

void PlayableCharacter::StopLeft(const float position)
{
	m_PlayerPosition.x = position + m_PlayerSprite.getGlobalBounds().width;
	m_PlayerSprite.setPosition(m_PlayerPosition);
}

void PlayableCharacter::StopJump()
{
	m_PlayerIsJumping = false;
	m_PlayerIsFalling = true;
}

// ===================== getters =====================
// ===================================================

Sprite PlayableCharacter::GetSprite()
{
	return m_PlayerSprite;
}

FloatRect PlayableCharacter::GetPosition() const
{
	return m_PlayerSprite.getGlobalBounds();
}

Vector2f PlayableCharacter::GetCenter() const
{
	return {
		m_PlayerPosition.x + m_PlayerSprite.getGlobalBounds().width / numberTwo,
		m_PlayerPosition.y + m_PlayerSprite.getGlobalBounds().height / numberTwo
	};
}

FloatRect PlayableCharacter::GetHead() const
{
	return m_RectHead;
}

FloatRect PlayableCharacter::GetFeet() const
{
	return m_RectFeet;
}

FloatRect PlayableCharacter::GetLeft() const
{
	return m_RectLeft;
}

FloatRect PlayableCharacter::GetRight() const
{
	return m_RectRight;
}
