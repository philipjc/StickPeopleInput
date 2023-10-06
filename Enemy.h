#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy   // NOLINT(cppcoreguidelines-special-member-functions)
{
protected:
	sf::Clock m_EnemyIdleClock;

	int m_EnemyIdleFrame = 1;
	int m_EnemyAttackFrames = 5;

	Sprite m_EnemySprite;
	Vector2f m_EnemyPosition;

	Texture m_EnemyTexture;
	Texture m_EnemyAttackTexture;
	Texture m_EnemyDeathTexture;
	Texture m_EnemyHitTexture;

	bool m_EnemyIsIdle = true;
	bool m_EnemyIsPatrolling = false;
	bool m_EnemyIsDead = false;
	bool m_EnemyIsAttacking = false;
	bool m_EnemyIsFalling = false;

	float m_EnemySpeed = 15.5f;
	float m_EnemyAttackSpeed = 1.0f;
	float m_EnemyGravity = 200.f;

	FloatRect m_EnemyFeetPosition;

	private:

public:
	virtual ~Enemy() = default;

	bool SpawnEnemy(Vector2f enemy_start_position, float gravity);

	void UpdateEnemy(const float elapsed_time);

	Sprite GetEnemySprite();

	FloatRect GetEnemyFeet() const;

	FloatRect GetEnemyPosition() const;

	void StopEnemyFalling(float top);
};
