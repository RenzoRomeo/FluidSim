#version 460

in float density;

out vec4 FragColor;

void main()
{
	FragColor = vec4(density, density, density, 1.0);
}