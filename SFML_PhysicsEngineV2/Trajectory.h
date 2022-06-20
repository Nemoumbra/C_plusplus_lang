#pragma once
#include <deque>
#include "Circle.h"

class Trajectory {
public:
	std::deque <Circle> trail_container;
	int counter;
	
	Circle child;
	double r;
	int max_size;
	sf::Color color;
	int frequency;

	Trajectory(const Circle& circle, double r, int max_size, const sf::Color& color, int frequency);

	void add(const Vector2D& pos);

	void save_new();

	void draw(sf::RenderWindow& window);
};

