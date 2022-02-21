#version 450 core

//https://learnopengl.com/Lighting/Basic-Lighting

in vec4 pass_position;
in vec3 worldPosition;
in vec3 pass_normal;
in vec3 worldNormal;
in vec2 pass_uv;
in vec4 pass_colour;

out vec4 out_colour;

uniform sampler2D mainTex;
uniform vec4 albedo;
uniform float smoothness;
uniform float specular;

uniform vec3 lightColour;
uniform vec3 lightDir;
uniform vec3 viewPos;

void main()
{
    vec4 texCol = texture(mainTex, pass_uv);

    float ambientStr = 0.1f;
    vec4 ambient = vec4(lightColour.xyz, 1.0f) * ambientStr;

    vec3 norm = normalize(worldNormal);
    vec3 light = normalize(lightDir); // just in case they arent normalized

    float minDiff = 0.2f;
    float diff = max(dot(norm, lightDir), minDiff);
    vec4 diffuse = diff * vec4(lightColour, 1.0f);

    vec3 viewDir = normalize(viewPos - worldPosition);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec4 specularCol = vec4(specular * spec * lightColour, 1.0f);

    //vec4 result = (ambient + diffuse + specularCol) * albedo * pass_colour;
    //vec4 result = (ambient + diffuse) * albedo * pass_colour;
    vec4 result = (ambient + diffuse + specularCol) * pass_colour * texCol * albedo;
    result.w = 1.0f;

    out_colour = result;
    //out_colour = vec4(pass_uv.xy, 0.0f, 1.0f);
    //out_colour = vec4(pass_normal.xyz, 1.0f);
    //out_colour = vec4(worldNormal.xyz, 1.0f);
}