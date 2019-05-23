cmake_minimum_required(VERSION 3.12)
project(CITS3003)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(CITS3003 src/main.cpp include/math3d/fwdtypes.h include/math3d/vec.h include/math3d/mat.h include/init.h src/math3d/vec2.cpp src/math3d/vec3.cpp src/math3d/vec4.cpp src/math3d/mat2.cpp src/math3d/mat3.cpp src/math3d/mat4.cpp include/callbacks.h src/common/render_scene.cpp src/common/keyboard_callback.cpp src/common/idle_callback.cpp include/state.h src/common/state.cpp src/common/init.cpp include/model.h src/common/model.cpp include/util/shaders.h src/util/shaders.cpp src/common/resize.cpp)

target_link_libraries(CITS3003 GL GLEW glut)