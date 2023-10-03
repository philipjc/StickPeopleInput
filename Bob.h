#pragma once
#include "PlayableCharacter.h"

class Bob final : public PlayableCharacter
{
public:
    // A constructor specific to Bob
    Bob();

    // The overriden input handler for Bob
    bool HandleInput() override;
};
