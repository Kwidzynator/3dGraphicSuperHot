#include "texturing.h"
#include "drawLine.h"
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <iostream>
#include <math.h>
#include <algorithm>


Texturing::Texturing(QImage* imgSeen, int height, int width)
{

    imgWalls = new QImage(":/new/wallsImages/missingTexture.jpg");


    drawLine = new DrawLine(imgSeen, height, width);
}

Texturing::~Texturing() {
    delete imgWalls;
    delete imgSeen;
    delete drawLine;
}

void Texturing::clear(QImage *image){
    unsigned char *ptr;
    ptr = image->bits();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ptr[width * 4 *y + 4 * x] = 0;
            ptr[width * 4 *y + 4 * x + 1] = 0;
            ptr[width * 4 * y + 4 * x+ 2] = 0;
        }
    }
    update();
}


// void Texturing::mousePressEvent(QMouseEvent *event) {
//     pointChosenAtPress.setX(event->x() - freeSpaceX);
//     pointChosenAtPress.setY(event->y() - freeSpaceY);

//     if(pointChosenAtPress.x() >= 650 && event->button() == Qt::LeftButton){

//         if(pointsForShape.size() < 3){
//             pointsForShape.push_back(pointChosenAtPress);

//         }
//     }
//     else if(pointChosenAtPress.x() < 650 && event->button() == Qt::LeftButton){
//         if(pointsFromImage.size() < 3){
//             pointsFromImage.push_back(pointChosenAtPress);
//         }
//     }

//     if(event->button() == Qt::RightButton){
//         pointsForShape.clear();
//         pointsFromImage.clear();

//     }

//     if(pointsForShape.size() == 3 && pointsFromImage.size() == 3){
//         fillingShape();
//     }
// }

void Texturing::fillingShape(){
    int min = findMinY();
    int max = findMaxY();
    int x = 0;
    for(int y = min; y <= max; y++){
        for(size_t i = 0; i < pointsForShape.size() - 1; i++){
            if(((pointsForShape.at(i).ry()<= y) && (y < pointsForShape.at(i + 1).ry())) ||
                ((pointsForShape.at(i + 1).ry() <= y) && (y < pointsForShape.at(i).ry()))){
                x = calculateX(pointsForShape.at(i), pointsForShape.at(i + 1), y);
                if(x != -1){
                    cuts.emplace_back(x, y);
                }
            }
        }
    }

    for(int y = min; y <= max; y++){
        if(((pointsForShape.at(0).ry()<= y) && (y < pointsForShape.back().ry())) ||
            ((pointsForShape.back().ry() <= y) && (y < pointsForShape.at(0).ry()))){
            x = calculateX(pointsForShape.at(0), pointsForShape.back(), y);
            if(x != -1){
                cuts.emplace_back(x, y);
            }
        }
    }

    std::sort(cuts.begin(), cuts.end(), [](const std::pair<float, int>& a, const std::pair<float, int>& b) {
        if (a.second == b.second) {
            return a.first < b.first;
        }
        return a.second < b.second;
    });

    painting();
}


int Texturing::findMinY(){
    int min = INT_MAX;
    for(QPoint p: pointsForShape){
        if(p.y() < min){
            min = p.y();
        }
    }
    return min;
}

int Texturing::findMaxY(){
    int max = INT_MIN;
    for(QPoint p: pointsForShape){
        if(p.y() > max){
            max = p.y();
        }
    }
    return max;
}

float Texturing::calculateX(QPoint p1, QPoint p2, int y){
    if(p2.y() - p1.y() == 0){
        return p1.rx();
    }
    return ((y - p1.y()) * (p2.x() - p1.x()) / (p2.y() - p1.y())) + p1.x();
}

void Texturing::painting(){
    QPoint tmp1;
    QPoint tmp2;
    for (int i = 0; i < cuts.size(); i += 2) {
        if (i + 1 < cuts.size()) {
            tmp1.rx() = cuts.at(i).first;
            tmp1.ry() = cuts.at(i).second;
            tmp2.rx() = cuts.at(i + 1).first;
            tmp2.ry() = cuts.at(i + 1).second;
            drawLine->paintLine(tmp1, tmp2);

        }

    }
    cuts.clear();
}

std::array<int, 3> Texturing::getColours(QPoint point){
    QPoint pA = pointsForShape.at(0);
    QPoint pB = pointsForShape.at(1);
    QPoint pC = pointsForShape.at(2);

    float u, v, w;
    float denominator = ( (pB.x() - pA.x()) * (pC.y() - pA.y()) - (pB.y() - pA.y()) * (pC.x() - pA.x()) );

    v = ( (float)(point.x() - pA.x()) * (float)(pC.y() - pA.y()) - (float)(point.y() - pA.y()) * (float)(pC.x() - pA.x()) ) / denominator;
    w = ( (float)(pB.x() - pA.x()) * (float)(point.y() - pA.y()) - (float)(pB.y() - pA.y()) * (float)(point.x() - pA.x()) ) / denominator;
    u = 1.0f - v - w;


    /*std::cout << v << std::endl;
    std::cout << w << std::endl;
    std::cout << u << std::endl;*/
    if(u < 0 || w < 0 || v < 0 ){
        return {};
    }

    QPoint pointInImage = getImgPoint(u, v, w);

    int x = static_cast<int>(pointInImage.x());
    int y = static_cast<int>(pointInImage.y());

    float fx = pointInImage.x() - x;
    float fy = pointInImage.y() - y;


    float topRed = interpolate(getRed(QPoint(x, y)), getRed(QPoint(x + 1, y)), fx);
    float topGreen = interpolate(getGreen(QPoint(x, y)), getGreen(QPoint(x + 1, y)), fx);
    float topBlue = interpolate(getBlue(QPoint(x, y)), getBlue(QPoint(x + 1, y)), fx);

    float bottomRed = interpolate(getRed(QPoint(x, y + 1)), getRed(QPoint(x + 1, y + 1)), fx);
    float bottomGreen = interpolate(getGreen(QPoint(x, y + 1)), getGreen(QPoint(x + 1, y + 1)), fx);
    float bottomBlue = interpolate(getBlue(QPoint(x, y + 1)), getBlue(QPoint(x + 1, y + 1)), fx);


    int red = static_cast<int>(interpolate(topRed, bottomRed, fy));
    int green = static_cast<int>(interpolate(topGreen, bottomGreen, fy));
    int blue = static_cast<int>(interpolate(topBlue, bottomBlue, fy));

    return {blue, green, red};
}


float Texturing::interpolate(float start, float end, float fraction) {
    return start * (1 - fraction) + end * fraction;
}



QPoint Texturing::getImgPoint(float u, float v, float w){
    QPoint p;
    p.rx() = pointsFromImage.at(0).x() * u + pointsFromImage.at(1).x() * v + pointsFromImage.at(2).x() * w;
    p.ry() = pointsFromImage.at(0).y() * u + pointsFromImage.at(1).y() * v + pointsFromImage.at(2).y() * w;
    return p;
}


float Texturing::getBlue(QPoint point){
    unsigned char * ptr;
    ptr = imgWalls->bits();
    std::vector<int> colours;

    return ptr[width*4*point.ry() + 4 * point.rx()];
}

float Texturing::getGreen(QPoint point){
    unsigned char * ptr;
    ptr = imgWalls->bits();
    std::vector<int> colours;

    return ptr[width*4*point.ry() + 4*point.rx() + 1];
}

float Texturing::getRed(QPoint point){
    unsigned char * ptr;
    ptr = imgWalls->bits();
    std::vector<int> colours;

    return ptr[width*4*point.ry() + 4*point.rx()+ 2];
}
