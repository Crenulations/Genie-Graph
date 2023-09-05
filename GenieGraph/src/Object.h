#pragma once
#include "graphics/models/Model.h"
#include "util/Basic.h"

struct Position {
	float x, y, z;
};

struct ModelData {
	float r, g, b;
};

class Object {
public:
	Position position;
	ModelData modelData;
	Model* model;
public:
	Object(Model* model);
	~Object();

	Position* GetPosition();
	ModelData GetModelData();
	Model* GetModel();

	void SetPosition(Position new_pos);
};