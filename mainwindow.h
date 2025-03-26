#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "drawline.h"
#include "zbuffer.h"

#include "OpenGLSetup.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct Point3D {
    float x, y, z;
};

struct Point2D {
    float x, y;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    DrawLine* drawline;
    Zbuffer* zbuffer;

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

    float edgeLength;
    std::vector<float> depths;
    std::vector<float> rubikDepths;
    std::array<std::array<float, 3>, 8> cubeCoordinates3D;
    std::array<std::array<float, 3>, 64> rubikWallCoordinates3D;
    std::vector<std::array<int, 2>> cubeCoordinates2D;
    std::vector<std::array<int, 2>> rubikWallCoordinates2D;
    std::array<std::array<int, 4>, 6> walls;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setUpSliders();
    void setUpImg();
    void setUpCube();
    void setUpFloor();
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


    void coordinatesTo2D();

    void drawCube();
    void drawFloor();

    void multiplicateMatrix();
    std::array<std::array<double, 4>, 4> getBiggerMatrix(std::array<std::array<double, 4>, 4>, std::array<std::array<double, 4>, 4>);
    void movePixel(double[4], std::vector<std::array<int, 2>> *);
    std::array<std::array<double, 4>, 4> multiplyMatrices(const std::array<std::array<double, 4>, 4> &, const std::array<std::array<double, 4>, 4> &);
    void copy(QImage *, QImage *);
    void clear(QImage *);


    bool isFaceVisible(const Point3D& normal, const Point3D& viewDir);
    Point3D calculateNormal(const Point3D& p1, const Point3D& p2, const Point3D& p3);

private:
    OpenGLSetup *openGLWidget;
    std::vector<std::vector<float>> zBuffer;
    Ui::MainWindow *ui;
    QPoint lastPosition;
    void updatePosition();
    double OXpositionWSAD;
    double OZpositionWSAD;
    bool isWPressed;
    bool isSPressed;
    bool isAPressed;
    bool isDPressed;
private slots:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

};

#endif // MAINWINDOW_H
