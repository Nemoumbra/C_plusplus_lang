#include "Engine.h"
#include <string>
#include <cmath>

void Engine::log(const std::string& text) {
	if (Settings::logging_on) {
		std::cout << text << "\n";
	}
}

void Engine::add_circle(const Circle& circle, sf::RenderWindow& window) {
	std::cout << "Engine::add_circle called\n";
	object_storage.push_back(circle);
	object_storage.back().draw(window);
}
void Engine::add_trajectory(const Circle& circle, double r, int max_size, const sf::Color& color, int frequensy) {
	trajectory_storage.emplace_back(circle, r, max_size, color, frequensy);
}

void Engine::prepare_UI(const sf::Font& font) {
	uniform_gravity_text.setFont(font);
	uniform_gravity_text.setCharacterSize(22); // 22
	uniform_gravity_text.setFillColor(sf::Color(10, 100, 10));
	uniform_gravity_text.setPosition(38, 45);
	
	time_stopped_text.setFont(font);
	time_stopped_text.setCharacterSize(22); // 22
	time_stopped_text.setFillColor(sf::Color(110, 40, 40));
	time_stopped_text.setPosition(645, 45);

	/*
		if (recording) {
			stroke(110, 40, 40);
			text("REC", 645, 70);
			circle(700, 62, 10);
		}
	*/

	drag_text.setFont(font);
	drag_text.setCharacterSize(22); // 22
	drag_text.setFillColor(sf::Color(110, 110, 0));
	drag_text.setPosition(40, 70);
	
	frame_by_frame_debug_text.setFont(font);
	frame_by_frame_debug_text.setCharacterSize(22); //22
	frame_by_frame_debug_text.setFillColor(sf::Color(40, 40, 100));
	frame_by_frame_debug_text.setString("Frame-by-frame debug on");
	frame_by_frame_debug_text.setPosition(305, 45);
}

void Engine::draw_user_interface(sf::RenderWindow& window) {
	//for (const sf::Text& text : UI_texts) {
	//	window.draw(text);
	//}
	uniform_gravity_text.setString("Uniform gravity on: " + bool_to_string(Settings::uniform_gravity));

	time_stopped_text.setString("Time stopped: " + bool_to_string(Settings::time_stopped));

	drag_text.setString("Air friction on: " + bool_to_string(Settings::stokes_drag_on));

	window.draw(uniform_gravity_text);
	window.draw(time_stopped_text);
	window.draw(drag_text);
	if (Settings::frame_by_frame_debug_on) {
		window.draw(frame_by_frame_debug_text);
	}
}

void Engine::draw_trajectories(sf::RenderWindow& window, bool draw_if_stopped) {
	if ((Settings::time_stopped || Settings::frame_by_frame_lock) && !draw_if_stopped) {
		return;
	}
	for (Trajectory& trajectory : trajectory_storage) {
		trajectory.draw(window);
	}
}

void Engine::draw_circles(sf::RenderWindow& window) {
	for (Circle& circle : object_storage) {
		circle.draw(window);
	}
}

void Engine::apply_uniform_gravity(Circle& circle) {
	if (Settings::uniform_gravity && !Settings::g.z) {
		circle.acceleration += remove_z(Settings::g);
	}
}
void Engine::apply_gravity(int index) {
	if (Settings::gravity_on) {
		Circle& circle_1 = object_storage[index];
		for (int i = index + 1; i < object_storage.size(); ++i) {
			Circle& circle_2 = object_storage[i];
			Vector2D circle_1_to_circle_2 = circle_2.pos - circle_1.pos;
			double r_squared = len_squared(circle_1_to_circle_2);
			normalize(circle_1_to_circle_2);

			if (!circle_1.immovable) {
				circle_1.acceleration += (Settings::G * circle_2.mass / r_squared) * circle_1_to_circle_2;
			}
			if (!circle_2.immovable) {
				circle_2.acceleration -= (Settings::G * circle_1.mass / r_squared) * circle_1_to_circle_2;
			}
		}
	}
}
void Engine::apply_stokes_drag(Circle& circle) {
	if (Settings::stokes_drag_on) {
		circle.acceleration -= (6 * PI() * Settings::viscosity * circle.r / circle.mass) * circle.velocity;
	}
}
void Engine::apply_newtonian_drag(Circle& circle) {
	if (Settings::newtonian_drag_on) {
		circle.acceleration -= (Settings::newtonian_k * length(circle.velocity) / circle.mass) * circle.velocity;
	}
}
void Engine::apply_friction_and_stiction(Circle& circle) {
	if (!(Settings::uniform_gravity && Settings::g.z)) {
		return;
	}
	if (length(circle.acceleration) <= Settings::mu * length(Settings::g)) {
		circle.acceleration.x = 0;
		circle.acceleration.y = 0;
		return;
	}
	if (circle.velocity.x != 0 && circle.velocity.y != 0) {
		circle.acceleration -= (Settings::mu * length(Settings::g) / length(circle.velocity)) * circle.velocity;
	}
}

