#version 450 core

in vec4 pos;
out vec4 out_colour;

void main()
{
    //out_colour = vec4(1.0, 0.0, 1.0, 1.0);
    out_colour = pos + vec4(1, 1, 0, 0);
}