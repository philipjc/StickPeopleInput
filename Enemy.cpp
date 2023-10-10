#include "Engine.h"
#include "Enemy.h"
#include "Knight.h"

bool Enemy::SpawnEnemy(Vector2f enemyStartPosition, float gravity)
{
	m_EnemyTexture = TextureCache::GetTexture("graphics/skeleton/idle.png");
	m_EnemyDeathTexture = TextureCache::GetTexture("graphics/skeleton/dead.png");
	m_EnemyAttackTexture = TextureCache::GetTexture("graphics/skeleton/attack_1.png");

	m_EnemySprite = Sprite();
	m_EnemySprite.setTexture(m_EnemyTexture);

	// Face left
	m_EnemySprite.setScale(-1, 1);

	m_EnemyPosition.x = 500.f;
	m_EnemyPosition.y = 0.f;
	m_EnemyIsFalling = true;
	m_EnemyIsPatrolling = true;

	Enemy::StartPatrol();

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

void Enemy::UpdateEnemy(const float elapsedTime)
{
	UpdatePatrolAnimation(elapsedTime);
	UpdateAttackAnimation(elapsedTime);

	if (m_EnemyIsFalling)
	{
		m_EnemyPosition.y += m_EnemyGravity * elapsedTime;
	}

	// Find feet
	// Update the rect for all body parts
	const FloatRect rect = GetEnemyPosition();

	// Feet
	if (!m_EnemyIsAttacking)
	{
		m_EnemyFeetPosition.left = rect.left + 3;
		m_EnemyFeetPosition.top = rect.top + rect.height - 1;
		m_EnemyFeetPosition.width = rect.width - 6;
		m_EnemyFeetPosition.height = 1;
		m_EnemySprite.setPosition(m_EnemyPosition);

	}

	
}

void Enemy::UpdatePatrolAnimation(const float elapsedTime)
{
	if (m_EnemyIsPatrolling)
	{
		m_EnemyPosition.x -= m_EnemySpeed * elapsedTime;
		// Animate patrol
		if (m_EnemyIdleClock.getElapsedTime().asSeconds() > 0.1f)
		{
			if (m_EnemyIdleFrame == m_EnemyWalkingFrames)
			{
				m_EnemyIdleFrame = 0;
				m_EnemySprite.setTextureRect(sf::IntRect(0, 30, 128, 90));
			}
			else
			{
				m_EnemySprite.setTextureRect(sf::IntRect(m_EnemyIdleFrame * 128, 30, 128, 90));
			}

			m_EnemyIdleFrame++;
			m_EnemyIdleClock.restart();
			m_EnemySprite.setPosition(m_EnemyPosition);

			const FloatRect rect = GetEnemyPosition();
			m_EnemyFeetPosition.left = rect.left + 1;
		}
	}
}

void Enemy::UpdateAttackAnimation(const float elapsedTime)
{
	if (m_EnemyIsAttacking)
	{
		if (m_EnemyIdleClock.getElapsedTime().asSeconds() > 0.1f)
		{
			if (m_EnemyIdleFrame == 4)
			{
				m_EnemyIdleFrame = 0;
				m_EnemySprite.setTextureRect(sf::IntRect(0, 30, 80, 90));
			}

			if (m_EnemyIdleFrame == 1)
			{
				m_EnemySprite.setTextureRect(sf::IntRect(120, 30, 80, 90));
			}

			if (m_EnemyIdleFrame == 2)
			{
				m_EnemySprite.setTextureRect(sf::IntRect(260, 30, 80, 90));
			}

			if (m_EnemyIdleFrame == 3)
			{
				m_EnemySprite.setTextureRect(sf::IntRect(410, 30, 80, 90));
			}

			if (m_EnemyIdleFrame == 4)
			{
				m_EnemySprite.setTextureRect(sf::IntRect(540, 30, 80, 90));
			}

			m_EnemyIdleFrame++;
			m_EnemyIdleClock.restart();
			m_EnemySprite.setPosition(m_EnemyPosition);
		}

	}
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

void Enemy::EngageCombat()
{
	if (m_EnemyIsAttacking)
	{
		m_EnemySprite.setTexture(m_EnemyAttackTexture);
		m_EnemyIsPatrolling = false;
		m_EnemyIsAttacking = true;
		return;
	}
	m_EnemySprite.setTexture(m_EnemyWalkingTexture);
	m_EnemyIsPatrolling = false;
	m_EnemyIsAttacking = true;
	
}

void Enemy::DisengageCombat()
{
	if (!m_EnemyIsAttacking)
	{
		m_EnemySprite.setTexture(m_EnemyWalkingTexture);
		m_EnemyIsPatrolling = true;
		m_EnemyIsAttacking = false;
		return;
	}
	m_EnemySprite.setTexture(m_EnemyAttackTexture);
	m_EnemyIsPatrolling = false;
	m_EnemyIsAttacking = true;
}

void Enemy::StartPatrol()
{
	if (m_EnemyIsPatrolling)
	{
		m_EnemySprite.setTexture(m_EnemyWalkingTexture);
		m_EnemyIsPatrolling = true;
		m_EnemyIsAttacking = false;
		return;

	}
	m_EnemyIsAttacking = false;
	m_EnemyIsPatrolling = true;
}

void Enemy::StopPatrol()
{
	if (!m_EnemyIsPatrolling)
	{
		m_EnemySprite.setTexture(m_EnemyAttackTexture);

		return;
	}
	m_EnemyIsAttacking = true;
	m_EnemyIsPatrolling = false;
}

