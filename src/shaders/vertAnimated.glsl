#version 330

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTex;


out vec3 fPosition;
out vec3 fNormal;
out vec3 fLight1;
out vec3 fLight2;
out vec2 texCoord;
out vec3 color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 LightPosition1;
uniform vec3 LightPosition2;

in vec4 boneIDs;
in vec4 boneWeights;
uniform mat4 boneTransforms[64];



mat4 ModelView = View * Model;

void main()
{
    color = vec3(1.0);

    mat4 boneTransform =(
    boneWeights[0] * boneTransforms[int(boneIDs[0])] +
    boneWeights[1] * boneTransforms[int(boneIDs[1])] +
    boneWeights[2] * boneTransforms[int(boneIDs[2])] +
    boneWeights[3] * boneTransforms[int(boneIDs[3])]
    ) / 4;

    //pass the position along to the fragment shader for use in per pixel lighting
    fPosition = (ModelView * boneTransform * vec4(vPosition, 1.0)).xyz;
    fNormal = normalize((ModelView * boneTransform * vec4(vNormal, 0.0)).xyz);

    //for some reason the lights don't render in the correct place
    fLight1 = (View * vec4(LightPosition1, 1.0)).xyz;
    fLight2 = (View * vec4(LightPosition2, 1.0)).xyz;

    texCoord = vTex;
    gl_Position = Projection * ModelView * boneTransform * vec4(vPosition * 0.7, 1.0);
}
