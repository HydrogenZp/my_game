#include "play_sounds.h"
#include <iostream>
#include <unordered_map>

#ifdef _WIN32
#include <windows.h>
// Windows上动态加载SDL2_mixer
static HMODULE sdl2_mixer_dll = nullptr;

// SDL2主库函数指针定义
typedef int (*SDL_Init_t)(unsigned int flags);
typedef void (*SDL_Quit_t)(void);
typedef const char* (*SDL_GetError_t)(void);

// SDL2_mixer函数指针定义
typedef int (*Mix_OpenAudio_t)(int frequency, Uint16 format, int channels, int chunksize);
typedef int (*Mix_Init_t)(int flags);
typedef void (*Mix_Quit_t)(void);
typedef void (*Mix_CloseAudio_t)(void);
typedef Mix_Chunk* (*Mix_LoadWAV_t)(const char* file);
typedef Mix_Music* (*Mix_LoadMUS_t)(const char* file);
typedef int (*Mix_PlayChannel_t)(int channel, Mix_Chunk* chunk, int loops);
typedef int (*Mix_PlayMusic_t)(Mix_Music* music, int loops);
typedef void (*Mix_HaltMusic_t)(void);
typedef void (*Mix_FreeChunk_t)(Mix_Chunk* chunk);
typedef void (*Mix_FreeMusic_t)(Mix_Music* music);
typedef int (*Mix_VolumeMusic_t)(int volume);
typedef int (*Mix_Volume_t)(int channel, int volume);
typedef int (*Mix_PlayingMusic_t)(void);
typedef int (*Mix_PausedMusic_t)(void);
typedef void (*Mix_PauseMusic_t)(void);
typedef void (*Mix_ResumeMusic_t)(void);
typedef const char* (*Mix_GetError_t)(void);

// SDL2主库函数指针变量
static HMODULE sdl2_dll = nullptr;
static SDL_Init_t SDL_Init_ptr = nullptr;
static SDL_Quit_t SDL_Quit_ptr = nullptr;
static SDL_GetError_t SDL_GetError_ptr = nullptr;

// SDL2_mixer函数指针变量
static Mix_OpenAudio_t Mix_OpenAudio_ptr = nullptr;
static Mix_Init_t Mix_Init_ptr = nullptr;
static Mix_Quit_t Mix_Quit_ptr = nullptr;
static Mix_CloseAudio_t Mix_CloseAudio_ptr = nullptr;
static Mix_LoadWAV_t Mix_LoadWAV_ptr = nullptr;
static Mix_LoadMUS_t Mix_LoadMUS_ptr = nullptr;
static Mix_PlayChannel_t Mix_PlayChannel_ptr = nullptr;
static Mix_PlayMusic_t Mix_PlayMusic_ptr = nullptr;
static Mix_HaltMusic_t Mix_HaltMusic_ptr = nullptr;
static Mix_FreeChunk_t Mix_FreeChunk_ptr = nullptr;
static Mix_FreeMusic_t Mix_FreeMusic_ptr = nullptr;
static Mix_VolumeMusic_t Mix_VolumeMusic_ptr = nullptr;
static Mix_Volume_t Mix_Volume_ptr = nullptr;
static Mix_PlayingMusic_t Mix_PlayingMusic_ptr = nullptr;
static Mix_PausedMusic_t Mix_PausedMusic_ptr = nullptr;
static Mix_PauseMusic_t Mix_PauseMusic_ptr = nullptr;
static Mix_ResumeMusic_t Mix_ResumeMusic_ptr = nullptr;
static Mix_GetError_t Mix_GetError_ptr = nullptr;

