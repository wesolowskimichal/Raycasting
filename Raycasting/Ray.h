#pragma once
class Screen;
class Wall;
class Ray{
private:
	int x;
	int y;
	const double PI;
	const double rad;
public:
	float dist;
	float xx, yy;
	Ray(Screen* obj, int rad);
	void draw(Screen* obj);
	double degToRad(double degrees);
};

