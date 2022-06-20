#pragma once
#include "Functions.h"

class Circle {
public:
	double r;
	//int color;
	Vector2D pos;
	Vector2D velocity;
	Vector2D acceleration;
	double mass;
	//bool special;
	sf::Color color;
	bool opaque;
	double opacity;
	bool immovable;
	bool projectile;

	sf::CircleShape shape;
	
	Circle(double x, double y, double r, const sf::Color& color = sf::Color());

	Circle(const Vector2D& pos, double r, const sf::Color& color = sf::Color());

	void draw(sf::RenderWindow& window);

	void move(double dt);
};

