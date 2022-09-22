#include "Wall.h"
#include "Screen.h"

//
//  A_______D
//	|		|
//	|_______|
//	B		C

Wall::Wall(std::pair<int, int> A, int size) :A(A), B({A.first, A.second+size}), C({ A.first + size, A.second + size}), D({ A.first + size, A.second}) {
	this->self.setFillColor(sf::Color::Green);
	this->self.setSize(sf::Vector2f(size, size));
	this->self.setPosition(A.first, A.second);
};

void Wall::draw(Screen* obj) {
	obj->window.draw(this->self);
}