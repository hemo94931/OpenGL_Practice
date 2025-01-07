#version 330 core
out vec4 FragColor;

in vec4 outColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

void main()
{
	vec2 tempCoord;
	tempCoord.x = 1-TexCoord.x;
	tempCoord.y = TexCoord.y;
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, tempCoord), mixValue);
}