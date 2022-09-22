#include "Ray.h"
#include "Wall.h"
#include "Screen.h"
#include <math.h>

pair<float, float>intersection(pair<int,int>A, pair<int,int>B, pair<int,int>C, pair<int,int>D) {
	float s1x, s1y, s2x, s2y;
	s1x = B.first - A.first;
	s1y = B.second - A.second;
	s2x = D.first - C.first;
	s2y = D.second - C.second;
	float s, t;
	s = (-s1y * (A.first - C.first) + s1x * (A.second - C.second)) / (-s2x * s1y + s1x * s2y);
	t = (s2x * (A.second - C.second) - s2y * (A.first - C.first)) / (-s2x * s1y + s1x * s2y);
	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		// Collision detected
		return { A.first + (t * s1x), A.second + (t*s1y)};
	}
	return{ -1, -1 };
}

Ray::Ray(Screen* obj, int rad):PI(3.14159265358979311600), rad(this->degToRad(rad)){
	// calc for x y
	int r = obj->VIEW;
	double xV = cos(this->rad) * r;
	double yV = sin(this->rad) * r;
	int fX = obj->mPosX + xV, fY = obj->mPosY + yV;
	for (auto wall : obj->walls) {
		pair<int, int> intersect1 = intersection({ obj->mPosX, obj->mPosY }, { obj->mPosX + xV, obj->mPosY + yV }, wall->A, wall->B);
		pair<int, int> intersect2 = intersection({ obj->mPosX, obj->mPosY }, { obj->mPosX + xV, obj->mPosY + yV }, wall->A, wall->D);
		pair<int, int> intersect3 = intersection({ obj->mPosX, obj->mPosY }, { obj->mPosX + xV, obj->mPosY + yV }, wall->B, wall->C);
		pair<int, int> intersect4 = intersection({ obj->mPosX, obj->mPosY }, { obj->mPosX + xV, obj->mPosY + yV }, wall->D, wall->C);

		if (intersect1.first != -1) {
			float curr = sqrt(pow(fX - obj->mPosX, 2) + pow(fY - obj->mPosY, 2));
			float prop = sqrt(pow(intersect1.first - obj->mPosX, 2) + pow(intersect1.second - obj->mPosY, 2));
			if (curr > prop) {
				fX = intersect1.first;
				fY = intersect1.second;
			}
		}
		if (intersect2.first != -1) {
			float curr = sqrt(pow(fX - obj->mPosX, 2) + pow(fY - obj->mPosY, 2));
			float prop = sqrt(pow(intersect2.first - obj->mPosX, 2) + pow(intersect2.second - obj->mPosY, 2));
			if (curr > prop) {
				fX = intersect2.first;
				fY = intersect2.second;
			}
		}
		if (intersect3.first != -1) {
			float curr = sqrt(pow(fX - obj->mPosX, 2) + pow(fY - obj->mPosY, 2));
			float prop = sqrt(pow(intersect3.first - obj->mPosX, 2) + pow(intersect3.second - obj->mPosY, 2));
			if (curr > prop) {
				fX = intersect3.first;
				fY = intersect3.second;
			}
		}
		if (intersect4.first != -1) {
			float curr = sqrt(pow(fX - obj->mPosX, 2) + pow(fY - obj->mPosY, 2));
			float prop = sqrt(pow(intersect4.first - obj->mPosX, 2) + pow(intersect4.second - obj->mPosY, 2));
			if (curr > prop) {
				fX = intersect4.first;
				fY = intersect4.second;
			}
		}
	}
	this->dist = sqrt(pow(fX - obj->mPosX, 2) + pow(fY - obj->mPosY, 2));
	this->xx = fX;
	this->yy = fY;
	/*sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(obj->mPosX, obj->mPosY)),
		sf::Vertex(sf::Vector2f(fX, fY))
	};
	
	obj->window.draw(line, 2, sf::Lines);*/
}

double Ray::degToRad(double degrees) {
	return degrees * this->PI / 180.0;
}

void Ray::draw(Screen* obj) {
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(obj->mPosX, obj->mPosY)),
		sf::Vertex(sf::Vector2f(xx, yy))
	};

	obj->window.draw(line, 2, sf::Lines);
}