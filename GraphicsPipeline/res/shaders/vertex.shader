#version 330 core

layout(location = 0) in vec4 position; // because gl_Position is vec4
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_mvp = mat4(1.0, 0.0, 0.0, 0.0,
                          0.0, 1.0, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0,
                          0.0, 0.0, 0.0, 1.0);

void main()
{
   gl_Position = u_mvp * position;
   v_TexCoord = texCoord;
};
