#version 330
in vec4 vColor;
in vec2 UV;
layout(location = 0) out vec4 fColor;

//layout(location = 1) out vec3 color;

uniform sampler2D tex;
uniform bool dos;

void main()
{
    if(dos)
    fColor = texture2D(tex,UV);
    else
    fColor = vColor.rgba;
    //fColor = vec3(1.0,0,0);
}
