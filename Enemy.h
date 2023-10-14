#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy   // NOLINT(cppcoreguidelines-special-member-functions)
{
protected:
	sf::Clock m_EnemyIdleClock;

	int m_EnemyIdleFrame = 0;
	int m_EnemyAttackFrames = 5;
	int m_EnemyWalkingFrames = 0;

	Sprite m_EnemySprite;
	Vector2f m_EnemyPosition;

	Texture m_EnemyTexture;
	Texture m_EnemyIdleTexture;
	Texture m_EnemyWalkingTexture;
	Texture m_EnemyAttackTexture;
	Texture m_EnemyDeathTexture;
	Texture m_EnemyHitTexture;

	bool m_EnemyIsIdle = true;
	bool m_EnemyIsPatrolling = false;
	bool m_EnemyIsDead = false;
	bool m_EnemyIsAttacking = false;
	bool m_EnemyIsFalling = false;

	float m_EnemySpeed = 12.f;
	float m_EnemyAttackSpeed = 1.0f;
	float m_EnemyGravity = 200.f;

	FloatRect m_EnemyFeetPosition;

	int m_HitPoints = 0;
	int m_MaxHitPoints = 0;
	int m_Damage = 0;
	bool m_IsAlive = true;

private:
	

public:
	virtual ~Enemy() = default;

	bool SpawnEnemy(Vector2f enemyStartPosition, float gravity);

	void UpdateEnemy(const float elapsedTime);

	void UpdatePatrolAnimation(const float elapsedTime);

	void UpdateAttackAnimation(const float elapsedTime);

	Sprite GetEnemySprite();

	FloatRect GetEnemyFeet() const;

	FloatRect GetEnemyPosition() const;

	void StopEnemyFalling(float top);
	void SetEnemyPosition(float x, float y);

	void EngageCombat();

	void DisengageCombat();
	void SetPatrolState(bool isPatrolling, bool isAttacking);
	void SetAttackState(bool isAttacking, bool isPatrolling);

	void UpdateTexture();

	void StartPatrol();

	void StopPatrol();

	virtual void TakeDamage(int field) = 0;
};
