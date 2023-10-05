#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class PlayableCharacter
{
protected:
	bool m_IsIdle = true;

	const int left = 0;
	const int bottom = -20;
	const int right = 75;
	const int top = 86;

	const int idle_Frames = 4;
	const int walking_Frames = 6;

	sf::Clock m_IdleClock;

	int m_IdleFrame = 0;

	// int m_WalkingFrame;

	// Of course we will need a sprite
	Sprite m_Sprite;

	Sprite m_WalkingSprite;

	// How long does a jump last
	float m_JumpDuration = 0;

	// Is character currently jumping or falling
	bool m_IsJumping = false;
	bool m_IsFalling = false;

	// Which directions is the character currently moving in
	bool m_LeftPressed = false;
	bool m_RightPressed = false;

	// How long has this jump lasted so far
	float m_TimeThisJump = 0;

	// Has the player just initialized a jump
	bool m_JustJumped = false;

	// Private variables and functions come next
private:
	// What is the gravity
	float m_Gravity = 0;

	// How fast is the character
	float m_Speed = 240;

	// Where is the player
	Vector2f m_Position;

	// Where are the characters various body parts?
	FloatRect m_Feet;
	FloatRect m_Head;
	FloatRect m_Right;
	FloatRect m_Left;

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
	FloatRect GetPosition();

	// A rectangle representing the position of different parts of the sprite
	FloatRect GetFeet();
	FloatRect GetHead();
	FloatRect GetRight();
	FloatRect GetLeft();

	// Send a copy of the sprite to main
	Sprite GetSprite();

	// Make the character stand firm
	void StopFalling(float position);
	void StopRight(float position);
	void StopLeft(float position);
	void StopJump();

	// Where is the center of the character
	Vector2f GetCenter();

	// We will call this function once every frame
	void Update(float elapsed_time);
};