#include "Thomas.h"
#include "TextureCache.h"

Thomas::Thomas()
{
	// Associate a texture with the sprite
	m_PlayerSprite = Sprite(TextureCache::GetTexture(
		"graphics/thomas.png"));

	m_JumpDuration = static_cast<float>(.45);
}

// A virtual function
bool Thomas::HandleInput()
{
	m_PlayerJustJumped = false;

	if (Keyboard::isKeyPressed(Keyboard::W))
	{

		// Start a jump if not already jumping
		// but only if standing on a block (not falling)
		if (!m_PlayerIsJumping && !m_PlayerIsFalling)
		{
			m_PlayerIsJumping = true;
			m_PlayerTimeJump = 0;
			m_PlayerJustJumped = true;
		}
	}
	else
	{
		m_PlayerIsJumping = false;
		m_PlayerIsFalling = true;

	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		m_PlayerLeftPressed = true;
	}
	else
	{
		m_PlayerLeftPressed = false;
	}


	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		m_PlayerRightPressed = true;
	}
	else
	{
		m_PlayerRightPressed = false;
	}

	return m_PlayerJustJumped;
}