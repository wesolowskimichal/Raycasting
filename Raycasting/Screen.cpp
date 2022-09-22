#include "Screen.h"
Screen::Screen(int width, int height):W(width),H(height){
	this->window.create(sf::VideoMode(this->W, this->H), "Raycasting");
	this->mPosX = 300;
	this->mPosY = 500;
	this->viewS = 270;
	this->viewE = 330;
	this->viewUP = 0;
	this->me.setFillColor(sf::Color::Magenta);
	this->me.setRadius(this->UNIT);
	this->me.setPosition(this->mPosX, this->mPosY);
	this->map = {
		{'#','#','#','#','#','#','#','#'},
		{'#','-','-','-','-','-','-','#'},
		{'#','-','#','-','-','#','-','#'},
		{'#','-','#','#','-','-','-','#'},
		{'#','-','-','-','-','-','-','#'},
		{'#','-','#','-','-','-','-','#'},
		{'#','-','-','-','-','-','-','#'},
		{'#','-','-','-','-','-','-','#'},
		{'#','-','#','-','-','#','-','#'},
		{'#','-','#','#','-','-','-','#'},
		{'#','-','-','-','-','-','-','#'},
		{'#','#','#','#','#','#','#','#'}
	};
	for (int i = viewS; i <= viewE; i++)
		this->rays.push_back(new Ray(this, i));
	for (size_t i{}; i < this->map.size(); i++)
		for (size_t j{}; j < this->map[0].size(); j++)
			if (map[i][j] == '#')
				this->walls.push_back(new Wall({ j * this->MAP_SCALE, i * this->MAP_SCALE }, this->MAP_SCALE));
}

sf::RenderWindow& Screen::_window() {
	return this->window;
}

void Screen::move() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->mPosY -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->mPosY += 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->mPosX -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->mPosX += 1;
	this->me.setPosition(this->mPosX - this->UNIT, this->mPosY -  this->UNIT);
}

void Screen::turn() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->viewS--;
		this->viewE--;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->viewS++;
		this->viewE++;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->viewUP++;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->viewUP--;
	}
}

void Screen::drawSky() {
	sf::RectangleShape sky(sf::Vector2f(this->W, 50));
	sky.setPosition(0, 0);
	sky.setFillColor(sf::Color::Blue);
	this->window.draw(sky);
}

void Screen::drawFloor() {
	sf::RectangleShape floor(sf::Vector2f(this->W, this->H));
	floor.setPosition(0, 0);
	floor.setFillColor(sf::Color::Red);
	this->window.draw(floor);
}

void Screen::update() {
	move();
	turn();
	//this->window.draw(this->me);
	for (auto ray : this->rays)
		delete ray;
	this->drawFloor();
	//this->drawSky();
	this->rays.clear();
	for (int i = viewS; i <= viewE; i++)
			this->rays.push_back(new Ray(this, i));
	float x = 0.0;
	float y = this->W/this->rays.size();
	for (int i = 0; i <60; i++) {
		float FOV = float(rays[i]->dist / (float)this->VIEW);
		//float FOV = float(rays[i]->dist / (float)this->VIEW);
		sf::RectangleShape w(sf::Vector2f(y, this->H * (1-FOV)));
		w.setFillColor(sf::Color(0, 255 * (1 - rays[i]->dist / VIEW), 0));
		w.setPosition(x, this->viewUP * FOV);
		x += y;
		this->window.draw(w);
	}
	this->window.display();
	this->window.clear();
}

void Screen::helpDispl() {
	move();
	turn();
	this->window.draw(this->me);
	for (auto ray : this->rays)
		delete ray;
	this->rays.clear();
	for (int i = viewS; i <= viewE; i++) 
		this->rays.push_back(new Ray(this, i));
	for (auto ray : this->rays)
		ray->draw(this);
	for (auto wall : walls)
		wall->draw(this);
	this->window.display();
	this->window.clear();
}