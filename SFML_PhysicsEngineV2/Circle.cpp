#include "Circle.h"
#include "Settings.h"
#include <iostream>

Circle::Circle(double x, double y, double r, const sf::Color& color) :
	r(r),
	//color(100), // here will be either a const value or a call to rand function
	pos(Vector2D(x, y)),
	velocity(Vector2D(0, 0)),
	acceleration(Vector2D(0, 0)),
	mass(0),
	//special(false),
	color(color),
	opaque(true),
	opacity(0),
	immovable(false),
	projectile(false),
	shape(sf::CircleShape(r)) 
{
	shape.setFillColor(sf::Color(color.r, color.g, color.b, opaque ? 0 : opacity));
	shape.setOutlineThickness(1);
	if (Settings::circles_stroke) {
		shape.setOutlineColor(sf::Color(200, 0, 0, opaque ? 0 : opacity));
	}
	else {
		shape.setOutlineColor(sf::Color(color.r, color.g, color.b, opaque ? 0 : opacity));
	}
	shape.setPosition(x, y);

}

Circle::Circle(const Vector2D& pos, double r, const sf::Color& color) :
	r(r),
	//color(), // here will be either a const value or a call to rand function
	pos(Vector2D(pos)),
	velocity(Vector2D(0, 0)),
	acceleration(Vector2D(0, 0)),
	mass(0),
	//bool special;
	color(color),
	opaque(true),
	opacity(0),
	immovable(false),
	projectile(false),
	shape(sf::CircleShape(r)) 
{
	shape.setFillColor(sf::Color(color.r, color.g, color.b, opaque ? 0 : opacity));
	shape.setOutlineThickness(1);
	if (Settings::circles_stroke) {
		shape.setOutlineColor(sf::Color(200, 0, 0, opaque ? 0 : opacity));
	}
	else {
		shape.setOutlineColor(sf::Color(color.r, color.g, color.b, opaque ? 0 : opacity));
	}
	shape.setPosition(pos.x, pos.y);
}

void Circle::draw(sf::RenderWindow& window) {
	shape.setPosition(pos.x, pos.y);
	window.draw(shape);
	std::cout << "Circle::draw is called!\n";
	std::cout << "pos = {" << pos.x << "; " << pos.y << "}\n";
}

void Circle::move(double dt) {
	if (!immovable) {
		velocity += acceleration * dt;
		pos += velocity * dt;
	}
}
