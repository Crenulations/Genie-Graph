#pragma once

#include <GL/glew.h>

#include "glm/glm.hpp";
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include "core/IndexBuffer.h"
#include "core/VertexArray.h"
#include "core/Shader.h"

#include "../Object.h"
#include "Camera.h"
#include "models/NodeModel.h"
#include "models/Model.h"

class Renderer {
public:
	Camera camera;

	Renderer(RuntimeVars* settings);
	void Clear() const;
	void Draw(Model& model) const;
	void DrawNodeModelVerts(NodeModel& nodes) const;
	void DrawNodeModelEdges(NodeModel& nodes) const;
};

glm::mat4 GetModelPositionMat(Position pos);