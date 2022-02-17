#version 450 core

in vec4 pass_position;
in vec3 pass_normal;
in vec2 pass_uv;
in vec4 pass_colour;

out vec4 out_colour;

uniform sampler2D mainTex;
uniform vec4 albedo;
uniform float smoothness;
uniform float specular;

void main()
{
    vec4 texCol = texture(mainTex, pass_uv);
    //vec4 uvCol = vec4(pass_uv.xy, 0.0f, 1.0f);

    out_colour = texCol;
    //out_colour = vec4(1, 1, 1, 1);
}