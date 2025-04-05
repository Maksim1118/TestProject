#pragma once

#include "Symbol.h"
#include <utility>
#include <random>
class Combination
{
public:
	Combination();
	void addCoombinationSymbol(Symbol::Type type);
	void generate();
	bool operator==(const Combination& other) const;
private:
	std::vector<Symbol::Type> m_Combination;
};

