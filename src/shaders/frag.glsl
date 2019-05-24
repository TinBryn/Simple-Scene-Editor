#version 330 core

in vec2 texCoord;
in vec3 lVec;
in vec3 fPos;
in vec3 fNormal;

uniform sampler2D texture;

uniform vec3 lightColor;

out vec4 gl_FragColor;

void main()
{
    vec3 L = normalize(lVec);
    vec3 E = normalize(-fPos);
    vec3 H = normalize(L + E);

    vec3 N = normalize(fNormal);

    float Kd = max( dot(L, N), 0.0);

    vec3 ambient = vec3(0.3);

    vec3 diffuse = vec3(Kd);

    float Ks = pow( max (dot(N, H), 0.0), 1000);
    vec3 specular = vec3(Ks);

    vec4 color = vec4(1.0);
    color.rgb = ambient + diffuse + specular;

    gl_FragColor = color * texture2D(texture, texCoord);
}