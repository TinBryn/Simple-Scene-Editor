//
// Created by kieran on 23/05/19.
//

#include "util/gnatidread.h"

void failInt(std::string const &msg1, int i)
{
    std::cerr << msg1 << " " << i << std::endl;
    exit(1);
}

texture loadTextureNum(int num)
{
    if (num < 0 || num >= numTextures)
        failInt("Error in loading texture - wrong texture number:", num);

    char fileName[220];
    sprintf(fileName, "%s/texture%d.bmp", dataDir, num);
    texture t{};
    t.open(fileName);
    return t;
}

void aiInit()
{
    aiLogStream stream{};

    // get a handle to the predefined STDOUT log stream and attach
    // it to the logging system. It remains active for all further
    // calls to aiImportFile(Ex) and aiApplyPostProcessing.
    stream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT, nullptr);
    aiAttachLogStream(&stream);

    // ... same procedure, but this stream now writes the
    // log messages to assimp_log.txt
    stream = aiGetPredefinedLogStream(aiDefaultLogStream_FILE, "assimp_log.txt");
    aiAttachLogStream(&stream);
}

aiMesh *loadMesh(int meshNumber)
{
    char filename[256];
    sprintf(filename, "%s/model%d.x", dataDir, meshNumber);
    const aiScene *scene = aiImportFile(filename, aiProcessPreset_TargetRealtime_Quality
                                                  | aiProcess_ConvertToLeftHanded);
    return scene->mMeshes[0];
}

void doToolUpdateXY(int x, int y)
{
    if (currButton == GLUT_LEFT_BUTTON || currButton == GLUT_MIDDLE_BUTTON)
    {
        Vec2 currPos = Vec2(currMouseXYscreen(x, y));
        if (currButton == GLUT_LEFT_BUTTON)
            leftCallback(leftTrans * (currPos - prevPos));
        else
            middCallback(middTrans * (currPos - prevPos));

        prevPos = currPos;
        glutPostRedisplay();
    }
}

Mat2 rotZ(float rotSidewaysDeg)
{
    return Mat2(1).rotated(rotSidewaysDeg * M_PI / 180.0);
}

Vec2 currMouseXYworld(float rotSidewaysDeg)
{ return rotZ(rotSidewaysDeg) * currMouseXYscreen(mouseX, mouseY); }

void setToolCallbacks(void (*newLeftCallback)(Vec2), Mat2 leftT, void (*newMiddCallback)(Vec2), Mat2 middT)
{

    leftCallback = newLeftCallback;
    leftTrans = leftT;
    middCallback = newMiddCallback;
    middTrans = middT;

    currButton = -1;  // No current button to start with

    // std::cout << leftXYold << " " << middXYold << std::endl; // For debugging
}

void activateTool(int button)
{
    currButton = button;
    clickPrev = currMouseXYscreen(mouseX, mouseY);

    // std::cout << clickOrigin << std::endl;  // For debugging
}

void deactivateTool()
{
    currButton = -1;
}

void doNothingCallback(Vec2 xy)
{}
