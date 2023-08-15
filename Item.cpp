#include "Item.h"
#include <filesystem>
#include <fstream>
#include <algorithm>



void saveToFile(const std::vector<Item>& items, const std::string& fileName) 
{
	std::ofstream ostream(fileName);
	ostream << items.size();

	for (const Item& item : items) {
		std::string description = item.m_description;
		std::replace(description.begin(), description.end(), ' ', '_');

		ostream << '\n' << description << ' ' << item.m_done << ' ' << item.m_startTime;
	}
}

std::vector<Item> loadFromFile(const std::string& fileName)
{
	if (!std::filesystem::exists(fileName)) {
		return std::vector<Item>();
	}

	std::vector<Item> items;
	std::ifstream istream(fileName);

	int vectorSize;
	istream >> vectorSize;

	for (int i = 0; i < vectorSize; i++) {
		std::string description;
		bool done;
		time_t startTime;

		istream >> description >> done >> startTime;
		std::replace(description.begin(), description.end(), '_', ' ');

		items.push_back(Item(description, done, startTime));
	}

	return items;
}
