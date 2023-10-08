#pragma once
#include "Enemy.h"

class Skeleton final : public Enemy
{
public:
	Skeleton();

	void TakeDamage(int field) override;
	void UpdatePatrolAnimation(const float elapsed_time);
};
