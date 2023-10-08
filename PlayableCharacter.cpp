// ReSharper disable CppClangTidyBugProneNarrowingConversions
// ReSharper disable CppClangTidyClangDiagnosticDoublePromotion
// ReSharper disable CppClangTidyClangDiagnosticImplicitFloatConversion

#include "PlayableCharacter.h"
#include "TextureCache.h"

void PlayableCharacter::Spawn(const Vector2f start_position)
{
	// Place the player at the starting point
	m_PlayerPosition.x = start_position.x;
	m_PlayerPosition.y = start_position.y;

	// Move the sprite in to position
	m_PlayerSprite.setPosition(m_PlayerPosition);

}

void PlayableCharacter::Update(const float elapsed_time)
{
	if (m_PlayerRightPressed)
	{
		m_PlayerPosition.x += m_KnightSpeed * elapsed_time;
	}

	if (m_PlayerLeftPressed)
	{
		m_PlayerPosition.x -= m_KnightSpeed * elapsed_time;
	}

	UpdateJump(elapsed_time);
	UpdateBody(elapsed_time);
	UpdateGravity(elapsed_time);
	
	// Move the sprite into position
	m_PlayerSprite.setPosition(m_PlayerPosition);
}

void PlayableCharacter::UpdateJump(const float elapsed_time)
{
	if (m_PlayerIsJumping)
	{
		// Update how long the jump has been going
		m_PlayerTimeJump += elapsed_time;

		// Is the jump going upwards
		if (m_PlayerTimeJump < m_JumpDuration)
		{
			// Move up at twice gravity
			m_PlayerPosition.y -= m_PlayerGravity * 2 * elapsed_time;
		}
		else
		{
			m_PlayerIsJumping = false;
			m_PlayerIsFalling = true;
		}
	}
}

void PlayableCharacter::UpdateBody(float elapsed_time)
{
	// Update the rect for all body parts
	const FloatRect rect = GetPosition();

	// Feet
	m_RectFeet.left = rect.left + 3;
	m_RectFeet.top = rect.top + rect.height - 1;
	m_RectFeet.width = rect.width - 6;
	m_RectFeet.height = 1;

	// Head
	m_RectHead.left = rect.left;
	m_RectHead.top = rect.top + (rect.height * .3);
	m_RectHead.width = rect.width;
	m_RectHead.height = 1;

	// Right
	m_RectRight.left = rect.left + rect.width - 2;
	m_RectRight.top = rect.top + rect.height * .35;
	m_RectRight.width = 1;
	m_RectRight.height = rect.height * .3;

	// Left
	m_RectLeft.left = rect.left;
	m_RectLeft.top = rect.top + rect.height * .5;
	m_RectLeft.width = 1;
	m_RectLeft.height = rect.height * .3;
}

void PlayableCharacter::UpdateGravity(const float elapsed_time)
{
	// Apply gravity
	if (m_PlayerIsFalling)
	{
		m_PlayerPosition.y += m_PlayerGravity * elapsed_time;
	}
}

FloatRect PlayableCharacter::GetPosition() const
{
	return m_PlayerSprite.getGlobalBounds();
}

Vector2f PlayableCharacter::GetCenter() const
{
	return {
		m_PlayerPosition.x + m_PlayerSprite.getGlobalBounds().width / 2,
		m_PlayerPosition.y + m_PlayerSprite.getGlobalBounds().height / 2
	};
}

FloatRect PlayableCharacter::GetFeet() const
{
	return m_RectFeet;
}

FloatRect PlayableCharacter::GetHead() const
{
	return m_RectHead;
}

FloatRect PlayableCharacter::GetLeft() const
{
	return m_RectLeft;
}

FloatRect PlayableCharacter::GetRight() const
{
	return m_RectRight;
}

Sprite PlayableCharacter::GetSprite()
{
	return m_PlayerSprite;
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
	// Stop a jump early 
	m_PlayerIsJumping = false;
	m_PlayerIsFalling = true;
}

