#version 330 core

in vec3 vPosition;
in vec2 vTex;
in vec3 vNormal;

out vec2 texCoord;
out vec4 color;

uniform vec3 Ambient, Diffuse, Specular;
uniform mat4 ModelView;
uniform mat4 Projection;
uniform vec4 light;
uniform float shininess;

void main()
{
    texCoord = vTex;
    color = vec4(1.0);
    gl_Position = ModelView * vec4(vPosition * 0.7, 1.0);
}
