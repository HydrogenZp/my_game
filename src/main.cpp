#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_INCLUDE_NONE

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <imgui_impl_opengl3_loader.h>

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "ImGui + GLFW Demo", NULL, NULL);
    if (!window) return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //高DPI适配
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    float xScale, yScale;
    glfwGetMonitorContentScale(monitor, &xScale, &yScale);
    io.DisplayFramebufferScale = ImVec2(xScale, yScale);
    ImGui::GetStyle().ScaleAllSizes(xScale);
    ImFontConfig fontConfig;
    fontConfig.SizePixels = 16.0f;
    ImFont* font = io.Fonts->AddFontFromFileTTF("../fonts/Roboto-VariableFont_wdth,wght.ttf", 32.0f * xScale, &fontConfig); // 或者直接使用xScale调整大小

    IM_ASSERT(font != nullptr);
    io.FontDefault = font;

    ImGui::StyleColorsLight();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(width, height));
        ImGui::Begin("Hello, world!", nullptr,
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

        ImVec2 buttonSize(width * 0.15f, height * 0.15f);
        ImVec2 buttonPos(
            (width - buttonSize.x) / 2.0f,
            (height - buttonSize.y) / 2.0f + 0.2f * height
        );

        ImGui::SetCursorPos(buttonPos);
        ImGui::Button("Start", buttonSize);

        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}