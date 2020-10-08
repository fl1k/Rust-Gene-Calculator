#pragma once
#include <vector>

typedef char byte;

class Gene
{
public:
	byte w;
	byte x;
	byte h;
	byte g;
	byte y;
	Gene();
	void Add(char i);
	byte GetStrongestGene();
	byte GetCombinationsCount();
	std::vector<char> GetCombinations();
};

