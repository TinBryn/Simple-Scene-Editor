#version 330

in vec3 fPosition;
in vec3 fNormal;
in vec3 fLight1;
in vec3 fLight2;
in vec2 texCoord;
in vec3 color;

out vec4 gl_FragColor;

uniform sampler2D texture;
uniform float shininess;
uniform vec3 Ambient;
uniform vec3 LightColor1;
uniform vec3 LightColor2;
uniform vec3 objectColor;
uniform float textureScale;
uniform float metalicity;
uniform float fogDistance;
uniform vec3 fogColor;

vec3 binom(float x, vec3 a, vec3 b)
{
    float y = 1-x;
    return a * y + b * x;
}

//An exposure function allows me to use lights that are brighter white without clipping the color
vec3 exposure(vec3 hdr)
{
    return vec3(1.0) - exp(-hdr);
}

float exposure(float f)
{
    return 1.0 - exp(-f);
}

float lengthFun(float len)
{
    float a = 0.0006;
    float b = 0.001;
    float c = 0.001;
    return 1 / (a * len*len + b * len + c);
}


void main()
{
    vec3 E = normalize(-fPosition);
    vec3 N = normalize(fNormal);
    float true_shiny = exp(shininess);

    vec3 texColor = texture2D(texture, texCoord * vec2(textureScale)).rgb * objectColor;

    //Calculations for light 1
    float lDist1 = length(fLight1 - fPosition);
    float drop1 = lengthFun(lDist1);

    vec3 L1 = normalize(fLight1 - fPosition);
    vec3 H1 = normalize(L1 + E);

    float Kd1 = max(dot(L1, N), 0);
    float Ks1 = 0;
    if (Kd1 > 0)
    Ks1 = pow(max(dot(N, H1), 0), true_shiny);

    Kd1 = drop1 * Kd1;
    Ks1 = drop1 * Ks1 * exposure(true_shiny - 1);

    vec3 diffuseColor1 = LightColor1 * Kd1;
    vec3 specularColor1 = LightColor1 * Ks1;

    //Calculations for light 2
    float lDist2 = length(fLight2 - fPosition);
    float drop2 = lengthFun(lDist2);

    vec3 L2 = normalize(fLight2 - fPosition);
    vec3 H2 = normalize(L2 + E);

    float Kd2 = max(dot(L2, N), 0);
    float Ks2 = 0;
    if (Kd2 > 0)
    Ks2 = pow(max(dot(N, H2), 0), true_shiny);

    Kd2 = drop2 * Kd2;
    Ks2 = drop2 * Ks2 * exposure(true_shiny - 1);

    vec3 diffuseColor2 = LightColor2 * Kd2;
    vec3 specularColor2 = LightColor2 * Ks2;

    //Add up each light's effect
    vec3 diffuseColor = diffuseColor1 + diffuseColor2;
    vec3 specularColor = specularColor1 + specularColor2;

    //metalicity is the amount of light that gets specularly reflected, this is used so that there is conservation of
    //energy, ala it increases specular reflections and decreases diffuse reflections
    vec3 lightColor = binom(metalicity, (diffuseColor + Ambient) * texColor, specularColor);

    //how much fog is between the object and the camera, this also uses the exposure function so fog never
    //actually completely obscures anything in theory. Practically it still gets very foggy and you can't
    //see anything
    float fog = exposure(fPosition.z / fogDistance);

    gl_FragColor = vec4(binom(fog, exposure(lightColor), fogColor) * color, 1.0);
}