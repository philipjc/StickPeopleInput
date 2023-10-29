#pragma once

class Ability {
public:
	virtual ~Ability() = default;
	virtual void use() = 0; // Pure virtual function
};
