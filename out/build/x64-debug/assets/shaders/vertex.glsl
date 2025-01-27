#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColors;
out vec3 color;
uniform float time;
void main()
{
    float rat = (sin(time) + 1.0) / 2.0;
    float rat2 = sin(time) / 2.0;
    gl_Position = vec4(aPos.x + rat2, aPos.y, aPos.z, 1.0);
    color = aColors * rat;
}