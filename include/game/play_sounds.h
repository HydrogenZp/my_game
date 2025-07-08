#ifndef PLAY_SOUNDS_H
#define PLAY_SOUNDS_H

#include <string>

// 前向声明SDL2_mixer类型
#ifdef _WIN32
// Windows上使用void*来表示SDL结构体
typedef void Mix_Chunk;
typedef void Mix_Music;
typedef unsigned short Uint16;
#else
// Linux/Unix系统包含实际的SDL2_mixer头文件
#include <SDL2/SDL_mixer.h>
#endif

class SoundManager {
public:
    static bool initialize();
    static void cleanup();
    static bool playSound(const std::string& soundPath);
    static bool playMusic(const std::string& musicPath, int loops = -1);
    static void stopMusic();
    static void pauseMusic();
    static void resumeMusic();
    static void setMusicVolume(int volume); // 0-128
    static void setSoundVolume(int volume); // 0-128
    static bool isMusicPlaying();

private:
    static bool isInitialized;
};

#endif // PLAY_SOUNDS_H