// 加载SDL2主库DLL
bool LoadSDL2() {
    if (sdl2_dll != nullptr) {
        return true;
    }

    sdl2_dll = LoadLibraryA("SDL2.dll");
    if (sdl2_dll == nullptr) {
        std::cerr << "无法加载SDL2.dll" << std::endl;
        return false;
    }

    // 获取SDL2函数指针
    SDL_Init_ptr = (SDL_Init_t)GetProcAddress(sdl2_dll, "SDL_Init");
    SDL_Quit_ptr = (SDL_Quit_t)GetProcAddress(sdl2_dll, "SDL_Quit");
    SDL_GetError_ptr = (SDL_GetError_t)GetProcAddress(sdl2_dll, "SDL_GetError");

    if (!SDL_Init_ptr || !SDL_Quit_ptr || !SDL_GetError_ptr) {
        std::cerr << "无法获取SDL2函数指针" << std::endl;
        FreeLibrary(sdl2_dll);
        sdl2_dll = nullptr;
        return false;
    }

    return true;
}

// 加载SDL2_mixer DLL
bool LoadSDL2Mixer() {
    if (sdl2_mixer_dll != nullptr) {
        return true;
    }

    sdl2_mixer_dll = LoadLibraryA("SDL2_mixer.dll");
    if (sdl2_mixer_dll == nullptr) {
        std::cerr << "无法加载SDL2_mixer.dll" << std::endl;
        return false;
    }

    // 获取函数指针
    Mix_OpenAudio_ptr = (Mix_OpenAudio_t)GetProcAddress(sdl2_mixer_dll, "Mix_OpenAudio");
    Mix_Init_ptr = (Mix_Init_t)GetProcAddress(sdl2_mixer_dll, "Mix_Init");
    Mix_Quit_ptr = (Mix_Quit_t)GetProcAddress(sdl2_mixer_dll, "Mix_Quit");
    Mix_CloseAudio_ptr = (Mix_CloseAudio_t)GetProcAddress(sdl2_mixer_dll, "Mix_CloseAudio");
    Mix_LoadWAV_ptr = (Mix_LoadWAV_t)GetProcAddress(sdl2_mixer_dll, "Mix_LoadWAV");
    Mix_LoadMUS_ptr = (Mix_LoadMUS_t)GetProcAddress(sdl2_mixer_dll, "Mix_LoadMUS");
    Mix_PlayChannel_ptr = (Mix_PlayChannel_t)GetProcAddress(sdl2_mixer_dll, "Mix_PlayChannel");
    Mix_PlayMusic_ptr = (Mix_PlayMusic_t)GetProcAddress(sdl2_mixer_dll, "Mix_PlayMusic");
    Mix_HaltMusic_ptr = (Mix_HaltMusic_t)GetProcAddress(sdl2_mixer_dll, "Mix_HaltMusic");
    Mix_FreeChunk_ptr = (Mix_FreeChunk_t)GetProcAddress(sdl2_mixer_dll, "Mix_FreeChunk");
    Mix_FreeMusic_ptr = (Mix_FreeMusic_t)GetProcAddress(sdl2_mixer_dll, "Mix_FreeMusic");
    Mix_VolumeMusic_ptr = (Mix_VolumeMusic_t)GetProcAddress(sdl2_mixer_dll, "Mix_VolumeMusic");
    Mix_Volume_ptr = (Mix_Volume_t)GetProcAddress(sdl2_mixer_dll, "Mix_Volume");
    Mix_PlayingMusic_ptr = (Mix_PlayingMusic_t)GetProcAddress(sdl2_mixer_dll, "Mix_PlayingMusic");
    Mix_PausedMusic_ptr = (Mix_PausedMusic_t)GetProcAddress(sdl2_mixer_dll, "Mix_PausedMusic");
    Mix_PauseMusic_ptr = (Mix_PauseMusic_t)GetProcAddress(sdl2_mixer_dll, "Mix_PauseMusic");
    Mix_ResumeMusic_ptr = (Mix_ResumeMusic_t)GetProcAddress(sdl2_mixer_dll, "Mix_ResumeMusic");
    Mix_GetError_ptr = (Mix_GetError_t)GetProcAddress(sdl2_mixer_dll, "Mix_GetError");

    if (!Mix_OpenAudio_ptr || !Mix_LoadWAV_ptr || !Mix_PlayChannel_ptr) {
        std::cerr << "无法获取SDL2_mixer函数指针" << std::endl;
        FreeLibrary(sdl2_mixer_dll);
        sdl2_mixer_dll = nullptr;
        return false;
    }

    return true;
}

