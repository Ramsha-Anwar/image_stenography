cmake_minimum_required(VERSION 3.10)
project(SteganographyImGui)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCES src/*.cpp include/*.h include/glad/src/glad.c)

find_package(OpenCV REQUIRED)
find_package(glfw3 REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(SteganographyImGui ${SOURCES})

target_link_libraries(SteganographyImGui PRIVATE glfw ${OpenCV_LIBS} imgui::imgui ${CMAKE_DL_LIBS})
