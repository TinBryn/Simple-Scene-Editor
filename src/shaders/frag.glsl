#version 330 core

in vec4 color;
in vec2 texCoord;

uniform sampler2D texture;

out vec4 gl_FragColor;

void main()
{
    gl_FragColor = color * texture2D(texture, texCoord);
}