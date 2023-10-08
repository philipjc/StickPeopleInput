#pragma once
#include "PlayableCharacter.h"

class Knight final : public PlayableCharacter
{
public:
	// A constructor specific to Knight
	Knight();
	void UpdateAttackAnimation() override;
	void UpdateWalkAnimation() override;
	void UpdateIdleAnimation() override;

	// The overriden input handler for Knight
	bool HandleInput() override;
	bool m_knightIsIdle{};
};
