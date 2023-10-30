#include "AbilityManager.h"

void AbilityManager::AddAbility(std::unique_ptr<Ability> ability) {
    abilities.push_back(std::move(ability));
}

void AbilityManager::TriggerAbility(const int index) const
{
    if (index >= 0 && index < abilities.size()) {
        abilities[index]->use();
    }
}
