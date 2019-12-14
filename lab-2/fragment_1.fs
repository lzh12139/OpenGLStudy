#version 330 core

out vec4 out_FragColor;

in vec3 temp_Color;
in vec2 temp_TexCoord;

uniform sampler2D Mytexture;

void main()
{
	out_FragColor = texture(Mytexture,temp_TexCoord);
	//out_FragColor.x=out_FragColor.x*temp_Color.x;
	//out_FragColor.y=out_FragColor.y*temp_Color.y;
	//out_FragColor.z=out_FragColor.z*temp_Color.z;
}