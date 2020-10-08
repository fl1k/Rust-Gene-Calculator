#include "Gene.h"

Gene::Gene()
{
	this->w = 0;
	this->x = 0;
	this->h = 0;
	this->g = 0;
	this->y = 0;
}

byte Gene::GetStrongestGene()
{
	byte max = this->w;
	if (this->x > max) max = this->x;
	if (this->h > max) max = this->h;
	if (this->g > max) max = this->g;
	if (this->y > max) max = this->y;
	return max;
}

byte Gene::GetCombinationsCount()
{
	byte strongestGene = this->GetStrongestGene();
	byte combinationCount = 0;
	if (strongestGene == this->w) combinationCount++;
	if (strongestGene == this->x) combinationCount++;
	if (strongestGene == this->h) combinationCount++;
	if (strongestGene == this->g) combinationCount++;
	if (strongestGene == this->y) combinationCount++;
	return combinationCount;
}

void Gene::Add(char i)
{
	if (i == 'W') { this->w += 5; return; }
	if (i == 'X') { this->x += 5; return; }
	if (i == 'H') { this->h += 3; return; }
	if (i == 'G') { this->g += 3; return; }
	if (i == 'Y') { this->y += 3; return; }
}

std::vector<char> Gene::GetCombinations()
{
    byte strongestGene = this->GetStrongestGene();
    std::vector<char> combinations(this->GetCombinationsCount());
    int i = 0;
    if (strongestGene == this->w)
    {
        combinations[i] = 'W';
        i++;
    }
    if (strongestGene == this->x)
    {
        combinations[i] = 'X';
        i++;
    }
    if (strongestGene == this->h)
    {
        combinations[i] = 'H';
        i++;
    }
    if (strongestGene == this->g)
    {
        combinations[i] = 'G';
        i++;
    }
    if (strongestGene == this->y)
    {
        combinations[i] = 'Y';
        i++;
    }
    return combinations;
}