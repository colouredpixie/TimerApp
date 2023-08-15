#pragma once
#include <string>
#include <vector>

class Item
{
public:
	std::string m_description;
	bool m_done;
	time_t m_startTime;

	Item(std::string description, bool done, time_t startTime) : m_description(description), m_done(done), m_startTime(startTime) {}

};

void saveToFile(const std::vector<Item>& items, const std::string& fileName);
std::vector<Item> loadFromFile(const std::string& fileName);

