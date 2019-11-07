#type vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 viewProjection;
uniform mat4 transform;

out vec2 TexCoord;

void main()
{
	gl_Position = viewProjection * transform * vec4(position, 1.0);
	TexCoord = texCoord;
}

#type fragment
#version 330 core

out vec4 fragColor;

in vec2 TexCoord;

uniform vec4 color;
uniform sampler2D diffuse;

void main()
{
	fragColor = texture(diffuse, TexCoord) * color;
}