#version 450 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec4 colour;

out vec4 pass_position;
out vec3 pass_normal;
out vec2 pass_uv;
out vec4 pass_colour;

void main()
{
    pass_position = position;
    pass_normal = normal;
    pass_uv = uv;
    pass_colour = colour;
    gl_Position = position;
}