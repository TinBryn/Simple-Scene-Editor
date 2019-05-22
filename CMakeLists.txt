cmake_minimum_required(VERSION 3.14)
project(CITS3003)

set(CMAKE_CXX_STANDARD 11)

add_executable(CITS3003 src/main.cpp include/math3d/fwdtypes.h include/math3d/vec.h include/math3d/mat.h common/shader_init.h common/shader_init.cpp common/init.h include/math3d/vec2.cpp include/math3d/vec3.cpp include/math3d/vec4.cpp include/math3d/mat2.cpp include/math3d/mat3.cpp include/math3d/mat4.cpp common/callbacks.h common/render_scene.cpp common/keyboard_callback.cpp common/idle_callback.cpp common/state.h common/state.cpp common/init.cpp)

target_link_libraries(CITS3003 GL GLEW glut)