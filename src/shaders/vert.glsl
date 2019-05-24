#version 330 core

in vec3 vPosition;
in vec2 vTex;
in vec3 vNormal;

out vec2 texCoord;
out vec4 color;

uniform vec3 Ambient, Diffuse, Specular;
uniform mat4 ModelView;
uniform mat4 Projection;
uniform vec3 light;
uniform float shininess;

void main()
{
    vec4 vpos = vec4(vPosition, 1.0);

    vec3 pos = (ModelView * vpos).xyz;

    vec3 Lvec = light-pos;

    vec3 L = normalize(Lvec);
    vec3 E = normalize(-pos);
    vec3 H = normalize(L + E);

    vec3 N = normalize( (ModelView * vec4(vNormal, 0.0)).xyz);

    texCoord = vTex;
    color = vec4(1.0);
    gl_Position = Projection * ModelView * vec4(vPosition * 0.7, 1.0);
}
