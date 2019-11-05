#version 330 core
layout (location = 0) in vec3 in_Pos;
layout (location = 1) in vec3 in_Color;
layout (location = 2) in vec2 in_TexCoord;

out vec3 temp_Color;
out vec2 temp_TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(in_Pos, 1.0f);
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x,aTexCoord.y);
}