#include "Combination.h"

Combination::Combination()
{

}

void Combination::addCoombinationSymbol(Symbol::Type type)
{
	m_Combination.emplace_back(type);
}


bool Combination::operator==(const Combination& other) const
{
	if (m_Combination.size() != other.m_Combination.size()) return false;
	for (int i = 0; i < m_Combination.size(); ++i)
	{
		if (other.m_Combination[i] != m_Combination[i])
			return false;
	}
	return true;
}

void Combination::generate()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> shapeDist(0, 3);
	uniform_int_distribution<> colorDist(0, 9);

	for (int i = 0; i < 3; ++i)
	{
		Symbol::Type type = static_cast<Symbol::Type>(shapeDist(gen));
		m_Combination.emplace_back(type);
	}
}