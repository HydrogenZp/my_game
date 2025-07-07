cmake_minimum_required(VERSION 3.10)
project(MyGame)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
endif()

add_subdirectory(include/glfw)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/include/imgui)
set(MINIAUDIO_DIR ${CMAKE_SOURCE_DIR}/include/miniaudio)

add_library(imgui STATIC
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)
add_library(miniaudio STATIC
        ${MINIAUDIO_DIR}/miniaudio.c
)

target_include_directories(imgui PUBLIC
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        ${CMAKE_SOURCE_DIR}/include/glfw/include
        ${CMAKE_SOURCE_DIR}/include/utils
        ${MINIAUDIO_DIR}/
)

# 添加Windows系统库链接
if (WIN32)
    target_link_libraries(imgui PUBLIC
            glfw
            opengl32
            gdi32
    )
else()
    target_link_libraries(imgui PUBLIC glfw)
endif()

add_executable(gluttonous_snake src/main.cpp
        include/utils/Timer.cpp
        include/game/play_sounds.cpp
)

# 添加 include 目录，确保头文件能被找到
target_include_directories(gluttonous_snake PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/utils
        ${CMAKE_SOURCE_DIR}/include/game
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        ${MINIAUDIO_DIR}
)

target_link_libraries(gluttonous_snake PRIVATE
        imgui
        glfw
        miniaudio
)

if (WIN32)
    target_link_libraries(gluttonous_snake PRIVATE
            opengl32
            gdi32
    )
endif()


if (MINGW)
    target_link_options(gluttonous_snake PRIVATE -mwindows)
endif()