// Flat Color Shader

#type vertex
#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 viewProjection;
uniform mat4 transform;

void main()
{
	gl_Position = viewProjection * transform* vec4(position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 Color;

uniform vec4 color;

void main()
{
	Color = color;
} 