#pragma once
#include <vector>
#include <random>

struct RGBColor
{
    int r;
    int g;
    int b;
    RGBColor(int r, int g, int b) : r(r), g(g), b(b) {};
};

struct HSLColor
{
    int h;
    int s;
    int l;
    HSLColor(int h, int s, int l) : h(h), s(s), l(l) {};
};

HSLColor* GenHSLColor();

// Adapted from:
// https://stackoverflow.com/questions/2353211/hsl-to-rgb-color-conversion
float hueToRGB(float p, float q, float t);

// Adapted from:
// https://stackoverflow.com/questions/2353211/hsl-to-rgb-color-conversion
RGBColor* HSLtoRGB(HSLColor* hsl);

std::vector<RGBColor*> GenRGBPair();
