//
// Created by kieran on 25/05/19.
//

#include <string>
#include <vector>
#include <GL/freeglut.h>
#include <state.h>
#include "menus.h"
#include "state.h"
#include "math3d/mat.h"

std::vector<std::string> const objectMenuEntries = {
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

std::vector<std::string> const textureMenuEntries = {
        "1 Plain", "2 Rust", "3 Concrete", "4 Carpet", "5 Beach Sand",
        "6 Rocky", "7 Brick", "8 Water", "9 Paper", "10 Marble",
        "11 Wood", "12 Scales", "13 Fur", "14 Denim", "15 Hessian",
        "16 Orange Peel", "17 Ice Crystals", "18 Grass", "19 Corrugated Iron", "20 Styrofoam",
        "21 Bubble Wrap", "22 Leather", "23 Camouflage", "24 Asphalt", "25 Scratched Ice",
        "26 Rattan", "27 Snow", "28 Dry Mud", "29 Old Concrete", "30 Leopard Skin"
};

int createArrayMenu(std::vector<std::string> const &entries, void(*menuFn)(int));

void objectMenu(int id);

void materialMenu(int id);

void texMenu(int id);

void groundMenu(int id);

void lightMenu(int id);

void mainMenu(int id);

void makeMenu()
{
    int objectId = createArrayMenu(objectMenuEntries, objectMenu);

    int materialMenuId = glutCreateMenu(materialMenu);
    glutAddMenuEntry("RG/BY/Brightness", 10);
    glutAddMenuEntry("Ambient", 20);
    glutAddMenuEntry("Shininess/Metalicity", 21);

    int texMenuId = createArrayMenu(textureMenuEntries, texMenu);
    int groundMenuId = createArrayMenu(textureMenuEntries, groundMenu);

    int lightMenuId = glutCreateMenu(lightMenu);

    glutAddMenuEntry("Move Light 1", 70);
    glutAddMenuEntry("RG/BY/Brightness Light 1", 71);
    glutAddMenuEntry("Move Light 2", 80);
    glutAddMenuEntry("RG/BY/Brightness Light 2", 81);

    glutCreateMenu(mainMenu);

    glutAddMenuEntry("Rotate Camera", 50);
    glutAddSubMenu("Add object", objectId);
    glutAddMenuEntry("Position/Scale", 41);
    glutAddMenuEntry("Rotation", 55);
    glutAddMenuEntry("Texture scale", 56);
    glutAddSubMenu("Material", materialMenuId);
    glutAddSubMenu("Texture", texMenuId);
    glutAddSubMenu("Ground Texture", groundMenuId);
    glutAddSubMenu("Lights", lightMenuId);
    glutAddMenuEntry("Exit", 99);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mainMenu(int id)
{
    switch (id)
    {
        case 99:
            glutLeaveMainLoop();
            break;
        default:
            State::currMode = id;
            break;
    }
    glutPostRedisplay();
}

void objectMenu(int id)
{
    addObject(id);

    glutPostRedisplay();
}

void materialMenu(int id)
{
    State::currMode = id;

    glutPostRedisplay();
}

int createArrayMenu(std::vector<std::string> const &entries, void(*menuFn)(int))
{
    int size = (int) entries.size();
    int nSubMenus = (size - 1) / 10 + 1;
    int subMenus[nSubMenus];

    for (int i = 0; i < nSubMenus; i++)
    {
        subMenus[i] = glutCreateMenu(menuFn);
        for (int j = i * 10 + 1; j <= std::min(i * 10 + 10, size); j++)
        {
            glutAddMenuEntry(entries[j - 1].c_str(), j);
        }
    }
    int menuId = glutCreateMenu(menuFn);

    for (int i = 0; i < nSubMenus; i++)
    {
        int lower = i * 10 + 1;
        int upper = std::min(i * 10 + 10, size);
        std::string num = std::to_string(lower) + "-" + std::to_string(upper);
        glutAddSubMenu(num.c_str(), subMenus[i]);
    }

    return menuId;
}

void texMenu(int id)
{
    State::objects[State::currObject].textureId = id;

    glutPostRedisplay();
}

void groundMenu(int id)
{
    State::floor.textureId = id;

    glutPostRedisplay();
}

void lightMenu(int id)
{
    State::currMode = id;

    glutPostRedisplay();
}


