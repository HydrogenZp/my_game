# Game Project for *Program Design*

## General

This is a game project designed as part of the lesson *Program Design*. The project leverages modern C++ and integrates libraries such as [GLFW](https://www.glfw.org/) and [Dear ImGui](https://github.com/ocornut/imgui) to create a graphical user interface and handle input/output operations.

The project is structured to be modular and easy to extend, making it suitable for educational purposes and experimentation with game development concepts.

---

## Dependencies

This project relies on the following libraries:

1. **[GLFW](https://www.glfw.org/)**: A library for creating windows, contexts, and surfaces, and receiving input and events.
2. **[Dear ImGui](https://github.com/ocornut/imgui)**: A bloat-free graphical user interface library for C++.

These dependencies are included in the `include/` directory and do not require separate installation.

---

## Building the Project

### Prerequisites

- **CMake**: Ensure you have CMake installed and accessible from your terminal or command prompt.
- **C++ Compiler**: A modern C++ compiler supporting C++17 or later (e.g., GCC, Clang, MSVC).

### Steps to Build

1. **Clone the Repository**:
   ```bash
   git clone <repository-url>
   cd game_ws
   ```

2. **Generate Build Files**:
   Use CMake to generate the necessary build files:
   ```bash
   mkdir build
   cd build
   cmake ..
   ```

3. **Compile the Project**:
   Compile the project using the generated Makefile or solution file:
   ```bash
   cmake --build .
   ```

4. **Run the Executable**:
   Once the build process is complete, the executable will be located in the `build/` directory. Run it as follows:
   ```bash
   ./MyGame
   ```

---

## Running the Game

After successfully building the project, you can run the game by executing the generated binary. The game window will open, and you can interact with it using the mouse and keyboard.

---

## Contributing

This project is primarily intended for educational purposes. If you wish to contribute or extend the functionality, feel free to fork the repository and submit pull requests. Please ensure that your contributions adhere to the following guidelines:

- Follow the existing coding style and conventions.
- Write clear and concise commit messages.
- Include comments and documentation for new features.

---

## Acknowledgments

- **GLFW**: For providing a robust framework for window management and input handling.
- **Dear ImGui**: For enabling rapid prototyping of graphical user interfaces.
- **CMake**: For simplifying the build process across different platforms.

---

