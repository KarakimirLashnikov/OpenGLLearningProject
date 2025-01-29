#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColors;
layout (location = 2) in vec2 aUV;
out vec3 color;
out vec2 uv;
uniform float time;
void main()
{
    float rat = (sin(time) + 1.0) / 2.0;
    float rat2 = sin(time) / 2.0;
    float detaU = time * 0.1;
    float scale = 1.0 / time;
    vec3 sPos = aPos * scale;
    gl_Position = vec4(sPos.x + rat2, sPos.y, sPos.z, 1.0);
    color = aColors * rat;
    uv = vec2(aUV.x + detaU, aUV.y);
}