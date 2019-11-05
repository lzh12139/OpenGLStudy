#version 330 core

out vec4 out_FragColor;

in vec3 temp_Color;
in vec2 temp_TexCoord;

uniform sampler2D Mytexture;

void main()
{
	FragColor = texture(Mytexture,TexCoord);
}