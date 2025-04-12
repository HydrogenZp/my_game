
# 小游戏项目

## 项目简介
本项目是一个基于C++开发的小游戏，为*程序设计*课程大作业
## 开发环境
- **操作系统**: Ubuntu
- **版本控制**: Git
- **远程仓库**: GitHub

## 使用的技术与工具
- **CMake**: 用于构建系统，简化编译过程。
- **GLFW**: 用于创建窗口、上下文和管理输入。
- **Dear ImGui**: 用于快速开发图形用户界面。
- **OpenGL**: 提供跨平台的图形渲染功能。

### 主要开源库介绍
1. **GLFW**
    - GLFW 是一个多平台库，用于桌面 OpenGL、OpenGL ES 和 Vulkan 应用程序开发。它提供了一个简单的 API 来创建窗口、上下文和表面，读取输入，以及处理事件等。
    - **许可证**: zlib/libpng license
    - **链接**: [GLFW 官方网站](https://www.glfw.org/)

2. **Dear ImGui**
    - Dear ImGui 是一个轻量级的即时模式 GUI 库，专为 C++ 设计。它输出优化的顶点缓冲区，可以在任何支持 3D 管线的应用程序中随时渲染。ImGui 非常适合需要快速迭代和调试工具的内容创作工具。
    - **许可证**: MIT License
    - **链接**: [Dear ImGui GitHub 仓库](https://github.com/ocornut/imgui)

## 构建与运行

### 构建项目
依赖项：GLFW, Dear ImGUI（include 目录中有其源码）
```bash
mkdir build
cd build
cmake ..
make
```


### 运行游戏
TODO


## 目录结构
```
.
├── CMakeLists.txt          # CMake 配置文件
├── README.md               # 项目说明文档
├── include                 # 头文件目录
│   ├── glfw                # GLFW 相关头文件
│   └── imgui               # Dear ImGui 相关头文件
├── src                     # 源代码目录
│   └── main.cpp            # 主程序入口
└── build                   # 构建输出目录
```

