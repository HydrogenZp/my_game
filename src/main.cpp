#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_INCLUDE_NONE

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <imgui_impl_opengl3_loader.h>
#include <Timer.h>
#include <vector>
#include <deque>
#include <random>

// 方向枚举
enum class Direction {
    UP, DOWN, LEFT, RIGHT
};

// 游戏状态枚举
enum class GameState {
    MENU, PLAYING, PAUSED, GAME_OVER
};

// 蛇身体段落结构
struct SnakeSegment {
    int x, y;
};

// 简单的随机数生成函数
int getRandomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

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

    GLFWwindow* window = glfwCreateWindow(1280, 720, "贪吃蛇游戏", NULL, NULL);
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
    io.Fonts->AddFontDefault();
    io.Fonts->AddFontFromFileTTF("c:/windows/fonts/simhei.ttf", 13.0f, NULL,
                                 io.Fonts->GetGlyphRangesChineseFull());

    ImGui::StyleColorsLight();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // 游戏初始化
    const int gridWidth = 40;
    const int gridHeight = 30;
    const int cellSize = 30;
    ImVec2 gridOrigin(50.0f, 50.0f);

    // 蛇初始化
    std::deque<SnakeSegment> snake;
    snake.push_back({10, 7}); // 头部
    snake.push_back({9, 7});
    snake.push_back({8, 7});
    Direction direction = Direction::RIGHT;
    Direction pendingDirection = Direction::RIGHT;

    // 食物初始化
    int foodX = 15, foodY = 7;

    // 游戏状态
    GameState gameState = GameState::MENU;
    int score = 0;
    int highScore = 0;

    // 计时器初始化 - 控制蛇的移动速度
    Timer gameTimer(0.2f);

    // 测试计时器的性能
    Timer fpsTimer(1.0f);
    int frameCount = 0;
    int fps = 0;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // 处理输入
        if (gameState == GameState::PLAYING) {
            if (ImGui::IsKeyPressed(ImGuiKey_UpArrow) && direction != Direction::DOWN) {
                pendingDirection = Direction::UP;
            }
            else if (ImGui::IsKeyPressed(ImGuiKey_DownArrow) && direction != Direction::UP) {
                pendingDirection = Direction::DOWN;
            }
            else if (ImGui::IsKeyPressed(ImGuiKey_LeftArrow) && direction != Direction::RIGHT) {
                pendingDirection = Direction::LEFT;
            }
            else if (ImGui::IsKeyPressed(ImGuiKey_RightArrow) && direction != Direction::LEFT) {
                pendingDirection = Direction::RIGHT;
            }
        }

        if (ImGui::IsKeyPressed(ImGuiKey_Space)) {
            if (gameState == GameState::PLAYING) {
                gameState = GameState::PAUSED;
            } else if (gameState == GameState::PAUSED) {
                gameState = GameState::PLAYING;
            }
        }

        if (ImGui::IsKeyPressed(ImGuiKey_R)) {
            if (gameState == GameState::GAME_OVER || gameState == GameState::PAUSED) {
                // 重置游戏
                snake.clear();
                snake.push_back({10, 7});
                snake.push_back({9, 7});
                snake.push_back({8, 7});
                direction = Direction::RIGHT;
                pendingDirection = Direction::RIGHT;
                foodX = 15;
                foodY = 7;
                score = 0;
                gameState = GameState::PLAYING;
            }
        }

        // 更新游戏状态
        if (gameState == GameState::PLAYING && gameTimer.isReady()) {
            // 更新方向
            direction = pendingDirection;

            // 获取头部位置
            SnakeSegment head = snake.front();

            // 根据方向移动蛇头
            switch (direction) {
                case Direction::UP: head.y--; break;
                case Direction::DOWN: head.y++; break;
                case Direction::LEFT: head.x--; break;
                case Direction::RIGHT: head.x++; break;
            }

            // 检查是否撞墙
            if (head.x < 0 || head.x >= gridWidth || head.y < 0 || head.y >= gridHeight) {
                gameState = GameState::GAME_OVER;
            } else {
                // 检查是否撞到自己
                for (auto it = snake.begin(); it != snake.end(); ++it) {
                    if (head.x == it->x && head.y == it->y) {
                        gameState = GameState::GAME_OVER; // 撞到自己直接GAME_OVER
                        break;
                    }
                }

                if (gameState != GameState::GAME_OVER) {
                    // 检查是否吃到食物
                    bool ateFood = (head.x == foodX && head.y == foodY);

                    // 添加新的头部
                    snake.push_front(head);

                    // 如果没有吃到食物，移除尾部
                    if (!ateFood) {
                        snake.pop_back();
                    } else {
                        // 吃到食物，生成新的食物位置
                        bool validPosition;
                        do {
                            validPosition = true;
                            foodX = getRandomInt(0, gridWidth - 1);
                            foodY = getRandomInt(0, gridHeight - 1);

                            // 确保食物不在蛇身上
                            for (const auto& segment : snake) {
                                if (segment.x == foodX && segment.y == foodY) {
                                    validPosition = false;
                                    break;
                                }
                            }
                        } while (!validPosition);

                        // 增加分数
                        score++;
                        if (score > highScore) {
                            highScore = score;
                        }

                        // 随着分数增加，加快游戏速度
                        float gameSpeed = 1.0f + (score / 10.0f) * 0.5f;
                        gameTimer.setInterval(0.2f / gameSpeed);
                    }
                }
            }
        }

        // 开始ImGui帧
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 测量FPS - 使用Timer类
        frameCount++;
        if (fpsTimer.isReady()) {
            fps = frameCount;
            frameCount = 0;
        }

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(width, height));
        ImGui::Begin("贪吃蛇游戏", nullptr,
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

        // 显示FPS和Timer信息
        ImGui::Text("FPS: %d", fps);
        ImGui::Text("Timer间隔: %.3f秒", gameTimer.getInterval());

        if (gameState == GameState::MENU) {
            // 主菜单
            float windowWidth = ImGui::GetWindowWidth();
            ImVec2 textSize = ImGui::CalcTextSize("贪吃蛇游戏");
            ImGui::SetCursorPosX((windowWidth - textSize.x) / 2.0f);
            ImGui::SetCursorPosY(height * 0.2f);
            ImGui::Text("贪吃蛇游戏");

            ImVec2 buttonSize(200, 50);
            ImGui::SetCursorPosX((windowWidth - buttonSize.x) / 2.0f);
            ImGui::SetCursorPosY(height * 0.5f);
            if (ImGui::Button("开始游戏", buttonSize)) {
                gameState = GameState::PLAYING;
            }
        }
        else {
            // 绘制游戏区域背景
            ImDrawList* drawList = ImGui::GetWindowDrawList();

            // 绘制网格背景
            float gridWidthPx = gridWidth * cellSize;
            float gridHeightPx = gridHeight * cellSize;
            drawList->AddRectFilled(
                ImVec2(gridOrigin.x, gridOrigin.y),
                ImVec2(gridOrigin.x + gridWidthPx, gridOrigin.y + gridHeightPx),
                IM_COL32(50, 50, 50, 255)
            );

            // 绘制边界
            drawList->AddRect(
                ImVec2(gridOrigin.x, gridOrigin.y),
                ImVec2(gridOrigin.x + gridWidthPx, gridOrigin.y + gridHeightPx),
                IM_COL32(255, 255, 255, 255),
                0.0f, 0, 2.0f
            );

            // 绘制食物
            ImVec2 foodPos(
                gridOrigin.x + foodX * cellSize,
                gridOrigin.y + foodY * cellSize
            );
            drawList->AddCircleFilled(
                ImVec2(foodPos.x + cellSize / 2, foodPos.y + cellSize / 2),
                cellSize / 2 - 2,
                IM_COL32(255, 0, 0, 255)
            );

            // 绘制蛇
            for (size_t i = 0; i < snake.size(); i++) {
                const auto& segment = snake[i];
                ImVec2 pos(
                    gridOrigin.x + segment.x * cellSize,
                    gridOrigin.y + segment.y * cellSize
                );

                // 蛇头使用不同颜色
                ImU32 color = (i == 0) ?
                              IM_COL32(220, 50, 50, 255) :  // 红色蛇头
                              IM_COL32(50, 220, 50, 255);   // 绿色蛇身

                // 留一点边距
                float margin = 1.0f;
                drawList->AddRectFilled(
                    ImVec2(pos.x + margin, pos.y + margin),
                    ImVec2(pos.x + cellSize - margin, pos.y + cellSize - margin),
                    color,
                    4.0f  // 圆角
                );
            }

            // 显示得分
            ImGui::SetCursorPos(ImVec2(gridOrigin.x, gridOrigin.y - 30));
            ImGui::Text("得分: %d   最高分: %d", score, highScore);

            // 游戏暂停或结束时显示相应信息
            if (gameState == GameState::PAUSED) {
                ImVec2 center(width / 2, height / 2);
                ImGui::SetCursorPos(ImVec2(center.x - 100, center.y - 50));
                ImGui::BeginChild("PauseWindow", ImVec2(200, 100), true);
                ImGui::Text("游戏已暂停");
                ImGui::Text("按空格键继续");
                ImGui::Text("按R键重新开始");
                ImGui::EndChild();
            }
            else if (gameState == GameState::GAME_OVER) {
                ImVec2 center(width / 2, height / 2);
                ImGui::SetCursorPos(ImVec2(center.x - 100, center.y - 50));
                ImGui::BeginChild("GameOverWindow", ImVec2(500, 500), true);
                ImGui::Text("Game Over!");
                ImGui::Text("Scores : %d", score);
                ImGui::Text("Press R to restart");
                ImGui::EndChild();
            }
        }

        ImGui::End();

        // 结束ImGui帧并渲染
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