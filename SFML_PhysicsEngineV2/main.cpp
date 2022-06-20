#include <SFML/Graphics.hpp>
#include <string>
#include "Functions.h"
#include "Circle.h"
#include "Settings.h"
#include "Engine.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(900, 900), "SFML-PhysicsEngine test!");
	window.setFramerateLimit(10);

	sf::Font font;
	if (!font.loadFromFile("comic.ttf")) {
		std::cout << "Error loading the file\n";
	}
	
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);
	
	Engine engine;
	engine.load_settings();

	//sf::Text text;
	//text.setFont(font);
	engine.prepare_UI(font);
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
					case sf::Keyboard::T: {
						std::cout << "T pressed\n";
						Settings::time_stopped = !Settings::time_stopped;
						break;
					}
					case sf::Keyboard::A: {
						Settings::stokes_drag_on = !Settings::stokes_drag_on;
						std::cout << "A pressed\n";
						break;
					}
					case sf::Keyboard::G: {
						std::cout << "G pressed\n";
						Settings::uniform_gravity = !Settings::uniform_gravity;
						break;
					}
					case sf::Keyboard::D: {
						Settings::frame_by_frame_debug_on = !Settings::frame_by_frame_debug_on;
						Settings::frame_by_frame_lock = false;
						std::cout << "D pressed\n";
						break;
					}
					case sf::Keyboard::F: {
						if (Settings::frame_by_frame_debug_on) {
							Settings::frame_by_frame_lock = true;
						}
						std::cout << "F pressed\n";
						break;
					}
					case sf::Keyboard::L: {
						Settings::logging_on = !Settings::logging_on;
						std::cout << "L pressed\n";
						break;
					}
				}
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (Settings::clicking_allowed) {
						engine.log("Adding new circle!");
						//auto[mouseX, mouseY] = sf::Mouse::getPosition();
						Circle circle(event.mouseButton.x, event.mouseButton.y, 35, sf::Color::Green);
						circle.mass = 9;
						//circle.color = circle.mass * 15;
						//circle.color = sf::Color(100, 100, 100);
						engine.add_circle(circle, window);
					}
				}
			}
		}

		//engine.log("window.clear() called in main.cpp");
		window.clear();

		engine.log("engine.update(window) called in main.cpp");
		engine.update(window);

		window.display();
		//engine.log("window.display() called in main.cpp");
	}

	return 0;
}
