#version 330 core

in vec3 vPosition;
in vec2 vTex;
in vec3 vNormal;

out vec2 texCoord;
out vec3 lVec;
out vec3 fPos;
out vec3 fNormal;

uniform vec3 Ambient, Diffuse, Specular;
uniform mat4 ModelView;
uniform mat4 Projection;
uniform float shininess;
uniform vec3 LightPosition;

void main()
{
    fPos = (ModelView * vec4(vPosition, 1.0)).xyz;
    lVec = LightPosition - fPos;

    fNormal = (vec4(vNormal, 0.0) ).xyz;

    texCoord = vTex;
    gl_Position = Projection * ModelView * vec4(vPosition * 0.7, 1.0);
}
