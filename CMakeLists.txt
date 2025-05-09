cmake_minimum_required(VERSION 3.10)
project(MyImGuiProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
endif()

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

add_executable(MyImGuiProject src/main.cpp)

target_link_libraries(MyImGuiProject PRIVATE
        imgui
        glfw
        ${CMAKE_THREAD_LIBS_INIT}
)

if (WIN32)
    target_link_libraries(MyImGuiProject PRIVATE
            opengl32
            gdi32
    )
endif()

target_include_directories(MyImGuiProject PRIVATE
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        ${CMAKE_SOURCE_DIR}/include/glfw/include
)

if (MINGW)
    target_link_options(MyImGuiProject PRIVATE -mwindows)
endif()