//
// Created by zzp on 2025/5/29.
//

#include "Timer.h"

Timer::Timer(float interval)
    : m_interval(interval)
{
    reset();
}

void Timer::reset() {
    m_lastTime = std::chrono::high_resolution_clock::now();
}

bool Timer::isReady() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration<float>(currentTime - m_lastTime).count();

    if (elapsedTime >= m_interval) {
        reset();
        return true;
    }

    return false;
}

void Timer::setInterval(float seconds) {
    m_interval = seconds;
}

float Timer::getInterval() const {
    return m_interval;
}