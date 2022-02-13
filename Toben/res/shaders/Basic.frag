#version 450 core

in vec4 pass_position;
in vec3 pass_normal;
in vec2 pass_uv;
in vec4 pass_colour;

out vec4 out_colour;

uniform sampler2D mainTex;

void main()
{
    vec4 texCol = texture(mainTex, pass_uv);
    vec4 col = pass_colour;

    out_colour = texCol * col;
}