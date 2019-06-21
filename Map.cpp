#include "pch.h"
#include "Map.hpp"
#include <fstream>
#include <string>
#include <iostream>

Map::Map() :
	m_width(5),
	m_height(5)
{
}

Map::Map(unsigned int t_width, unsigned int t_height) :
	m_width(t_width),
	m_height(t_height)
{
}

Map::~Map()
{
}

bool Map::init() {

	return Map::loadMap();
}

void Map::update() {
	std::cout << "|--------------------|" << std::endl;
	std::cout << "|....................|" << std::endl;
	std::cout << "|..............M.....|" << std::endl;
	std::cout << "|....................|" << std::endl;
	std::cout << "|--------------------|" << std::endl;
}

void Map::destroy() {

}

bool Map::loadMap() {
	std::string readLine;
	std::ifstream myMap;
	myMap.open("map.txt", std::ios::in | std::ios::app);

	if (myMap.is_open()) {
		while (std::getline(myMap, readLine)) {
			m_map.push_back(readLine);
		}
		myMap.close();
		return true;
	}
	else {
		return false;
	}
}