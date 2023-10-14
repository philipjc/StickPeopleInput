#pragma once
#include <random>

#include "Enemy.h"

class Skeleton final : public Enemy
{
private:
	std::mt19937 m_Gen;
	std::uniform_int_distribution<> m_Dis;
	std::random_device m_RandomDevice;

public:
	Skeleton();

	void TakeDamage(int field) override;

};
