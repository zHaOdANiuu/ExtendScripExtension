#pragma once

inline int clamp(int value, int min, int max)
{
    return value < min ? min : (value > max ? max : value);
}

inline double clamp(double value, double min, double max)
{
    return value < min ? min : (value > max ? max : value);
}

inline float clamp(float value, float min, float max)
{
    return value < min ? min : (value > max ? max : value);
}