void UnloadSDL2() {
    if (sdl2_dll != nullptr) {
        FreeLibrary(sdl2_dll);
        sdl2_dll = nullptr;
    }
}

void UnloadSDL2Mixer() {
    if (sdl2_mixer_dll != nullptr) {
        FreeLibrary(sdl2_mixer_dll);
        sdl2_mixer_dll = nullptr;
    }
}

#else
// Linux/Unix系统直接包含SDL2_mixer头文件
#include <SDL2/SDL_mixer.h>
#endif

bool SoundManager::isInitialized = false;

static std::unordered_map<std::string, Mix_Chunk*> soundCache;
static Mix_Music* currentMusic = nullptr;

bool SoundManager::initialize() {
    if (isInitialized) {
        return true;
    }

#ifdef _WIN32
    // Windows上先加载SDL2主库
    if (!LoadSDL2()) {
        return false;
    }

    // 初始化SDL2音频子系统
    if (SDL_Init_ptr(0x00000010) < 0) { // SDL_INIT_AUDIO = 0x00000010
        std::cerr << "SDL2初始化失败: " << SDL_GetError_ptr() << std::endl;
        UnloadSDL2();
        return false;
    }

    // Windows上动态加载SDL2_mixer
    if (!LoadSDL2Mixer()) {
        SDL_Quit_ptr();
        UnloadSDL2();
        return false;
    }
#endif

    // 初始化SDL_mixer
    if (Mix_OpenAudio_ptr(44100, 0x8010, 2, 1024) == -1) { // 0x8010 = AUDIO_S16LSB
        std::cerr << "SDL_mixer初始化失败";
        if (Mix_GetError_ptr) {
            std::cerr << ": " << Mix_GetError_ptr();
        }
        std::cerr << std::endl;
#ifdef _WIN32
        SDL_Quit_ptr();
        UnloadSDL2();
#endif
        return false;
    }

    // 初始化MP3支持
    if (Mix_Init_ptr) {
        int flags = 0x00000008; // MIX_INIT_MP3
        if (Mix_Init_ptr(flags) != flags) {
            std::cerr << "SDL_mixer MP3初始化失败";
            if (Mix_GetError_ptr) {
                std::cerr << ": " << Mix_GetError_ptr();
            }
            std::cerr << std::endl;
            // 可以继续，但MP3可能不支持
        }
    }

    // 设置默认音量
    if (Mix_VolumeMusic_ptr) Mix_VolumeMusic_ptr(64);  // 音乐音量 50%
    if (Mix_Volume_ptr) Mix_Volume_ptr(-1, 64);        // 所有音效音量 50%

    isInitialized = true;
    std::cout << "SDL_mixer初始化成功" << std::endl;
    return true;
}

void SoundManager::cleanup() {
    if (!isInitialized) {
        return;
    }

    // 停止所有音乐
    if (Mix_HaltMusic_ptr) Mix_HaltMusic_ptr();

    // 释��当前音乐
    if (currentMusic && Mix_FreeMusic_ptr) {
        Mix_FreeMusic_ptr(currentMusic);
        currentMusic = nullptr;
    }

    // 释放所有音效
    if (Mix_FreeChunk_ptr) {
        for (auto& pair : soundCache) {
            Mix_FreeChunk_ptr(pair.second);
        }
    }
    soundCache.clear();

    // 关闭SDL_mixer
    if (Mix_Quit_ptr) Mix_Quit_ptr();
    if (Mix_CloseAudio_ptr) Mix_CloseAudio_ptr();

#ifdef _WIN32
    SDL_Quit_ptr();
    UnloadSDL2Mixer();
    UnloadSDL2();
#endif

    isInitialized = false;
    std::cout << "SDL_mixer已清理" << std::endl;
}

