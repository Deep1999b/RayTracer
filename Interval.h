#pragma once

#include <cmath>

class interval {
public:
    double min, max;

    interval() : min(+INFINITY), max(-INFINITY) {}
    interval(double min, double max) : min(min), max(max) {}

    double size() const { return max - min; }
    bool contains(double x) const { return min <= x && x <= max; }
    bool surrounds(double x) const { return min < x && x < max; }

    double clamp(double x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    static const interval empty, universe;
};

// This tells the compiler it's a variable, NOT a function.
extern const interval intensity;