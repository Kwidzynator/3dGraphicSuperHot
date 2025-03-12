#include "drawLine.h"
#include "zbuffer.h"
#include <limits>
#include <iostream>
#include <vector>


Zbuffer::Zbuffer(int w, int h, DrawLine* drawl) : height(h), width(w), drawline(drawl){
    buffer = std::vector<std::vector<float>>(height,
                    std::vector<float>(width, std::numeric_limits<float>::infinity()));

}

void Zbuffer::clear() {
    for (auto& row : buffer) {
        std::fill(row.begin(), row.end(), std::numeric_limits<double>::infinity());
    }
}

bool Zbuffer::updateDepth(int x, int y, float depth) {
    if (depth < buffer[y][x]) {
        buffer[y][x] = depth;
        //std::cout << "drawing point: " << x << ", " << y << ", " << buffer[y][x] << std::endl;
        return true;
    }
    return false;
}

void Zbuffer::renderObject(std::vector<std::array<int, 2>> cubeCoordinates2D, std::vector<float> depths, std::array<std::array<int, 4>, 6> walls){
    for (auto wall : walls) {

        std::array<int, 8> cornerCoords = {
                                           cubeCoordinates2D[wall[0]][0], cubeCoordinates2D[wall[0]][1],
                                           cubeCoordinates2D[wall[1]][0], cubeCoordinates2D[wall[1]][1],
                                           cubeCoordinates2D[wall[2]][0], cubeCoordinates2D[wall[2]][1],
                                            cubeCoordinates2D[wall[3]][0], cubeCoordinates2D[wall[3]][1]};

        std::vector<float> cornerDepths = {depths[wall[0]], depths[wall[1]], depths[wall[2]], depths[wall[3]]};

        renderWall(cornerCoords, cornerDepths);
    }
}

void Zbuffer::renderWall(const std::array<int, 8>& cornerCoords, const std::vector<float>& cornerDepths) {
    if (cornerDepths.size() < 4) {
        std::cerr << "Błąd: cornerDepths musi mieć co najmniej 4 elementy!" << std::endl;
        return;
    }

    int xMin = std::min({cornerCoords[0], cornerCoords[2], cornerCoords[4], cornerCoords[6]});
    int xMax = std::max({cornerCoords[0], cornerCoords[2], cornerCoords[4], cornerCoords[6]});
    int yMin = std::min({cornerCoords[1], cornerCoords[3], cornerCoords[5], cornerCoords[7]});
    int yMax = std::max({cornerCoords[1], cornerCoords[3], cornerCoords[5], cornerCoords[7]});

    xMin = std::max(xMin, 0);
    xMax = std::min(xMax, width - 1);
    yMin = std::max(yMin, 0);
    yMax = std::min(yMax, height - 1);

    for (int y = yMin; y <= yMax; ++y) {
        for (int x = xMin; x <= xMax; ++x) {
            if (isPointInsideQuad(x, y, cornerCoords)) {
                float depth = interpolateDepth(x, y, cornerCoords, cornerDepths);
                if (depth >= 0 && updateDepth(x, y, depth)) {
                    drawline->paintingPixel(QPoint(x, y));
                }
            }
        }
    }
}

float Zbuffer::interpolateDepth(int x, int y, const std::array<int, 8>& cornerCoords, const std::vector<float>& cornerDepths) {
    float x0 = cornerCoords[0];
    float y0 = cornerCoords[1];
    float x1 = cornerCoords[2];
    float y1 = cornerCoords[3];
    float x2 = cornerCoords[4];
    float y2 = cornerCoords[5];
    float x3 = cornerCoords[6];
    float y3 = cornerCoords[7];

    float depth0 = cornerDepths[0];
    float depth1 = cornerDepths[1];
    float depth2 = cornerDepths[2];
    float depth3 = cornerDepths[3];

    float det = (x1 - x0) * (y3 - y0) - (x3 - x0) * (y1 - y0);
    float a = ((x - x0) * (y3 - y0) - (x3 - x0) * (y - y0)) / det;
    float b = ((x1 - x0) * (y - y0) - (x - x0) * (y1 - y0)) / det;
    float c = 1 - a - b;

    float depth = depth0 * a + depth1 * b + depth2 * c;
    return depth;
}

bool Zbuffer::isPointInsideQuad(int x, int y, const std::array<int, 8>& cornerCoords) {
    int intersections = 0;
    for (int i = 0; i < 4; ++i) {
        int x1 = cornerCoords[2 * i];
        int y1 = cornerCoords[2 * i + 1];
        int x2 = cornerCoords[2 * ((i + 1) % 4)];
        int y2 = cornerCoords[2 * ((i + 1) % 4) + 1];

        if ((y1 <= y && y < y2) || (y2 <= y && y < y1)) {
            float t = (float)(y - y1) / (float)(y2 - y1);
            if (x < x1 + t * (x2 - x1)) {
                intersections++;
            }
        }
    }
    return (intersections % 2) == 1;
}


