#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
class Screen;
class Wall{
private:
	const std::pair<int,int> A;
	const std::pair<int, int> B;
	const std::pair<int, int> C;
	const std::pair<int, int> D;
	sf::RectangleShape self;
	friend class Ray;
public:
	Wall(std::pair<int, int> A, int size);
	void draw(Screen* obj);
};

