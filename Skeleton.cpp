#include "TextureCache.h"
#include "Skeleton.h"

#include <iostream>
#include <random>

Skeleton::Skeleton() : m_Dis(1, 5) // Initialize random damage range
{
	m_Gen = std::mt19937(m_RandomDevice());

	m_EnemyTexture = TextureCache::GetTexture("graphics/skeleton/idle.png");
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
		const int randomDamage = m_Dis(m_Gen);

		// Apply random damage
		m_HitPoints -= randomDamage;
		std::cout << "Skeleton took " << randomDamage << " damage." << std::endl;

		if (m_HitPoints <= 0)
		{
			std::cout << "Skeleton died" << std::endl;
			m_IsAlive = false;
		}

	}

}
