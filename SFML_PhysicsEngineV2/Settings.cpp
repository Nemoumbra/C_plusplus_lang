#include "Settings.h"

bool Settings::circles_stroke;

bool Settings::clicking_allowed;

bool Settings::borders_on;

bool Settings::time_stopped;

int Settings::loops_per_frame;

double Settings::epsilon;

bool Settings::frame_by_frame_debug_on;
bool Settings::frame_by_frame_lock;

bool Settings::uniform_gravity;
Vector3D Settings::g;
double Settings::mu;

// border hit loss

bool Settings::logging_on;

bool Settings::gravity_on;
double Settings::G;

bool Settings::stokes_drag_on;
bool Settings::newtonian_drag_on;
double Settings::viscosity;
double Settings::newtonian_k;

bool Settings::is_recording;
std::string Settings::recording_path;
std::string Settings::recording_extension;
int Settings::next_recording_id;

void Settings::use_default_settings() {
	Settings::borders_on = false;
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
	Settings::logging_on = true;
	Settings::loops_per_frame = 1;
	Settings::mu = 0;
	Settings::newtonian_drag_on = false;
	Settings::newtonian_k = 0;
	Settings::next_recording_id = 0;
	Settings::recording_extension = ".png";
	Settings::recording_path = "";
	Settings::stokes_drag_on = false;
	Settings::time_stopped = true;
	Settings::uniform_gravity = false;
	Settings::viscosity = 0;
}