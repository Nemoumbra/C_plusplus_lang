#include <SFML/Graphics.hpp>
#include <string>
#include "Functions.h"
#include "Circle.h"
#include "Settings.h"
#include "Engine.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(900, 900), "SFML-PhysicsEngine test!");
	window.setFramerateLimit(60);

	sf::Font font;
	if (!font.loadFromFile("comic.ttf")) {
		std::cout << "Error loading the file\n";
	}
	
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);
	
	Engine engine;
	engine.load_settings();

	engine.prepare_UI(font);

	engine.prepare_borders(/*args*/);
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
					case sf::Keyboard::T: {
						engine.log("T pressed");
						Settings::time_stopped = !Settings::time_stopped;
						break;
					}
					case sf::Keyboard::A: {
						Settings::stokes_drag_on = !Settings::stokes_drag_on;
						engine.log("A pressed");
						break;
					}
					case sf::Keyboard::G: {
						engine.log("G pressed");
						Settings::uniform_gravity = !Settings::uniform_gravity;
						break;
					}
					case sf::Keyboard::D: {
						Settings::frame_by_frame_debug_on = !Settings::frame_by_frame_debug_on;
						Settings::frame_by_frame_lock = false;
						engine.log("D pressed");
						break;
					}
					case sf::Keyboard::F: {
						if (Settings::frame_by_frame_debug_on) {
							Settings::frame_by_frame_lock = false;
						}
						engine.log("F pressed");
						break;
					}
					case sf::Keyboard::L: {
						Settings::logging_on = !Settings::logging_on;
						engine.log("L pressed");
						break;
					}
					case sf::Keyboard::B: {
						Settings::borders_on = !Settings::borders_on;
						engine.log("B pressed");
						break;
					}
				}
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (Settings::clicking_allowed) {

						/*
							obj.mass = round(random(1, 15));
							obj.colour = round(obj.mass * 15);
						*/

						engine.log("Adding new circle!");
						//auto[mouseX, mouseY] = sf::Mouse::getPosition();
						int r = 30 + std::rand() % 10;
						int m = 1 + std::rand() % 14;
						char c = static_cast<char> (15 * m);
						Circle circle(event.mouseButton.x - r, event.mouseButton.y - r, r, sf::Color(c, c, c));
						circle.mass = m;
						
						//circle.mass = 9;
						//circle.color = circle.mass * 15;
						//circle.color = sf::Color(100, 100, 100);
						engine.add_circle(circle, window);
						engine.add_trajectory(engine.object_storage.back(), 7, 10, sf::Color::White, 5);
					}
				}
			}
		}

		//engine.log("window.clear() called in main.cpp");
		window.clear();

		//engine.log("engine.update(window) called in main.cpp");
		engine.update(window);

		window.display();
		//engine.log("window.display() called in main.cpp");
	}

	return 0;
}
