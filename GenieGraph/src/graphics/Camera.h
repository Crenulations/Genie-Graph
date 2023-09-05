#pragma once
#include <glm/glm.hpp>;
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <string>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include "../util/Basic.h"

class Camera {
private:

	float fov;

	RuntimeVars* settings;


	//glm::mat4 Projection;
public:
	Camera(RuntimeVars* settings);

	void AutoRotate();

	const glm::mat4 GetView() const;

	void printMat4(const char* name, glm::mat4 mat) ;

};