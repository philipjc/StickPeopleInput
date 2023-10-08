#include "TextureCache.h"
#include "Skeleton.h"

#include <iostream>

Skeleton::Skeleton()
{
	m_EnemyWalkingTexture = TextureCache::GetTexture("graphics/skeleton/walk.png");
	m_EnemyAttackTexture = TextureCache::GetTexture("graphics/skeleton/attack_1.png");
	m_EnemyDeathTexture = TextureCache::GetTexture("graphics/skeleton/dead.png");

	m_HitPoints = 10;
	m_MaxHitPoints = 10;
	m_Damage = 1;
	m_IsAlive = true;
	m_EnemyWalkingFrames = 7;
}

void Skeleton::TakeDamage(const int field)
{
	if (m_EnemyIsAttacking)
	{
		std::cout << "Skeleton is attacking" << std::endl;

		// random attack damage

		m_HitPoints -= 1;

		if (m_HitPoints <= 0)
		{
			std::cout << "Skeleton died" << std::endl;
			m_IsAlive = false;
		}

	}

}

void Skeleton::UpdatePatrolAnimation(const float elapsed_time)
{
	m_EnemySprite.setTexture(m_EnemyWalkingTexture);

	if (m_EnemyIsPatrolling)
	{
		m_EnemyPosition.x -= m_EnemySpeed * elapsed_time;

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
		}
	}
}
