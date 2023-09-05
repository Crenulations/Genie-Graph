#include "Camera.h"



Camera::Camera(RuntimeVars* settings) 
	:settings(settings)
{
	fov = 0.3f;
}

void Camera::AutoRotate() {
	settings->Rotate.x += 0.001f;
	settings->Rotate.y += 0.005f;
	settings->Rotate.z += 0.0001f;
}

const glm::mat4 Camera::GetView() const{
	glm::mat4 Projection = glm::perspective(glm::pi<float>() * fov, 1920.0f/1080, 0.001f, 10000.0f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), settings->Translate);
	View = glm::rotate(View, settings->Rotate.x, glm::vec3(1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, settings->Rotate.y, glm::vec3(0.0f, 1.0f, 0.0f));
	View = glm::rotate(View, settings->Rotate.z, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 persp = Projection * View;

	return persp;
}

void Camera::printMat4(const char* name, glm::mat4 mat) {
	//std::cout << glm::to_string(m) << std::endl;
	std::cout << name << std::endl;
	for (int y = 0; y < 4; y++) {
		std::cout << "| ";

		for (int x = 0; x < 4; x++) {
			std::cout << mat[x][y];
			if(x!=3)
				std::cout << " , ";
		}
		std::cout << " |" << std::endl;
	}

}