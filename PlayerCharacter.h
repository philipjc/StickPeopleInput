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

class PlayerCharacter  // NOLINT(cppcoreguidelines-special-member-functions)
{
protected:

	sf::Clock m_PlayerIdleClock;
	sf::Clock m_PlayerAttributeClock;

	bool m_IsIdle = true;
	int m_AnimIdleFrameCount = 0;

	int m_Top = 86;
	int m_Left = 0;
	int m_Bottom = 0;
	int m_Right = 75;

	Sprite m_PlayerSprite = Sprite();

	Texture m_IdleTexture;
	Texture m_WalkingTexture;
	Texture m_RunningTexture;
	Texture m_JumpingTexture;
	Texture m_FallingTexture;
	Texture m_AttackingTexture;
	Texture m_DefendingTexture;
	Texture m_PlayerDeadTexture;
	Texture m_AttackingSlashTexture;
	Texture m_TakeDamageTexture;

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
	int m_AttackingFrames = 5;

	bool m_PlayerAttacking = false;

	bool m_PlayerSkillActive = false;

	int m_WalkingFrames = 8;

	int m_PlayerStamina = 2;

	PlayerState m_CurrentState = PlayerState::Standing;

	// Ability Manager
	AbilityManager m_AbilityManager;

private:
	float m_PlayerGravity = 240;

	Vector2f m_PlayerPosition;

	// Where are the characters various body parts?
	FloatRect m_RectFeet;
	FloatRect m_RectHead;
	FloatRect m_RectRight;
	FloatRect m_RectLeft;

	// And a texture
	Texture m_PlayerTexture;

public:

	virtual ~PlayerCharacter() = default;

	void Spawn(Vector2f startPosition);
	void UpdateGravity(float elapsedTime);
	void UpdateAttributes(float elapsedTime);

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
	void UpdateJump(float elapsedTime);
	void UpdateBody(float elapsedTime);
	void UpdateMoveLeft(float elapsedTime);
	void UpdateMoveRight(float elapsedTime);

	void UpdateFeet(const FloatRect& rect);
	void UpdateHead(const FloatRect& rect);
	void UpdateRight(const FloatRect& rect);
	void UpdateLeft(const FloatRect& rect);
	
	void UpdateIdleAnimation();
	void UpdateAttackAnimation();
	void UpdateWalkAnimation();
	void UpdateSkillAnimation();

	bool HandleInput();

	// variables
	bool m_gPressed = false;
	float m_playerSpeed = 250.f;

};