void Engine::apply_forces() {
	if (Settings::time_stopped || Settings::frame_by_frame_lock) {
		return;
	}
	for (Circle& circle : object_storage) {
		circle.acceleration.x = 0;
		circle.acceleration.y = 0;
	}

	int i = 0;
	for (Circle& circle : object_storage) {
		apply_uniform_gravity(circle);
		apply_gravity(i);
		apply_stokes_drag(circle);
		apply_newtonian_drag(circle);
		apply_friction_and_stiction(circle);
		++i;
	}
}

void Engine::update_positions(double dt) {
	for (Circle& circle : object_storage) {
		log("circle.move(dt) called in engine.cpp");
		circle.move(dt);
	}
}

bool Engine::resolve_collision(Circle& circle_1, Circle& circle_2) {
	double dist = length(circle_1.pos - circle_2.pos) - circle_1.r - circle_2.r;
	if (dist > 0) {
		return false;
	}
	Vector2D O1_O2 = circle_2.pos - circle_1.pos;
	normalize(O1_O2);
	double v_1 = dot(circle_1.velocity, O1_O2);
	double v_2 = dot(circle_2.velocity, O1_O2);
	double v_c = (v_1 * circle_1.mass + v_2 * circle_2.mass) / (circle_1.mass + circle_2.mass);
	double V_1 = 2 * v_c - v_1, V_2 = 2 * v_c - v_2;
	circle_1.velocity += (V_1 - v_1) * O1_O2;
	circle_2.velocity += (V_2 - v_2) * O1_O2;
	return true;
}

bool Engine::resolve_collisions() {
	bool res = false;
	for (int i = 0; i < object_storage.size(); ++i) {
		for (int j = i + 1; j < object_storage.size(); ++j) {
			res = res || resolve_collision(object_storage[i], object_storage[j]);
		}
	}
	return res;
}

void Engine::update(sf::RenderWindow& window) {
	//log("draw_user_interface(window) called in engine.cpp");
	draw_user_interface(window);
	
	//log("apply_forces() called in engine.cpp");
	apply_forces();

	double dt = 1.0 / Settings::loops_per_frame;
	bool next_frame = false;

	for (int i = 0; i < Settings::loops_per_frame; ++i) {
		//log(std::to_string(i));
		if (next_frame) break;
		log("update_positions(dt) called in engine.cpp");
		update_positions(dt);

		//log("resolve_collisions() called in engine.cpp");
		next_frame = resolve_collisions();
	}
	if (Settings::frame_by_frame_debug_on && !Settings::frame_by_frame_lock) {
		Settings::frame_by_frame_lock = true;
	}
	// draw borders

	//log("draw_trajectories(window, true) called in engine.cpp");
	draw_trajectories(window, true);

	log("draw_circles(window) called in engine.cpp");
	draw_circles(window);
}

void Engine::use_default_settings() {
	/*Settings::borders_on = false;
	Settings::circles_stroke = false;
	Settings::clicking_allowed = true;
	Settings::epsilon = 1;
	Settings::frame_by_frame_debug_on = false;
	Settings::frame_by_frame_lock = false;
	Settings::G = 10;
	Settings::gravity_on = true;
	Settings::g = Vector3D(0, 0.5, 0);
	Settings::gravity_on = false;
	Settings::is_recording = false;
	Settings::logging_on = false;
	Settings::loops_per_frame = 1;
	Settings::mu = 0;
	Settings::newtonian_drag_on = false;
	Settings::next_recording_id = 0;
	Settings::recording_extension = ".png";
	Settings::recording_path = "";
	Settings::stokes_drag_on = false;
	Settings::time_stopped = true;
	Settings::uniform_gravity = false;
	Settings::viscosity = 0;*/
}

void Engine::save_settings() {
	std::cout << "Save settings called\n";
}

void Engine::load_settings() {
	/*if (!fsystem::exists("settings.ini")) {
		use_default_settings();
		save_settings();
		return;
	}*/
	std::ifstream input("settings.ini");
	if (!input.is_open()) {
		//use_default_settings();
		Settings::use_default_settings();
		//save_settings();
		return;
	}
	/*
	std::string buffer;
	try {
		std::getline(input, buffer);
	}
	catch (...) {

	}*/
}