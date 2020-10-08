#pragma once
#include <vector>
#include <string>

typedef char byte;

class Plant
{
public:
	char genes[6];
	std::vector<std::string> parents;
	float chance;
	Plant();
	Plant(std::string geneData);
	Plant(const char* geneData);
	Plant(char* geneData);
	Plant(char* geneData, float chance);
	Plant(const Plant* parentPlants, byte parentPlantCount);
	Plant(const Plant& plant);
	static Plant FindCombination(Plant perfectPlant, const Plant* genePool, int genePoolSize, byte minParentCount, byte maxParentCount);
	bool IsValid();
	friend bool operator==(const Plant& p1, const Plant& p2);
private:
	 int GetHash() const;
	static void GetCombinations(const Plant* genePool, int genePoolSize, byte parentCount, int combinationHash, int start, int index, Plant* combination, Plant& bestPlant, int& hashDiff);
	static std::vector<Plant> GetCrossbreedOutcomes(const Plant* parentPlants, byte parentCount);
};