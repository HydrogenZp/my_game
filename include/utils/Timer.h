// Created by: zzp
#pragma once
#include <chrono>
class Timer {
public:
    explicit Timer(float interval = 0.2f);

    void reset();

    bool isReady();
    
    void setInterval(float seconds);
    
    float getInterval() const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_lastTime;
    float m_interval;
};