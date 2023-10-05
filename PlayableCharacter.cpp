#include "PlayableCharacter.h"

#include "TextureCache.h"


void PlayableCharacter::Spawn(Vector2f start_position, float gravity)
{
	// Place the player at the starting point
	m_Position.x = start_position.x;
	m_Position.y = start_position.y;

	// Initialize the gravity
	m_Gravity = gravity;

	// Move the sprite in to position
	m_Sprite.setPosition(m_Position);

}

void PlayableCharacter::Update(float elapsed_time)
{

	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsed_time;
	}

	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsed_time;
	}


	// Handle Jumping
	if (m_IsJumping)
	{
		// Update how long the jump has been going
		m_TimeThisJump += elapsed_time;

		// Is the jump going upwards
		if (m_TimeThisJump < m_JumpDuration)
		{
			// Move up at twice gravity
			m_Position.y -= m_Gravity * 2 * elapsed_time;
		}
		else
		{
			m_IsJumping = false;
			m_IsFalling = true;
		}

	}


	// Apply gravity
	if (m_IsFalling)
	{
		m_Position.y += m_Gravity * elapsed_time;
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
	m_Sprite.setPosition(m_Position);

}

FloatRect PlayableCharacter::GetPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f PlayableCharacter::GetCenter()
{
	return Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
	);
}

FloatRect PlayableCharacter::GetFeet()
{
	return m_Feet;
}

FloatRect PlayableCharacter::GetHead()
{
	return m_Head;
}

FloatRect PlayableCharacter::GetLeft()
{
	return m_Left;
}

FloatRect PlayableCharacter::GetRight()
{
	return m_Right;
}

Sprite PlayableCharacter::GetSprite()
{
	return m_Sprite;
}



void PlayableCharacter::StopFalling(float position)
{
	m_Position.y = position - GetPosition().height;
	m_Sprite.setPosition(m_Position);
	m_IsFalling = false;
}

void PlayableCharacter::StopRight(float position)
{

	m_Position.x = position - m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::StopLeft(float position)
{
	m_Position.x = position + m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::StopJump()
{
	// Stop a jump early 
	m_IsJumping = false;
	m_IsFalling = true;
}


