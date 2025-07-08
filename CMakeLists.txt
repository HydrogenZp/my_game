cmake_minimum_required(VERSION 3.10)
project(MyGame)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
    set(CMAKE_C_FLAGS_DEBUG "-O0")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0")
    set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
endif()

add_subdirectory(include/glfw)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/include/imgui)
set(SDL2_MIXER_DIR ${CMAKE_SOURCE_DIR}/include/sdl2_mixer)

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
        ${CMAKE_SOURCE_DIR}/include/utils
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
        ${SDL2_MIXER_DIR}
)

# 链接SDL2_mixer库
if (WIN32)
    target_link_libraries(gluttonous_snake PRIVATE
            ${SDL2_MIXER_DIR}/SDL2_mixer.dll
    )
endif()

target_link_libraries(gluttonous_snake PRIVATE
        imgui
        glfw
)

if (WIN32)
    target_link_libraries(gluttonous_snake PRIVATE
            opengl32
            gdi32
            winmm
            ole32
            user32
    )
endif()

if (MINGW)
    target_link_options(gluttonous_snake PRIVATE -mwindows)
endif()

# 复制SDL2和SDL2_mixer DLL以及相关库到输出目录
if (WIN32)
    # 复制SDL2.dll
    add_custom_command(TARGET gluttonous_snake POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/include/sdl2/SDL2.dll"
            $<TARGET_FILE_DIR:gluttonous_snake>)
    
    # 复制SDL2_mixer.dll
    add_custom_command(TARGET gluttonous_snake POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_MIXER_DIR}/SDL2_mixer.dll"
            $<TARGET_FILE_DIR:gluttonous_snake>)

    # 复制可选的音频格式支持库
    add_custom_command(TARGET gluttonous_snake POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${SDL2_MIXER_DIR}/optional"
            $<TARGET_FILE_DIR:gluttonous_snake>)
endif()
