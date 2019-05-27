//
// Created by kieran on 22/05/19.
//

#include <random>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "init.h"
#include "callbacks.h"
#include "state.h"
#include "menus.h"


void preAllocateModelsAndTextures()
{
    const int ModelNumber = State::numMeshes;
    const int TextureNumber = State::numTextures;
    State::models = std::vector<Model>(ModelNumber);
    State::textures = std::vector<texture>(TextureNumber, texture{-1, 0, nullptr, 0});
    State::scenes = std::vector<aiScene const*> (ModelNumber, nullptr);
}

void init(int argc, char **argv)
{
    State::window_height = 768;
    State::window_width = 1024;

    State::numberFrames = 0;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(State::window_width, State::window_height);
    glutInitWindowPosition(100, 100);
    glutInitContextVersion(3, 2);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutCreateWindow(argv[0]);
    glewInit();


    glutDisplayFunc(render_scene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special_keyboard);
    glutPassiveMotionFunc(mouseMove);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMove);
    glutIdleFunc(idle);
    glutTimerFunc(1000, timer, 1);

    makeMenu();

    Vec3 bgColor = {0.2, 0.3, 0.4};
    glClearColor(bgColor.x, bgColor.y, bgColor.z, 1.0);
    State::fogColor = bgColor;
    State::fogDistance = 1000;
    glEnable(GL_DEPTH_TEST);

    State::program.attachShader({GL_VERTEX_SHADER, "../src/shaders/vertAnimated.glsl", 0});
    State::program.attachShader({GL_FRAGMENT_SHADER, "../src/shaders/frag.glsl", 0});
    State::program.reload();

    preAllocateModelsAndTextures();

    std::random_device device;
    State::randomEngine = std::default_random_engine(device());

    std::uniform_int_distribution<int> modelSelect(1, 55);
    std::uniform_int_distribution<int> textureSelect(2, 30);

    int model = modelSelect(State::randomEngine);
    int objTexture = textureSelect(State::randomEngine);
    int floorTexture = textureSelect(State::randomEngine);

    Vec3 const lightPos1{0, 100, 100};
    Vec3 const lightPos2{0, 100, -100};

    State::camera = Camera{{0,0,0}, 0, -0.2, 1, 150};
    State::currMode = 50;

    State::light1 = {{40, 40, 20}, {55, 4}};
    State::light1.rep.location = lightPos1;
    State::light1.rep.scale = 5;

    State::light2 = {{40, 40, 20}, {55, 4}};
    State::light2.rep.location = lightPos2;
    State::light2.rep.scale = 5;

    State::ambientColor = {1, 1, 1.4};

    State::floor.modelId = 0;
    State::floor.textureId = floorTexture;
    State::floor.scale = 1000;
    State::floor.angles[0] = -M_PI / 2;
    State::floor.shininess = 5;
    State::floor.color = {1, 1, 1};
    State::floor.texScale = 4;
    State::floor.metalicity = 0.5;

    State::objects.emplace_back(model, objTexture);
    State::currObject = State::objects.size() - 1;

}

void loop()
{
    glutMainLoop();
}
