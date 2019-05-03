#pragma once

#include <iostream>
#include <chrono>
#include <string>

class AlignTimer
{
public:
    std::chrono::high_resolution_clock::time_point begin;
    std::chrono::high_resolution_clock::time_point end;
    long long elapsed;
    long long timeLimit = 0;
    long long tracedTime = 0;

    void StartSilent();
    long long StopSilent();
    void SetTraceLimit(long long limit);
    bool IsTraceTimeExceeded();
};