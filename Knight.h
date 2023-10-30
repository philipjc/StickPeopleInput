#pragma once
#include "PlayableCharacter.h"

class Knight final : public PlayableCharacter
{
public:
	// A constructor specific to Knight
	Knight();

	// variables
	bool m_gPressed = false;

	// The overriden input handler for Knight
	void UpdateAttackAnimation() override;
	void UpdateWalkAnimation() override;
	void UpdateIdleAnimation() override;
	bool HandleInput() override;

private:
	const int m_IdleAnimFrames = 4;
	const int m_WalkingFrames = 8;
	const int m_AttackingFrames = 5;

};
