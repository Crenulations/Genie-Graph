#shader vertex
#version 440 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color; 

uniform mat4 u_MVP;
smooth out vec4 vert_color;

void main() {
	gl_Position = u_MVP * position;
	vert_color = color;
};

#shader fragment
#version 440 core

layout(location = 0) out vec4 color;

smooth in vec4 vert_color;

uniform vec4 u_Color;

void main() {
	color = vert_color;
};
