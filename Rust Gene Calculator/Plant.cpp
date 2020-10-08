#include "Plant.h"
#include "Gene.h"

Plant::Plant()
{
	this->chance = 0.0f;
}

Plant::Plant(std::string genes)
{
	for (byte i = 0; i < 6; i++)
		this->genes[i] = genes[i];
	this->chance = 1.0f;
}

Plant::Plant(const char* genes)
{
	for (byte i = 0; i < 6; i++)
		this->genes[i] = genes[i];
	this->chance = 1.0f;
}

Plant::Plant(char* genes)
{
	for (byte i = 0; i < 6; i++)
		this->genes[i] = genes[i];
	this->chance = 1.0f;
}

Plant::Plant(char* genes, float chance)
{
	for (byte i = 0; i < 6; i++)
		this->genes[i] = genes[i];
	this->chance = chance;
}

Plant::Plant(const Plant* parentPlants, byte parentPlantCount)
{
	this->parents = std::vector<std::string>(parentPlantCount);
	for (byte i = 0; i < parentPlantCount; i++)
		this->parents[i] = std::string(parentPlants[i].genes, 6);
}

Plant::Plant(const Plant& plant)
{
	for (byte i = 0; i < 6; i++)
		this->genes[i] = plant.genes[i];
	this->chance = plant.chance;
	byte parentCount = size(plant.parents);
	this->parents = std::vector<std::string>(parentCount);
	for (byte i = 0; i < parentCount; i++)
		this->parents[i] = plant.parents[i];
}

int Plant::GetHash() const
{
	int hash = 0;
	for (byte i = 0; i < 6; i++)
	{
		switch (this->genes[i])
		{
		case 'W':
			hash += 1;
			break;
		case 'X':
			hash += 7;
			break;
		case 'H':
			hash += (7 * 7);
			break;
		case 'G':
			hash += (7 * 7 * 7);
			break;
		case 'Y':
			hash += (7 * 7 * 7 * 7);
			break;
		default:
			return 0;
			break;
		}
	}
	return hash;
}

std::vector<Plant> Plant::GetCrossbreedOutcomes(const Plant* parentPlants, byte parentCount)
{
	int outcomeCount = 1;
	Gene gene[6];
	for (byte i = 0; i < 6; i++)
	{
		gene[i] = Gene();
		for (int j = 0; j < parentCount; j++)
			gene[i].Add(parentPlants[j].genes[i]);
		outcomeCount = (int)(outcomeCount * gene[i].GetCombinationsCount());
	}
	std::vector<Plant> childPlants = std::vector<Plant>(outcomeCount);
	for (int i = 0; i < outcomeCount; i++)
	{
		childPlants[i] = Plant(parentPlants, parentCount);
		childPlants[i].chance = 1.0f / outcomeCount;
	}

	for (byte i = 0; i < 6; i++)
	{
		std::vector<char> combinations = gene[i].GetCombinations();
		int combinationsCount = combinations.size();
		for (int j = 0; j < outcomeCount; j++)
			childPlants[j].genes[i] = combinations[j % combinationsCount];
	}
	return childPlants;
}

void Plant::GetCombinations(const Plant* genePool, int genePoolSize, byte parentCount, int combinationHash, int start, int index, Plant* combination, Plant& bestPlant, int& hashDiff)
{
	static bool foundCombination = false;
	if (parentCount == index)
	{
		std::vector<Plant> outcomes = Plant::GetCrossbreedOutcomes(combination, parentCount);
		for (int i = 0; i < std::size(outcomes); i++)
		{
			int tHashDiff = abs(combinationHash - outcomes[i].GetHash());
			if (tHashDiff == 0 && outcomes[i].chance == 1.0f)
			{
				bestPlant = Plant(outcomes[i]);
				foundCombination = true;
				return;
			}
			if (tHashDiff < hashDiff)
			{
				bestPlant = Plant(outcomes[i]);
				hashDiff = tHashDiff;
			}
			else if (tHashDiff == hashDiff && outcomes[i].chance > bestPlant.chance)
				bestPlant = Plant(outcomes[i]);
		}
		return;
	}
	for (int i = start; i < genePoolSize - (parentCount - 1); i++)
	{
		combination[index] = genePool[i + index];
		if (!foundCombination)
			Plant::GetCombinations(genePool, genePoolSize, parentCount, combinationHash, i, index + 1, combination, bestPlant, hashDiff);
	}
}

Plant Plant::FindCombination(Plant perfectPlant, const Plant* genePool, int genePoolSize, byte minParentCount, byte maxParentCount)
{
	Plant plant = Plant();
	for (int i = 0; i < genePoolSize; i++)
	{
		if (genePool[i] == perfectPlant)
		{
			plant = Plant(genePool[i]);
			plant.parents = std::vector<std::string>(1);
			plant.parents[0] = std::string(genePool[i].genes);
			plant.chance = 1.0f;
			return plant;
		}
	}
	int hashDiff = 1337331;
	for (byte i = minParentCount; i <= maxParentCount; i++)
	{
		Plant::GetCombinations(genePool, genePoolSize, i, perfectPlant.GetHash(), 0, 0, new Plant[i], plant, hashDiff);
		if (plant == perfectPlant && plant.chance == 1.0f)
			break;
	}
	return plant;
}

bool Plant::IsValid()
{
	return this->GetHash();
}

bool operator==(const Plant& p1, const Plant& p2)
{
	return p1.GetHash() == p2.GetHash();
}