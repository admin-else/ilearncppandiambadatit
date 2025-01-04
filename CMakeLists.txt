cmake_minimum_required(VERSION 3.10.5)

project(game)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

add_executable(game src/main.cc src/app.cc src/shader.cc)
target_compile_options(game PRIVATE -fsanitize=address,undefined)
target_link_options(game PRIVATE -fsanitize=address,undefined)
target_link_libraries(game OpenGL glfw GL GLU GLEW::glew)