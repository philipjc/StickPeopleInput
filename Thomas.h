#pragma once
#include "PlayableCharacter.h"

class Thomas final : public PlayableCharacter
{
public:
	// A constructor specific to Thomas
	Thomas();

	// The overriden input handler for Thomas
	bool HandleInput() override;

};