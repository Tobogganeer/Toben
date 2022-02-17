#version 450 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec4 colour;

out vec4 pass_position;
out vec3 pass_normal;
out vec2 pass_uv;
out vec4 pass_colour;

uniform mat4 mvp;
//uniform mat4 view;
//uniform mat4 proj;
//uniform mat4 tran;


void main()
{
    //vec4 worldPos = tran * position;
    //vec4 finalPos = proj * view * worldPos;
    //vec4 finalPos = tran * position;
    vec4 finalPos = mvp * position;
    //vec4 finalPos = position;

    //pass_position = mvp * position;
    pass_position = finalPos;
    pass_normal = normal;
    pass_uv = uv;
    pass_colour = colour;
    //gl_Position = mvp * position;
    gl_Position = finalPos;
}