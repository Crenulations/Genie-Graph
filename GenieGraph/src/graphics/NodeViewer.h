#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <utility>

#include "Renderer.h"
#include "Camera.h"
#include "models/Model.h"
#include "../ColonyManager.h"

#include "gui/MainGUI.h"


class NodeViewer {
private:
	GLFWwindow* window;
	Renderer renderer;

	MainGUI main_gui;
	size_t data_size;
	bool show_demo_window = true;


	int current_colony_num = 0;
	Colony* current_colony;
	ColonyManager* colony_manager;

	RuntimeVars* settings;

public:
	NodeViewer(RuntimeVars* settings);
	~NodeViewer();

	void SetColonyManager(ColonyManager* c);

	void Draw();
};