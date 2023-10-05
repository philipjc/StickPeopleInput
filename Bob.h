#pragma once

#include "PlayableCharacter.h"

class Bob final : public PlayableCharacter
{
public:
	// A constructor specific to Bob
	Bob();

	const int left = 0;
	const int bottom = -20;
	const int right = 75;
	const int top = 86;

	const int idle_frames = 6;
	const int walking_frames = 4;

	// The overriden input handler for Bob
	bool HandleInput() override;

};
