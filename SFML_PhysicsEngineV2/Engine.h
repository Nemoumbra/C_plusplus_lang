#pragma once
#include "Functions.h"
#include "Settings.h"
#include "Circle.h"
#include <vector>
#include "Trajectory.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include "Borders.h"

namespace fsystem = std::filesystem;

class Engine {
public:
	std::vector <Circle> object_storage;
	std::vector <Trajectory> trajectory_storage;
	Borders borders;

	//std::vector <sf::Text> UI_texts;
	sf::Text uniform_gravity_text;
	sf::Text time_stopped_text;
	sf::Text frame_by_frame_debug_text;
	sf::Text drag_text;
	//sf::Text 

	void log(const std::string& text);

	void add_circle(const Circle& circle, sf::RenderWindow& window);
	void add_trajectory(const Circle& circle, double r, int max_size, const sf::Color& color, int frequensy);


	void prepare_UI(const sf::Font& font);

	void prepare_borders(/*Vector2D left_up, Vector2D right_bottom, double thinkness, const sf::Color& color*/);

	void draw_user_interface(sf::RenderWindow& window);

	void draw_trajectories(sf::RenderWindow& window, bool draw_if_stopped);

	void draw_circles(sf::RenderWindow& window);

	void apply_uniform_gravity(Circle& circle);
	void apply_gravity(int index);
	void apply_stokes_drag(Circle& circle);
	void apply_newtonian_drag(Circle& circle);
	void apply_friction_and_stiction(Circle& circle);

	void apply_forces();

	void update_positions(double dt);

	bool resolve_collision(Circle& circle_1, Circle& circle_2);
	bool resolve_collision(Circle& circle, const Borders& borders);
	bool resolve_collisions();

	void update(sf::RenderWindow& window);

	void use_default_settings();
	void load_settings();

	void save_settings();

	Engine() = default;

};
