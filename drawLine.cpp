#include "drawline.h"
#include <iostream>
#include <cmath>
#include <QPoint>

DrawLine::DrawLine(QImage* image, int width, int height) {
    img = image;
    imgWidth = width;
    imgHeight = height;
}

bool DrawLine::checkIfInFrame(QPoint point) {
    return (point.rx() >= 0) && (point.ry() >= 0) && (point.rx() < imgWidth) && (point.ry() < imgHeight);
}

void DrawLine::paintingPixel(QPoint point) {
    if (!checkIfInFrame(point)) return;

    unsigned char* ptr = img->bits();


    int index = imgWidth * 4 * point.ry() + 4 * point.rx();
    ptr[index] = 0;
    ptr[index + 1] = 0;
    ptr[index + 2] = 255;

}

void DrawLine::paintLine(QPoint startPoint, QPoint endPoint) {
    int dx = endPoint.rx() - startPoint.rx();
    int dy = endPoint.ry() - startPoint.ry();

    if (dy == 0) {
        drawHorizontally(startPoint, endPoint);
    } else if (dx == 0) {
        drawVertically(startPoint, endPoint);
    } else if (abs(dx) >= abs(dy)) {
        drawDiagonallyX(startPoint, endPoint);
    } else {
        drawDiagonallyY(startPoint, endPoint);
    }
}

void DrawLine::drawHorizontally(QPoint start, QPoint end) {
    int direction = chooseDirectionX(start, end);
    for (int x = start.rx(); x != end.rx(); x += direction) {
        paintingPixel(QPoint(x, start.ry()));
    }
    paintingPixel(end);
}

void DrawLine::drawVertically(QPoint start, QPoint end) {
    int direction = chooseDirectionY(start, end);
    for (int y = start.ry(); y != end.ry(); y += direction) {
        paintingPixel(QPoint(start.rx(), y));
    }
    paintingPixel(end);
}

void DrawLine::drawDiagonallyX(QPoint start, QPoint end) {
    float a = calculateA(start, end);
    float b = calculateB(start, a);
    int direction = chooseDirectionX(start, end);

    for (int x = start.rx(); x != end.rx(); x += direction) {
        float y = a * x + b;
        paintingPixel(QPoint(x, static_cast<int>(y)));
    }
    paintingPixel(end);
}

void DrawLine::drawDiagonallyY(QPoint start, QPoint end) {
    float a = calculateA(start, end);
    float b = calculateB(start, a);
    int direction = chooseDirectionY(start, end);

    for (int y = start.ry(); y != end.ry(); y += direction) {
        float x = (y - b) / a;
        paintingPixel(QPoint(static_cast<int>(x), y));
    }
    paintingPixel(end);
}

float DrawLine::calculateA(QPoint startPoint, QPoint endPoint) {
    if (startPoint.rx() == endPoint.rx()) {
        return std::numeric_limits<float>::infinity();
    }
    return static_cast<float>(endPoint.ry() - startPoint.ry()) / (endPoint.rx() - startPoint.rx());
}

float DrawLine::calculateB(QPoint startPoint, float a) {
    return startPoint.ry() - a * startPoint.rx();
}

int DrawLine::chooseDirectionX(QPoint start, QPoint end) {
    return start.rx() < end.rx() ? 1 : -1;
}

int DrawLine::chooseDirectionY(QPoint start, QPoint end) {
    return start.ry() < end.ry() ? 1 : -1;
}
