#include "FPSCounter.hpp"

int FPSCounter::getFPS(const sf::Time& deltaTime)
{
    timeAccumulator += deltaTime.asSeconds();
    countCalls++;

    if (timeAccumulator >= timeLimit)
    {
        FPS = 1.f / (timeAccumulator / countCalls);
        timeAccumulator = 0.f;
        countCalls = 0;
    }

    return FPS;
}

void FPSCounter::setTimeLimit(const sf::Time& l)
{
    timeLimit = l.asSeconds();
}

FPSCounter::FPSCounter(const sf::Time& intervalTime)
{
    timeLimit = intervalTime.asSeconds();
}

FPSCounter::FPSCounter(const float& intervalTime)
{
    timeLimit = intervalTime;
}
