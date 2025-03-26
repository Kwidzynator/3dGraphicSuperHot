#ifndef ZBUFFER_H
#define ZBUFFER_H

#include "drawline.h"

#include <limits>
#include <vector>


class Zbuffer {
public:
    int height;
    int width;
    DrawLine* drawline;
    std::vector<std::vector<float>> buffer;
    std::vector<float> depths;
    std::array<std::array<int, 4>, 6> walls;
    int wa;
    Zbuffer(int, int, DrawLine*);
    ~Zbuffer();

    void clear();
    bool updateDepth(int x, int y, float depth);
    void renderObject(std::vector<std::array<int, 2>> cubeCoordinates2D, std::vector<float> depths, std::array<std::array<int, 4>, 6> walls);
    float interpolateDepth(int x, int y, const std::array<int, 8>& cornerCoords, const std::vector<float>& cornerDepths);
    void renderWall(const std::array<int, 8>& cornerCoords, const std::vector<float>& cornerDepths);
    bool isPointInsideQuad(int x, int y, const std::array<int, 8>& cornerCoords);

    void rasterizeTriangle(int x0, int x1, int x2,
                           int y0, int y1, int y2,
                           float z0, float z1, float z2);
};

#endif // ZBUFFER_H
