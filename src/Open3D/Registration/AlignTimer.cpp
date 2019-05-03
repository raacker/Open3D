#include "AlignTimer.h"

using namespace std;

void AlignTimer::StartSilent()
{
    elapsed = 0;
    begin = chrono::high_resolution_clock::now();
}

long long AlignTimer::StopSilent()
{
    end = chrono::high_resolution_clock::now();
    elapsed += chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    return elapsed / 1000L;
}

void AlignTimer::SetTraceLimit(long long limit)
{
    timeLimit = limit;
}

bool AlignTimer::IsTraceTimeExceeded()
{
    tracedTime += StopSilent();
    StartSilent();
    return tracedTime >= timeLimit;
}