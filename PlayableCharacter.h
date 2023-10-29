#pragma once
#include <SFML/Graphics.hpp>
#include "AbilityManager.h"

using namespace sf;

// forward declares
enum class PlayerState;

// ====================
enum class PlayerState
{
	Standing,
	Walking,
	Jumping,
	Falling
};

class PlayableCharacter  // NOLINT(cppcoreguidelines-special-member-functions)
{
protected:

	sf::Clock m_PlayerIdleClock;

	bool m_IsIdle = true;
	int m_AnimIdleFrameCount = 0;

	const int m_Top = 86;
	const int m_Left = 0;
	const int m_Bottom = 0;
	const int m_Right = 75;

	Sprite m_PlayerSprite;

	Texture m_IdleTexture;
	Texture m_WalkingTexture;
	Texture m_JumpingTexture;
	Texture m_FallingTexture;
	Texture m_AttackingTexture;
	Texture m_PlayerDeadTexture;

	// Has the player just initialized a jump
	bool m_PlayerJustJumped = false;
	float m_JumpDuration = 0;
	float m_PlayerTimeJump = 0;

	// Is character currently jumping or falling
	bool m_PlayerIsJumping = false;
	bool m_PlayerIsFalling = false;

	// Which directions is the character currently moving in
	bool m_PlayerLeftPressed = false;
	bool m_PlayerRightPressed = false;

	// Is the character currently attacking
	bool m_PlayerAttacking = false;

	PlayerState m_CurrentState = PlayerState::Standing;

	// Ability Manager
	AbilityManager m_AbilityManager;


private:
	float m_PlayerGravity = 240;

	float m_KnightSpeed = 230;

	Vector2f m_PlayerPosition;

	// Where are the characters various body parts?
	FloatRect m_RectFeet;
	FloatRect m_RectHead;
	FloatRect m_RectRight;
	FloatRect m_RectLeft;

	// And a texture
	Texture m_PlayerTexture;
	
public:

	// Class is abstract and cannot be instantiated
	virtual ~PlayableCharacter() = default;

	void Spawn(Vector2f startPosition);
	void UpdateMoveLeft(float elapsedTime);
	void UpdateMoveDirection(float elapsedTime);
	void UpdateMoveRight(float elapsedTime);
	void UpdateGravity(float elapsedTime);
	void UpdateState();

	// These are pure virtual function (overridden)
	void virtual UpdateAttackAnimation() = 0;
	void virtual UpdateWalkAnimation() = 0;
	void virtual UpdateIdleAnimation() = 0;
	bool virtual HandleInput() = 0;

	// Player location
	FloatRect GetPosition() const;

	// Positions of different parts of the sprite
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

	// Called once every frame
	void Update(float elapsedTime);
	void UpdateFeet(const FloatRect& rect);
	void UpdateHead(const FloatRect& rect);
	void UpdateRight(const FloatRect& rect);
	void UpdateLeft(const FloatRect& rect);
	void UpdateJump(float elapsedTime);
	void UpdateBody(float elapsedTime);
};