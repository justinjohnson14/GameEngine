#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TextureCoords;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 outPos;
out vec2 textureCoords;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
	outPos = a_Position;
	textureCoords = a_TextureCoords;
}

#type fragment
#version 330 core

out vec4 color;

uniform float time;
uniform vec4 u_Color;
uniform sampler2D Texture;

in vec3 outPos;
in vec2 textureCoords;

void main()
{
	color = vec4(abs(sin(outPos.x)),abs(sin(outPos.z)), abs(cos(outPos.y)), 1.0);
	//color = vec4(u_Color);
	color = texture(Texture, textureCoords);
	//color = u_color;
}