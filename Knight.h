#pragma once

#include "PlayableCharacter.h"

class Knight final : public PlayableCharacter
{
public:
	// A constructor specific to Knight
	Knight();

	// The overriden input handler for Knight
	bool HandleInput() override;

};
