#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class PlayableCharacter  // NOLINT(cppcoreguidelines-special-member-functions)
{
protected:
	bool m_IsIdle = true;

	const int m_Left = 0;
	const int m_Bottom = -20;
	const int m_Right = 75;
	const int m_Top = 86;

	const int m_IdleFrames = 4;
	const int m_WalkingFrames = 6;
	const int m_AttackingFrames = 5;

	sf::Clock m_IdleClock;

	int m_IdleFrame = 0;

	// int m_WalkingFrame;

	// Of course we will need a sprite
	Sprite m_PlayerSprite;

	Texture m_IdleTexture;

	Texture m_WalkingTexture;

	Texture m_JumpingTexture;

	Texture m_FallingTexture;

	Texture m_AttackingTexture;

	Texture m_PlayerDeadTexture;

	// How long does a jump last
	float m_JumpDuration = 0;

	// Is character currently jumping or falling
	bool m_PlayerIsJumping = false;
	bool m_PlayerIsFalling = false;

	// Which directions is the character currently moving in
	bool m_PlayerLeftPressed = false;
	bool m_PlayerRightPressed = false;

	// How long has this jump lasted so far
	float m_PlayerTimeJump = 0;

	// Has the player just initialized a jump
	bool m_PlayerJustJumped = false;

	bool m_PlayerAttacking = false;

	// Private variables and functions come next
private:
	// What is the gravity
	float m_PlayerGravity = 0;

	// How fast is the character
	float m_KnightSpeed = 230;

	// Where is the player
	Vector2f m_PlayerPosition;

	// Where are the characters various body parts?
	FloatRect m_RectFeet;
	FloatRect m_RectHead;
	FloatRect m_RectRight;
	FloatRect m_RectLeft;

	// And a texture
	Texture m_Texture;

	// All our public functions will come next
public:
	virtual ~PlayableCharacter() = default;

	void Spawn(Vector2f start_position, float gravity);

	// This is a pure virtual function
	bool virtual HandleInput() = 0;
	// This class is now abstract and cannot be instantiated
	// Where is the player
	FloatRect GetPosition() const;

	// A rectangle representing the position of different parts of the sprite
	FloatRect GetFeet() const;
	FloatRect GetHead() const;
	FloatRect GetLeft() const;
	FloatRect GetRight() const;
	
	// Send a copy of the sprite to main
	Sprite GetSprite();

	// Make the character stand firm
	void StopFalling(float position);
	void StopRight(float position);
	void StopLeft(float position);
	void StopJump();

	// Where is the center of the character
	Vector2f GetCenter() const;


	// We will call this function once every frame
	void Update(float elapsed_time);

};