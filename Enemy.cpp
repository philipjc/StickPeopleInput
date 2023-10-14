#include "Engine.h"
#include "Enemy.h"
#include "Knight.h"

bool Enemy::SpawnEnemy(Vector2f enemyStartPosition, float gravity)
{
	// Use enemyStartPosition to set the starting position of multiple enemies
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

bool Enemy::GetEnemyAttackState() const
{
	return m_EnemyIsAttacking;
}

void Enemy::UpdateEnemy(const float elapsedTime)
{
	UpdatePatrolAnimation(elapsedTime);
	UpdateAttackAnimation(elapsedTime);

	if (m_EnemyIsFalling)
	{
		m_EnemyPosition.y += m_EnemyGravity * elapsedTime;
	}

	const FloatRect rect = GetEnemyPosition();

	if (!m_EnemyIsAttacking)
	{
		// Update the rect for all body parts
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
			static const sf::IntRect textureCoords[] = {
                sf::IntRect(0, 30, 80, 90),
                sf::IntRect(120, 30, 80, 90),
                sf::IntRect(260, 30, 80, 90),
                sf::IntRect(410, 30, 80, 90),
                sf::IntRect(540, 30, 80, 90),
            };

            if (m_EnemyIdleFrame >= 4)
            {
                m_EnemyIdleFrame = 0;
            }

            m_EnemySprite.setTextureRect(textureCoords[m_EnemyIdleFrame]);
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

// set enemy position
void Enemy::SetEnemyPosition(const float x, const float y)
{
	m_EnemyPosition.x = x;
	m_EnemyPosition.y = y;
	m_EnemySprite.setPosition(m_EnemyPosition);
}

void Enemy::SetPatrolState(const bool isPatrolling, const bool isAttacking)
{
	m_EnemyIsPatrolling = isPatrolling;
	m_EnemyIsAttacking = isAttacking;
}

void Enemy::SetAttackState(const bool isAttacking, const bool isPatrolling)
{
	m_EnemyIsAttacking = isAttacking;
	m_EnemyIsPatrolling = isPatrolling;
}

void Enemy::UpdateTexture()
{
	if (m_EnemyIsAttacking)
	{
		m_EnemySprite.setTexture(m_EnemyAttackTexture);
	}
	else
	{
		m_EnemySprite.setTexture(m_EnemyWalkingTexture);
	}
}

void Enemy::EngageCombat()
{
	UpdateTexture();
	SetAttackState(true, false);
}

void Enemy::DisengageCombat()
{
	UpdateTexture();
	SetAttackState(false, true);
}

void Enemy::StartPatrol()
{
	SetPatrolState(true, false);
	UpdateTexture();
}

void Enemy::StopPatrol()
{
	SetPatrolState(false, true);
	UpdateTexture();
}

