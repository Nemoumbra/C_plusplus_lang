#pragma once
#include <SFML/Graphics.hpp>

using Vector2D = sf::Vector2 <double>;
using Vector3D = sf::Vector3 <double>;

double PI();

inline const std::string bool_to_string(bool value) {
	return std::string(value ? "true" : "false");
}

double length(const Vector2D& vec);
double length(const Vector3D& vec);

double len_squared(const Vector2D& vec);
double len_squared(const Vector3D& vec);

void normalize(Vector2D& vec);
void normalize(Vector3D& vec);


double dot(const Vector2D& vec1, const Vector2D& vec2);
double dot(const Vector3D& vec1, const Vector3D& vec2);

double angle(const Vector2D& vec1, const Vector2D& vec2);
double angle(const Vector3D& vec1, const Vector3D& vec2);


double cross(const Vector2D& vec1, const Vector2D& vec2);
Vector3D cross(const Vector3D& vec1, const Vector3D& vec2);

void rotate(Vector2D& vec, double phi);

Vector2D project(const Vector2D& vec1, const Vector2D& vec2);

Vector2D remove_z(const Vector3D& vec);