#shader vertex#
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 inColor;

out vec3 exColor;

uniform mat4 u_ProjectionMatrix;
uniform mat4 u_WorldMatrix;

void main()
{
    gl_Position = u_ProjectionMatrix * u_WorldMatrix * vec4(position, 1.0);
    exColor = inColor;
}

#shader fragment#
#version 330 core

in vec3 exColor;
out vec4 fragColor;

void main()
{
    fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}