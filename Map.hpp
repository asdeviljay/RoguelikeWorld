#pragma once

#include <string>
#include <vector>

class Map
{
public:
	Map();
	Map(unsigned int t_width, unsigned int t_height);
	~Map();
	Map(const Map&) = default;
	Map& operator= (const Map&) = default;

	bool init();
	void update();
	void destroy();

	bool loadMap();

private:
	unsigned int m_width;
	unsigned int m_height;

	//unsigned char[m_width][m_height];
	std::vector<std::string> m_map;
};
