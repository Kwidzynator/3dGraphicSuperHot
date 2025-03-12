#ifndef TEXTURING_H
#define TEXTURING_H

#include "drawLine.h"

#include <QWidget>
#include <QMouseEvent>
#include <QImage>
#include <QPainter>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>

class Texturing : public QWidget
{
    Q_OBJECT

public:
    Texturing(QImage *, int, int);
    ~Texturing();


private:
    QImage *imgSeen;
    QImage *imgWalls;
    DrawLine *drawLine;

    QPoint pointChosenAtPress;
    int height;
    int width;
    int freeSpaceX;
    int freeSpaceX2;
    int freeSpaceY;
    bool canTrackMove;

    std::vector<QPoint> pointsForShape;
    std::vector<QPoint> pointsFromImage;
    std::vector<std::pair<float, int>> cuts;

    void copy(QImage *, QImage *);
    void clear(QImage *);

    void setUpParameters();
    void paintingPixel(QPoint);
    void paintingPixelBlack(QPoint);
    bool checkIfInFrame(QPoint);
    void paintShape();
    void fillingShape();
    int findMinY();
    int findMaxY();
    float calculateX(QPoint, QPoint, int);
    void painting();

    float interpolate(float, float, float);
    QPoint getImgPoint(float, float, float);
    std::array<int, 3> getColours(QPoint point);
    float getBlue(QPoint point);
    float getGreen(QPoint point);
    float getRed(QPoint point);

private slots:
    // void mousePressEvent(QMouseEvent *event);


};



#endif // TEXTURING_H
