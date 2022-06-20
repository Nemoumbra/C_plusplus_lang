#pragma once
#include "Functions.h"
#include <string>

class Settings {
public:
	static bool circles_stroke;

	static bool clicking_allowed;

	static bool borders_on;

	static bool time_stopped;

	static int loops_per_frame;

	static double epsilon;

	static bool frame_by_frame_debug_on;
	static bool frame_by_frame_lock;

	static bool uniform_gravity;
	static Vector3D g;
	static double mu;

	// border hit loss

	static bool logging_on;

	static bool gravity_on;
	static double G;

	static bool stokes_drag_on;
	static bool newtonian_drag_on;
	static double viscosity;
	static double newtonian_k;

	static bool is_recording;
	static std::string recording_path;
	static std::string recording_extension;
	static int next_recording_id;

	Settings() = delete;

	static void use_default_settings();
};

