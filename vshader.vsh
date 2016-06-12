#version 330
in vec3 position;
in vec3 color;
in layout(location=3) mat4 modelMatrix;

uniform mat4 projMatrix;

out vec4 vColor;
out vec2 UV;
void main()
{

  gl_Position = projMatrix * modelMatrix *vec4(position, 1.0);
  vColor = vec4(color, 1.0);
  UV = gl_Position.xy;
}

