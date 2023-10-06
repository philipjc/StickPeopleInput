#pragma
#include "Engine.h"
#include "Enemy.h"


bool Enemy::SpawnEnemy(Vector2f enemy_start_position, float gravity)
{
	m_EnemyAttackTexture = TextureCache::GetTexture("graphics/skeleton/attack_1.png");
	m_EnemySprite = Sprite();
	m_EnemySprite.setTexture(m_EnemyAttackTexture);

	// Face left
	m_EnemySprite.setScale(-1, 1);

	m_EnemyPosition.x = 500.f;
	m_EnemyPosition.y = 0.f;
	m_EnemyIsFalling = true;
	m_EnemyIsPatrolling = true;

	return true;
}

Sprite Enemy::GetEnemySprite()
{
	return m_EnemySprite;
}

FloatRect Enemy::GetEnemyPosition() const
{
	return m_EnemySprite.getGlobalBounds();
}

void Enemy::UpdateEnemy(const float elapsed_time)
{
	if (m_EnemyIsPatrolling)
	{
		m_EnemyPosition.x -= m_EnemySpeed * elapsed_time;

		// Animate attacking
		if (m_EnemyIdleClock.getElapsedTime().asSeconds() > 0.1f)
		{
			if (m_EnemyIdleFrame == m_EnemyAttackFrames)
			{
				m_EnemyIdleFrame = 0;
			}

			m_EnemySprite.setTextureRect(sf::IntRect(10, 30, 80, 90));

			m_EnemyIdleFrame++;

			m_EnemyIdleClock.restart();
		}
	}

	if (m_EnemyIsFalling)
	{
		m_EnemyPosition.y += m_EnemyGravity * elapsed_time;
	}

	// Find feet
	// Update the rect for all body parts
	const FloatRect rect = GetEnemyPosition();


	// Feet
	m_EnemyFeetPosition.left = rect.left + 3;
	m_EnemyFeetPosition.top = rect.top + rect.height - 1;
	m_EnemyFeetPosition.width = rect.width - 6;
	m_EnemyFeetPosition.height = 1;

	m_EnemySprite.setPosition(m_EnemyPosition);
	
}

FloatRect Enemy::GetEnemyFeet() const
{
	return m_EnemyFeetPosition;
}

void Enemy::StopEnemyFalling(const float top)
{
	m_EnemyPosition.y = top - GetEnemyPosition().height;
	m_EnemySprite.setPosition(m_EnemyPosition);
	m_EnemyIsFalling = false;
}
