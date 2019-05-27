#version 330 core

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTex;

out vec3 fPosition;
out vec3 fNormal;
out vec3 fLight1;
out vec3 fLight2;
out vec2 texCoord;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 LightPosition1;
uniform vec3 LightPosition2;


mat4 ModelView = View * Model;

void main()
{
    //pass the position along to the fragment shader for use in per pixel lighting
    fPosition = (ModelView * vec4(vPosition, 1.0)).xyz;
    fNormal = normalize((ModelView * vec4(vNormal, 0.0)).xyz);

    //for some reason the lights don't render in the correct place
    fLight1 = (View * vec4(LightPosition1 * vec3(1.5), 1.0)).xyz;
    fLight2 = (View * vec4(LightPosition2* vec3(1.5), 1.0)).xyz;

    texCoord = vTex;
    gl_Position = Projection * ModelView * vec4(vPosition * 0.7, 1.0);
}
