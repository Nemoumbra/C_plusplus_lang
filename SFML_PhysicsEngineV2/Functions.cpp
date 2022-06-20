//#pragma once
#include <SFML/Graphics.hpp>
#include "Functions.h"

 double PI() {
	return std::atan(1) * 4;
}


double length(const Vector2D& vec) {
	return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}
double length(const Vector3D& vec) {
	return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double len_squared(const Vector2D& vec) {
	return vec.x * vec.x + vec.y * vec.y;
}
double len_squared(const Vector3D& vec) {
	return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

void normalize(Vector2D& vec) {
	double len = length(vec);
	vec.x /= len;
	vec.y /= len;
}
void normalize(Vector3D& vec) {
	double len = length(vec);
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
}

double dot(const Vector2D& vec1, const Vector2D& vec2) {
	return vec1.x * vec2.x + vec1.y * vec2.y;
}
double dot(const Vector3D& vec1, const Vector3D& vec2) {
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

double angle(const Vector2D& vec1, const Vector2D& vec2) {
	return std::acos(dot(vec1, vec2) / (length(vec1) * length(vec2)));
}
double angle(const Vector3D& vec1, const Vector3D& vec2) {
	return std::acos(dot(vec1, vec2) / (length(vec1) * length(vec2)));
}

double cross(const Vector2D& vec1, const Vector2D& vec2) {
	return vec1.x * vec2.y - vec1.y * vec2.x;
}
Vector3D cross(const Vector3D& vec1, const Vector3D& vec2) {
	return Vector3D(
		vec1.y * vec2.z - vec1.z * vec2.y, 
		vec1.z * vec2.x - vec1.x * vec2.z,
		vec1.x * vec2.y - vec1.y * vec2.x
	);
}

void rotate(Vector2D& vec, double phi) {
	double cos = std::cos(phi), sin = std::sin(phi);
	vec.x = vec.x * cos - vec.y * sin;
	vec.y = vec.x * sin + vec.y * cos;
}

Vector2D project(const Vector2D& vec1, const Vector2D& vec2) {
	return (dot(vec1, vec2) / len_squared(vec2)) * vec2;
}

Vector2D remove_z(const Vector3D& vec) {
	return Vector2D(vec.x, vec.y);
}