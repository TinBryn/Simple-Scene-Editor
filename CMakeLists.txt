cmake_minimum_required(VERSION 3.12)
project(CITS3003)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(CITS3003 src/main.cpp include/math3d/fwdtypes.h include/math3d/vec.h include/math3d/mat.h include/init.h src/math3d/vec2.cpp src/math3d/vec3.cpp src/math3d/vec4.cpp src/math3d/mat2.cpp src/math3d/mat3.cpp src/math3d/mat4.cpp include/callbacks.h src/common/callbacks/render_scene.cpp src/common/callbacks/keyboard_callback.cpp src/common/callbacks/idle_callback.cpp include/state.h src/common/state.cpp src/common/init.cpp include/model.h src/common/model.cpp include/util/shaders.h src/util/shaders.cpp src/common/resize.cpp include/scene_object.h include/util/bitmap.h include/texture.h src/common/bitmap.cpp src/common/texture.cpp include/camera.h src/common/scene_object.cpp src/common/callbacks/object_menu.cpp src/common/callbacks/mouse_callback.cpp include/mouse.h src/common/callbacks/menu.cpp)

target_link_libraries(CITS3003 GL GLEW glut assimp)