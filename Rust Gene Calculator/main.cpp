#include <iostream>
#include <filesystem>
#include  <fstream>
#include "Plant.h"

using namespace std;
#define MAX_PLANTS 1024

Plant genePool[MAX_PLANTS];

int main()
{
	if (!filesystem::exists("plants.txt"))
	{
		ofstream ofStream("plants.txt");
		ofStream.close();
		cout << "plants.txt created, type your genetics in there seperated by a space\n";
		system("pause");
		return 0;
	}
	ifstream ifStream("plants.txt");
	string input;
	int pointer = 0;
	int counter = 0;
	if (getline(ifStream, input))
	{
		while (pointer + 6 <= input.length() && counter < MAX_PLANTS)
		{
			for (int i = 0; i < 6; i++)
				genePool[counter].genes[i] = input[pointer + i];
			if (genePool[counter].IsValid())
				counter++;
			pointer += 7;
		}
	}
	Plant perfectPlant = Plant::FindCombination(Plant("YYYYGG"), genePool, counter, 3, 5);
	cout << "Best gene combination that was found from the gene pool is: " << string(perfectPlant.genes, 6) << "\n";
	cout << "Parents: ";
	for (size_t i = 0; i < size(perfectPlant.parents); i++)
		cout << perfectPlant.parents[i] << " ";
	cout << '\n';
	cout << "Chance: " << perfectPlant.chance * 100.0f << "%\n";
	system("pause");
	return 0;
}