#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;

out vec3 pos;

uniform mat4 u_Projection;
uniform mat4 u_Model;
uniform mat4 u_View;

void main()
{ 
	gl_Position = vec4(a_Position, 1.0);
	pos = a_Position;
}

#type fragment
#version 330 core

out vec4 color;

in vec3 pos;

void main()
{
	color = vec4(0.0, 0.0, 0.0, 1.0);
}