#version 460

layout(location = 0) in float a_X;
layout(location = 1) in float a_Y;
layout(location = 2) in float a_Density;

out float density;

void main()
{
	gl_Position = vec4(a_X, a_Y, 0.0, 1.0);
	density = a_Density;
}