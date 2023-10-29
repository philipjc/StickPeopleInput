#pragma once
#include <vector>
#include <memory>
#include "Ability.h"

class AbilityManager {
public:
	std::vector<std::unique_ptr<Ability>> abilities;

	void addAbility(std::unique_ptr<Ability> ability);
	void triggerAbility(int index);
};
