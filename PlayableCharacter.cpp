#include "PlayableCharacter.h"

#include "TextureCache.h"


void PlayableCharacter::Spawn(const Vector2f start_position, const float gravity)
{
	// Place the player at the starting point
	m_PlayerPosition.x = start_position.x;
	m_PlayerPosition.y = start_position.y;

	// Initialize the gravity
	m_PlayerGravity = gravity;

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


	// Handle Jumping
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


	// Apply gravity
	if (m_PlayerIsFalling)
	{
		m_PlayerPosition.y += m_PlayerGravity * elapsed_time;
	}

	// Update the rect for all body parts
	const FloatRect rect = GetPosition();


	// Feet
	m_Feet.left = rect.left + 3;
	m_Feet.top = rect.top + rect.height - 1;
	m_Feet.width = rect.width - 6;
	m_Feet.height = 1;

	// Head
	m_Head.left = rect.left;
	m_Head.top = rect.top + (rect.height * .3);
	m_Head.width = rect.width;
	m_Head.height = 1;

	// Right
	m_Right.left = rect.left + rect.width - 2;
	m_Right.top = rect.top + rect.height * .35;
	m_Right.width = 1;
	m_Right.height = rect.height * .3;

	// Left
	m_Left.left = rect.left;
	m_Left.top = rect.top + rect.height * .5;
	m_Left.width = 1;
	m_Left.height = rect.height * .3;

	// Move the sprite into position
	m_PlayerSprite.setPosition(m_PlayerPosition);

}

FloatRect PlayableCharacter::GetPosition() const
{
	return m_PlayerSprite.getGlobalBounds();
}

Vector2f PlayableCharacter::GetCenter() const
{
	return Vector2f(
		m_PlayerPosition.x + m_PlayerSprite.getGlobalBounds().width / 2,
		m_PlayerPosition.y + m_PlayerSprite.getGlobalBounds().height / 2
	);
}

FloatRect PlayableCharacter::GetFeet() const
{
	return m_Feet;
}

FloatRect PlayableCharacter::GetHead() const
{
	return m_Head;
}

FloatRect PlayableCharacter::GetLeft() const
{
	return m_Left;
}

FloatRect PlayableCharacter::GetRight() const
{
	return m_Right;
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


