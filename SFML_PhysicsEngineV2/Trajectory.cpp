#include "Trajectory.h"

Trajectory::Trajectory(const Circle& circle, double r, int max_size, const sf::Color& color, int frequency) :
	trail_container(),
	counter(0),
	child(circle),
	r(r),
	max_size(max_size),
	color(color),
	frequency(frequency)
{};

void Trajectory::add(const Vector2D& pos) {
	if (trail_container.size() == max_size) {
		trail_container.pop_front();
	}
	Circle circle(pos, r);
	//circle.special = true;
	circle.color = color;
	circle.opaque = false;
	trail_container.push_back(circle);
}

void Trajectory::save_new() {
	(++counter) %= frequency;
	if (!counter) {
		add(child.pos); // this is how it works with Java
	}
}

void Trajectory::draw(sf::RenderWindow& window) {
	auto size = trail_container.size();
	for (int i = 0; i < size; ++i) {
		trail_container[i].opacity = 100 * i / (size + 1);
		trail_container[i].draw(window);
	}
}
