#include "Object.h"



Object::Object(Model* m) 
	:model(m)
{
	modelData = { randFloat(),randFloat(),randFloat() };
}


	
Object::~Object() {
	std::cout << "DELETING OBJECT" << std::endl;
}

Position* Object::GetPosition() {
	return &position;
}
ModelData Object::GetModelData() {
	return modelData;
}
Model* Object::GetModel() {
	return model;
}

void Object::SetPosition(Position new_pos) {
	position = new_pos;
}
