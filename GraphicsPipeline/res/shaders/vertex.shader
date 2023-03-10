#version 330 core

layout(location = 0) in vec4 position; // because gl_Position is vec4
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

void main()
{
   gl_Position = position;
   v_TexCoord = texCoord;
};
