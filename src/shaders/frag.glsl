#version 330 core

in vec4 color;
in vec2 texCoord;

out vec4 gl_FragColor;

vec4 procedual_texture(vec2 coord)
{
    ivec2 p = ivec2(ceil(coord * 100));
    if ((p.x + p.y & 1) == 0)
    {
        return vec4(1.0);
    }
    return vec4(vec3(0.0), 1.0);
}

void main()
{
    gl_FragColor = color * procedual_texture(texCoord);
}