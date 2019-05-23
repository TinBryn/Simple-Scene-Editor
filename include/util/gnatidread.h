// UWA CITS3003
// Graphics 'n Animation Tool Interface & Data Reader (gnatidread.h)

// You shouldn't need to modify the code in this file, but feel free to.
// If you do, it would be good to mark your changes with comments.

//I've tweaked this to work with my linear algebra library and State singleton

#include <iostream>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <math3d/vec.h>
#include <math3d/mat.h>
#include <GL/glut.h>
#include "bitmap.h"
#include "state.h"

char dataDir[256];  // Stores the path to the models-textures folder.
const int numTextures = 31;
const int numMeshes = 56;


// ------Functions to fail with an error message then a string or int------

void failInt(std::string const &msg1, int i);


// -----Texture data reading--------------------------------------------

// A type for a 2D texture, with height and width in pixels


// Load the texture with number num from the models-textures directory
texture loadTextureNum(int num);

//----------------------------------------------------------------------------

// Initialise the Open Asset Importer toolkit
void aiInit();

// Load a mesh by number from the models-textures directory via the Open Asset Importer
aiMesh *loadMesh(int meshNumber);


// -------------- Strings for the texture and mesh menus ---------------------------------

char textureMenuEntries[numTextures][128] = {
        "1 Plain", "2 Rust", "3 Concrete", "4 Carpet", "5 Beach Sand",
        "6 Rocky", "7 Brick", "8 Water", "9 Paper", "10 Marble",
        "11 Wood", "12 Scales", "13 Fur", "14 Denim", "15 Hessian",
        "16 Orange Peel", "17 Ice Crystals", "18 Grass", "19 Corrugated Iron", "20 Styrofoam",
        "21 Bubble Wrap", "22 Leather", "23 Camouflage", "24 Asphalt", "25 Scratched Ice",
        "26 Rattan", "27 Snow", "28 Dry Mud", "29 Old Concrete", "30 Leopard Skin"
};

char objectMenuEntries[numMeshes][128] = {
        "1 Thin Dinosaur", "2 Big Dog", "3 Saddle Dinosaur", "4 Dragon", "5 Cleopatra",
        "6 Bone I", "7 Bone II", "8 Rabbit", "9 Long Dragon", "10 Buddha",
        "11 Sitting Rabbit", "12 Frog", "13 Cow", "14 Monster", "15 Sea Horse",
        "16 Head", "17 Pelican", "18 Horse", "19 Kneeling Angel", "20 Porsche I",
        "21 Truck", "22 Statue of Liberty", "23 Sitting Angel", "24 Metal Part", "25 Car",
        "26 Apatosaurus", "27 Airliner", "28 Motorbike", "29 Dolphin", "30 Spaceman",
        "31 Winnie the Pooh", "32 Shark", "33 Crocodile", "34 Toddler", "35 Fat Dinosaur",
        "36 Chihuahua", "37 Sabre-toothed Tiger", "38 Lioness", "39 Fish", "40 Horse (head down)",
        "41 Horse (head up)", "42 Skull", "43 Fighter Jet I", "44 Toad", "45 Convertible",
        "46 Porsche II", "47 Hare", "48 Vintage Car", "49 Fighter Jet II", "50 Gargoyle",
        "51 Chef", "52 Parasaurolophus", "53 Rooster", "54 T-rex", "55 Sphere"
};


//-----Code for using the mouse to adjust floats - you shouldn't need to modify this code.
// Calling setTool(vX, vY, vMat, wX, wY, wMat) below makes the left button adjust *vX and *vY
// as the mouse moves in the X and Y directions, via the transformation vMat which can be used
// for scaling and rotation. Similarly the middle button adjusts *wX and *wY via wMat.
// Any of vX, vY, wX, wY may be NULL in which case nothing is adjusted for that component.

static Vec2 prevPos;
static Mat2 leftTrans, middTrans;
static int currButton = -1;

void doNothingCallback(Vec2 xy);

static void (*leftCallback)(Vec2) = &doNothingCallback;

static void (*middCallback)(Vec2) = &doNothingCallback;

static int mouseX = 0, mouseY = 0;         // Updated in the mouse-passive-motion function.

Vec2 currMouseXYscreen(float x, float y)
{
    return Vec2(x / State::window_width, (State::window_height - y) / State::window_height);
}

void doToolUpdateXY(int x, int y);

static Mat2 rotZ(float rotSidewaysDeg);

//static vec2 currXY(float rotSidewaysDeg) { return rotZ(rotSidewaysDeg) * vec2(currRawX(), currRawY()); }
Vec2 currMouseXYworld(float rotSidewaysDeg);

// See the comment about 40 lines above
void setToolCallbacks(void(*newLeftCallback)(Vec2 transformedMovement), Mat2 leftT,
                             void(*newMiddCallback)(Vec2 transformedMovement), Mat2 middT);

static Vec2 clickPrev;

void activateTool(int button);

void deactivateTool();

//-------------------------------------------------------------
