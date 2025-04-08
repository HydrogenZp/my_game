cmake_minimum_required(VERSION 3.10)
project(MyImGuiProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(include/glfw)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/include/imgui)

add_library(imgui STATIC
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        ${CMAKE_SOURCE_DIR}/include/glfw/include
)

target_link_libraries(imgui PUBLIC glfw)

add_executable(MyImGuiProject src/main.cpp)

target_link_libraries(MyImGuiProject PRIVATE glfw imgui opengl32)

target_include_directories(MyImGuiProject PRIVATE
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        ${CMAKE_SOURCE_DIR}/include/glfw/include
)

if (MINGW)
    target_link_options(MyImGuiProject PRIVATE -mwindows)
endif()