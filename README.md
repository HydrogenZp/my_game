# 贪吃蛇游戏

基于C++和ImGui开发的贪吃蛇游戏，支持跨平台运行，集成音效系统。

## 项目特性

- 使用C++11标准开发
- Git版本管理
- ImGui图形界面，支持中文显示
- SDL2_mixer音频支持
- 跨平台兼容（Windows/Linux/macOS）
- 高DPI屏幕适配
- CMake构建系统

## 技术栈

### 核心库
- **[GLFW](https://www.glfw.org/)**：窗口管理和输入处理
- **[Dear ImGui](https://github.com/ocornut/imgui)**：即时模式图形用户界面
- **[SDL2_mixer](https://github.com/libsdl-org/SDL_mixer)**：音频播放和混合
- **OpenGL**：图形渲染

### 工具类
- **Timer**：游戏计时器（`include/utils/Timer.h`）
- **SoundManager**：音频管理器（`include/game/play_sounds.h`）

### 资源文件
- **音效文件**：`sounds/game_start.mp3`、`sounds/game_over.mp3`
- **字体文件**：`fonts/Roboto-VariableFont_wdth,wght.ttf`

## 项目结构

```
game_ws/
├── src/
│   └── main.cpp              # 主程序入口
├── include/
│   ├── game/                 # 游戏功能模块
│   │   ├── play_sounds.h     # 音频管理头文件
│   │   └── play_sounds.cpp   # 音频管理实现
│   ├── utils/                # 工具类
│   │   ├── Timer.h           # 计时器头文件
│   │   └── Timer.cpp         # 计时器实现
│   ├── glfw/                 # GLFW库
│   ├── imgui/                # ImGui库
│   ├── sdl2/                 # SDL2库
│   └── sdl2_mixer/           # SDL2_mixer库
├── sounds/                   # 音效文件
├── fonts/                    # 字体文件
└── CMakeLists.txt           # CMake构建配置
```

## 系统要求

- **CMake** 3.10 或更高版本
- **C++11** 兼容的编译器
  - Windows: Visual Studio 2015+ 或 MinGW
  - Linux: GCC 4.9+ 或 Clang 3.4+


### 1. 克隆项目
```bash
git clone <repository-url>
cd game_ws
```

### 2. 创建构建目录
```bash
mkdir build
cd build
```

### 3. 生成构建文件
```bash
cmake ..
```

### 4. 编译项目
```bash
cmake --build .
```

### 5. 运行游戏
```bash
# Windows
.\gluttonous_snake.exe

# Linux/macOS
./gluttonous_snake
```

## 游戏说明

### 控制方式
- **方向键**：控制蛇的移动方向
- **空格键**：暂停/继续游戏
- **R键**：重新开始游戏

### 游戏规则
- 控制蛇吃食物来增长身体
- 撞到墙壁或自身则游戏结束
- 游戏开始和结束播放音效
- 游戏速度随分数增加而提升

## 依赖库说明

### 第三方库集成
所有依赖库都包含在 `include/` 目录中，无需额外安装：

- **GLFW**：提供跨平台的窗口创建和输入处理
- **ImGui**：轻量级即时模式GUI库，用于游戏界面渲染
- **SDL2/SDL2_mixer**：音频播放库，支持多种音频格式

### Windows特定配置
项目在Windows平台会自动：
- 链接必要的系统库（`opengl32`, `gdi32`, `winmm`等）
- 复制SDL2相关DLL到输出目录
- 配置静态链接以减少依赖

## 开发说明

### 编译配置
- 使用C++11标准
- Debug模式：`-O0`优化级别
- Release模式：`-O2`优化级别
- MinGW：启用静态链接

### 主要类和函数
- `GameState`：游戏状态枚举
- `SnakeSegment`：蛇身段落结构
- `Timer`：高精度计时器类
- `SoundManager`：音频管理单例类

---

### 第三方开源库

使用了以下项目
- [GLFW](https://www.glfw.org/) - 窗口管理库
- [Dear ImGui](https://github.com/ocornut/imgui) - 图形用户界面库
- [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer) - 音频处理库
- [CMake](https://cmake.org/) - 跨平台构建系统
