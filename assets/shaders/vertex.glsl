#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColors;
uniform mat4 view;
uniform mat4 transform;
uniform mat4 projection;
out vec3 ourColor;
void main()
{
    gl_Position =  projection * view *  vec4(aPos, 1.0);
    ourColor = aColors;
}