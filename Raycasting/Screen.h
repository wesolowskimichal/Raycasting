#pragma once
#include <SFML/Graphics.hpp>
#include "Wall.h"
#include <vector>
#include <iostream>
#include <random>
#include "Ray.h"
using namespace std;
class Screen{
private:
	sf::RenderWindow window;
	const int W;
	const int H;
	int mPosX;
	int mPosY;
	const int VIEW = 250;
	const int UNIT = 25;
	const int MAP_SCALE = 100;
	const int numberOfWalls = 10;
	sf::CircleShape me; 
	vector<vector<char>>map;
	vector<Wall*>walls;
	vector<Ray*>rays;
	friend class Wall;
	friend class Ray;
	int viewS, viewE, viewUP;
	//vector<vector<int>>map;
public:
	Screen(int width, int height);
	sf::RenderWindow& _window();
	void move();
	void turn();
	void update();
	void helpDispl();
	void drawSky();
	void drawFloor();
};