bool SoundManager::playSound(const std::string& soundPath) {
    if (!isInitialized) {
        std::cerr << "SoundManager未初始化" << std::endl;
        return false;
    }

    if (!Mix_LoadWAV_ptr || !Mix_PlayChannel_ptr) {
        std::cerr << "SDL_mixer函数未加载" << std::endl;
        return false;
    }

    // 检查缓存
    auto it = soundCache.find(soundPath);
    Mix_Chunk* sound = nullptr;

    if (it != soundCache.end()) {
        sound = it->second;
    } else {
        // 加载音效文件
        sound = Mix_LoadWAV_ptr(soundPath.c_str());
        if (!sound) {
            std::cerr << "无法加载音效文件 " << soundPath;
            if (Mix_GetError_ptr) {
                std::cerr << ": " << Mix_GetError_ptr();
            }
            std::cerr << std::endl;
            return false;
        }
        // 缓存音效
        soundCache[soundPath] = sound;
    }

    // 播放音效
    if (Mix_PlayChannel_ptr(-1, sound, 0) == -1) {
        std::cerr << "播放音效失败";
        if (Mix_GetError_ptr) {
            std::cerr << ": " << Mix_GetError_ptr();
        }
        std::cerr << std::endl;
        return false;
    }

    return true;
}

bool SoundManager::playMusic(const std::string& musicPath, int loops) {
    if (!isInitialized) {
        std::cerr << "SoundManager未初始化" << std::endl;
        return false;
    }

    if (!Mix_LoadMUS_ptr || !Mix_PlayMusic_ptr) {
        std::cerr << "SDL_mixer音乐函数未加载" << std::endl;
        return false;
    }

    // 停止当前音乐
    stopMusic();

    // 加载音乐文件
    currentMusic = Mix_LoadMUS_ptr(musicPath.c_str());
    if (!currentMusic) {
        std::cerr << "无法加载音乐文件 " << musicPath;
        if (Mix_GetError_ptr) {
            std::cerr << ": " << Mix_GetError_ptr();
        }
        std::cerr << std::endl;
        return false;
    }

    // 播放音乐
    if (Mix_PlayMusic_ptr(currentMusic, loops) == -1) {
        std::cerr << "播放音乐失败";
        if (Mix_GetError_ptr) {
            std::cerr << ": " << Mix_GetError_ptr();
        }
        std::cerr << std::endl;
        return false;
    }

    return true;
}

void SoundManager::stopMusic() {
    if (!isInitialized) {
        return;
    }

    if (Mix_HaltMusic_ptr) Mix_HaltMusic_ptr();

    if (currentMusic && Mix_FreeMusic_ptr) {
        Mix_FreeMusic_ptr(currentMusic);
        currentMusic = nullptr;
    }
}

void SoundManager::pauseMusic() {
    if (!isInitialized) {
        return;
    }

    if (Mix_PlayingMusic_ptr && Mix_PauseMusic_ptr) {
        if (Mix_PlayingMusic_ptr()) {
            Mix_PauseMusic_ptr();
        }
    }
}

void SoundManager::resumeMusic() {
    if (!isInitialized) {
        return;
    }

    if (Mix_PausedMusic_ptr && Mix_ResumeMusic_ptr) {
        if (Mix_PausedMusic_ptr()) {
            Mix_ResumeMusic_ptr();
        }
    }
}

void SoundManager::setMusicVolume(int volume) {
    if (!isInitialized) {
        return;
    }

    // 确保音量在有效范围内
    if (volume < 0) volume = 0;
    if (volume > 128) volume = 128;

    if (Mix_VolumeMusic_ptr) Mix_VolumeMusic_ptr(volume);
}

void SoundManager::setSoundVolume(int volume) {
    if (!isInitialized) {
        return;
    }

    // 确保音量在有效范围内
    if (volume < 0) volume = 0;
    if (volume > 128) volume = 128;

    if (Mix_Volume_ptr) Mix_Volume_ptr(-1, volume);
}

bool SoundManager::isMusicPlaying() {
    if (!isInitialized) {
        return false;
    }

    if (Mix_PlayingMusic_ptr) {
        return Mix_PlayingMusic_ptr() == 1;
    }
    return false;
}
