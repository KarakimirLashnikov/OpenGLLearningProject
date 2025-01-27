#version 460 core
out vec4 FragColor;
in vec3 color;
uniform float time;
void main()
{
    FragColor = vec4(color + (vec3(cos(time) + 1.0) / 2.0), 1.0);
}