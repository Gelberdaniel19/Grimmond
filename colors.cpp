#include "colors.hpp"

HSLColor* GenHSLColor()
{
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> distH(0, 360);
    std::uniform_int_distribution<std::mt19937::result_type> distS(60, 100);
    std::uniform_int_distribution<std::mt19937::result_type> distL(25, 50);

    return new HSLColor(distH(rng), distS(rng), distL(rng));
}

// Adapted from:
// https://stackoverflow.com/questions/2353211/hsl-to-rgb-color-conversion
float hueToRGB(float p, float q, float t)
{
    if(t < 0) t++;
    if(t > 1) t--;
    if(t < 1.0/6) return p + (q - p) * 6 * t;
    if(t < 1.0/2) return q;
    if(t < 2.0/3) return p + (q - p) * (2.0/3 - t) * 6;
    return p;
}

// Adapted from:
// https://stackoverflow.com/questions/2353211/hsl-to-rgb-color-conversion
RGBColor* HSLtoRGB(HSLColor* hsl)
{
    float h = (float)hsl->h/360;
    float s = (float)hsl->s/100;
    float l = (float)hsl->l/100;
    float r, g, b;

    if (s == 0) {
        r = g = b = l;
    } else {
        float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        float p = 2 * l - q;
        r = hueToRGB(p, q, h + 1.0/3);
        g = hueToRGB(p, q, h);
        b = hueToRGB(p, q, h - 1.0/3);
    }

    return new RGBColor((int)(r*255), (int)(g*255), (int)(b*255));
}

std::vector<RGBColor*> GenRGBPair()
{
    HSLColor* hsl1 = GenHSLColor();
    HSLColor* hsl2 = new HSLColor(hsl1->h, hsl1->s, hsl1->l+30);

    std::vector<RGBColor*> pair;
    pair.emplace_back(HSLtoRGB(hsl1));
    pair.emplace_back(HSLtoRGB(hsl2));

    delete hsl1;
    delete hsl2;
    return pair;
}
