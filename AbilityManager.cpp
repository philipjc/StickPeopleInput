#include "AbilityManager.h"

void AbilityManager::addAbility(std::unique_ptr<Ability> ability) {
    abilities.push_back(std::move(ability));
}

void AbilityManager::triggerAbility(int index) const
{
    if (index >= 0 && index < abilities.size()) {
        abilities[index]->use();
    }
}
