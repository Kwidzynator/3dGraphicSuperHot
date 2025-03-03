#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drawline.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    DrawLine* drawline;

    int imgMatrix[4];
    std::vector<std::pair<int, int>> edges;
    std::array<std::array<double, 4>, 4> translateMatrix;
    std::array<std::array<double, 4>, 4> rotateMatrix;
    std::array<std::array<double, 4>, 4> rotateMatrixY;
    std::array<std::array<double, 4>, 4> rotateMatrixZ;
    std::array<std::array<double, 4>, 4> scaleMatrix;
    std::array<std::array<double, 4>, 4> shearingMatrixOX;
    std::array<std::array<double, 4>, 4> shearingMatrixOY;
    int cx;
    int cy;
    int d;
    int a;
    int freeSpaceX;
    int freeSpaceY;
    int height;
    int width;
    int imgBeginX;
    int imgBeginY;
    QImage* layerBehindImg;

    int edgeLength;
    std::array<std::array<int, 3>, 8> cubeCoordinates3D;
    std::vector<std::array<int, 2>> cubeCoordinates2D;
    std::array<std::array<int, 4>, 6> walls;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setUpSliders();
    void setUpImg();
    void setUpCube();
    void resetSliders();
    void onSliderValueChanged(int);
    void sliderTranslateOX(int);
    void sliderTranslateOY(int);
    void sliderTranslateOZ(int);
    void sliderRotateOX(int);
    void sliderRotateOY(int);
    void sliderRotateOZ(int);
    void sliderScaleOX(int);
    void sliderScaleOY(int);
    void sliderScaleOZ(int);
    void sliderShearingOX(int);
    void sliderShearingOY(int);

    void drawCube();
    void multiplicateMatrix();
    std::array<std::array<double, 4>, 4> getBiggerMatrix(std::array<std::array<double, 4>, 4>, std::array<std::array<double, 4>, 4>);
    void movePixel(double[4], int, int);
    std::array<std::array<double, 4>, 4> multiplyMatrices(const std::array<std::array<double, 4>, 4> &, const std::array<std::array<double, 4>, 4> &);
    void copy(QImage *, QImage *);
    void clear(QImage *);

private:
    Ui::MainWindow *ui;

private slots:
    void paintEvent(QPaintEvent*);

};

#endif // MAINWINDOW_H
