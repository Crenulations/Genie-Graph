#pragma once

#include <cstdlib>
#include <cmath>


inline float randFloat() { //MOVE TO A UTILITY HEADER
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

inline float VecMag(float x, float y, float z) {
	return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
}

inline float Sigmoid(float a) {
	return (1 / (1 + exp(-a-2)))-0.5f;
};

struct RuntimeVars {
	bool window_close = false;



	//Simulation Settings
	int focused_colony = 0;
	unsigned int fps = 0;
	bool active = true; 
	bool restart = false;
	int speed = 5;

	// Camera Settings
	bool auto_rotate = true;
	glm::vec3 Translate = glm::vec3(0.0f, 0.0f, -10.0f);;
	glm::vec3 Rotate = glm::vec3(0.0f, 0.0f, 0.0f);
};