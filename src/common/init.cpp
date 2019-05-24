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


void loadAllModelsAndTextures()
{
    const int ModelNumber = 56;
    const int TextureNumber = 31;

    State::models = std::vector<Model>(ModelNumber, Model{0, 0});
    State::textures = std::vector<texture>(TextureNumber, texture{-1, 0, nullptr, 0});
}

void init(int argc, char **argv)
{
    State::window_height = 768;
    State::window_width = 1024;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(State::window_width, State::window_height);
    glutInitWindowPosition(100, 100);
    glutInitContextVersion(3, 2);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow(argv[0]);
    glewInit();


    glutDisplayFunc(render_scene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special_keyboard);
    glutPassiveMotionFunc(mousePassiveMotion);
    glutIdleFunc(idle);


    glClearColor(0.2, 0.3, 0.4, 1.0);
    glEnable(GL_DEPTH_TEST);

    State::program.attachShader({GL_VERTEX_SHADER, "../src/shaders/vert.glsl", 0});
    State::program.attachShader({GL_FRAGMENT_SHADER, "../src/shaders/frag.glsl", 0});
    State::program.reload();
//    State::shader = initShader("../src/shaders/vert.glsl", "../src/shaders/frag.glsl");
//    glUseProgram(State::shader);

    loadAllModelsAndTextures();

    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> modelSelect(1, 55);
    std::uniform_int_distribution<int> textureSelect(2, 30);

    int model = modelSelect(generator);
    int objTexture = textureSelect(generator);
    int floorTexture = textureSelect(generator);

    State::floor.modelId = 0;
    State::floor.textureId = floorTexture;
    State::floor.scale = 100;
    State::floor.angles[0] = M_PI / 2;

    State::objects.emplace_back(model, objTexture);

    State::models.push_back(Model::initFromFile("../models-textures/model0.x", State::program));
    State::models.push_back(Model::initFromFile("../models-textures/model3.x", State::program));
}

void loop()
{
    glutMainLoop();
}
