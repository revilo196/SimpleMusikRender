#version 330
in vec3 position;
in vec3 tex;

out vec2 UV;


void main()
{
    gl_Position = vec4(position , 1.0);
    UV = tex.xy;
}

