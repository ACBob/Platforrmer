#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

void main()
{
	float horzMix = distance(fragTexCoord.y,1) - 0.25;
	vec3 color1 = vec3(0.854,0.987,1.0);
	vec3 color2 = vec3(0.612,0.922,0.952);

    finalColor = vec4(mix(color1, color2, horzMix), 1);
}