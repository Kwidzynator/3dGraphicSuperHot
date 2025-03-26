#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QPainter>
#include <cmath>
#include "drawline.h"
#include "qevent.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , lastPosition(QPoint(0, 0))
{
    setMouseTracking(true);
    ui->setupUi(this);

    setUpSliders();
    setUpImg();

    // openGLWidget = new OpenGLSetup(this);
    // openGLWidget->setParent(ui->openGLContainer);

    drawline = new DrawLine(layerBehindImg, width, height);
    zbuffer = new Zbuffer(width, height, drawline);


    setUpCube();

    multiplicateMatrix();

    OXpositionWSAD = 0;
    OZpositionWSAD = 0;
    isWPressed = false;
    isSPressed = false;
    isAPressed = false;
    isDPressed = false;


}


MainWindow::~MainWindow()
{
    delete ui;
    delete drawline;
}

void MainWindow::setUpSliders(){
    int minVal = -500;
    int maxVal = 500;

    ui->translationSliderOX->setMinimum(minVal);
    ui->translationSliderOX->setMaximum(maxVal);
    ui->translationSliderOX->setValue(0);

    ui->translationSliderOY->setMinimum(minVal);
    ui->translationSliderOY->setMaximum(maxVal);
    ui->translationSliderOY->setValue(0);

    ui->translationSliderOZ->setMinimum(minVal);
    ui->translationSliderOZ->setMaximum(maxVal);
    ui->translationSliderOZ->setValue(0);

    ui->rotationSliderOX->setMaximum(628);
    ui->rotationSliderOX->setValue(0);

    ui->rotationSliderOY->setMaximum(628);
    ui->rotationSliderOY->setValue(0);

    ui->rotationSliderOZ->setMaximum(628);
    ui->rotationSliderOZ->setValue(0);

    ui->scalingSliderOX->setMinimum(minVal);
    ui->scalingSliderOX->setMaximum(maxVal);
    ui->scalingSliderOX->setValue(0);

    ui->scalingSliderOY->setMinimum(minVal);
    ui->scalingSliderOY->setMaximum(maxVal);
    ui->scalingSliderOY->setValue(0);

    ui->scalingSliderOZ->setMinimum(minVal);
    ui->scalingSliderOZ->setMaximum(maxVal);
    ui->scalingSliderOZ->setValue(0);

    ui->shearingSliderOX->setMinimum(-70);
    ui->shearingSliderOX->setMaximum(70);
    ui->shearingSliderOX->setValue(0);

    ui->shearingSliderOY->setMinimum(-70);
    ui->shearingSliderOY->setMaximum(70);
    ui->shearingSliderOY->setValue(0);

    connect(ui->translationSliderOX, &QSlider::valueChanged, this, &MainWindow::sliderTranslateOX);
    connect(ui->translationSliderOY, &QSlider::valueChanged, this, &MainWindow::sliderTranslateOY);
    connect(ui->translationSliderOZ, &QSlider::valueChanged, this, &MainWindow::sliderTranslateOZ);
    connect(ui->rotationSliderOX, &QSlider::valueChanged, this, &MainWindow::sliderRotateOX);
    connect(ui->rotationSliderOY, &QSlider::valueChanged, this, &MainWindow::sliderRotateOY);
    connect(ui->rotationSliderOZ, &QSlider::valueChanged, this, &MainWindow::sliderRotateOZ);
    connect(ui->scalingSliderOX, &QSlider::valueChanged, this, &MainWindow::sliderScaleOX);
    connect(ui->scalingSliderOY, &QSlider::valueChanged, this, &MainWindow::sliderScaleOY);
    connect(ui->scalingSliderOZ, &QSlider::valueChanged, this, &MainWindow::sliderScaleOZ);
    connect(ui->shearingSliderOX, &QSlider::valueChanged, this, &MainWindow::sliderShearingOX);
    connect(ui->shearingSliderOY, &QSlider::valueChanged, this, &MainWindow::sliderShearingOY);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::resetSliders);
}

void MainWindow::setUpImg(){
    resize(900, 650);
    height = 600;
    width = 600;
    freeSpaceX = 25;
    freeSpaceY = 25;

    layerBehindImg = new QImage(width, height, QImage::Format_RGB32);

    translateMatrix[0] = {1, 0, 0, 0};
    translateMatrix[1] = {0, 1, 0, 0};
    translateMatrix[2] = {0, 0, 1, 0};
    translateMatrix[3] = {0, 0, 0, 1};

    rotateMatrix[0] = {1, 0, 0, 0};
    rotateMatrix[1] = {0, 1, 0, 0};
    rotateMatrix[2] = {0, 0, 1, 0};
    rotateMatrix[3] = {0, 0, 0, 1};

    rotateMatrixY[0] = {1, 0, 0, 0};
    rotateMatrixY[1] = {0, 1, 0, 0};
    rotateMatrixY[2] = {0, 0, 1, 0};
    rotateMatrixY[3] = {0, 0, 0, 1};

    rotateMatrixZ[0] = {1, 0, 0, 0};
    rotateMatrixZ[1] = {0, 1, 0, 0};
    rotateMatrixZ[2] = {0, 0, 1, 0};
    rotateMatrixZ[3] = {0, 0, 0, 1};

    scaleMatrix[0] = {1, 0, 0, 0};
    scaleMatrix[1] = {0, 1, 0, 0};
    scaleMatrix[2] = {0, 0, 1, 0};
    scaleMatrix[3] = {0, 0, 0, 1};

    shearingMatrixOX[0] = {1, 0, 0, 0};
    shearingMatrixOX[1] = {0, 1, 0, 0};
    shearingMatrixOX[2] = {0, 0, 1, 0};
    shearingMatrixOX[3] = {0, 0, 0, 1};

    shearingMatrixOY[0] = {1, 0, 0, 0};
    shearingMatrixOY[1] = {0, 1, 0, 0};
    shearingMatrixOY[2] = {0, 0, 1, 0};
    shearingMatrixOY[3] = {0, 0, 0, 1};



    imgBeginX = width / 2;
    imgBeginY = height / 2;
}


void MainWindow::setUpCube(){
    edgeLength = 300;
    float a = edgeLength/2;
    cx = width/2;
    cy = height/2;
    d = 170;

    float rubikPoint = 100;

    cubeCoordinates3D = {{
        {{-a, -a, -a}}, {{ a, -a, -a}}, {{ a,  a, -a}}, {{-a,  a, -a}},
        {{-a, -a,  a}}, {{ a, -a,  a}}, {{ a,  a,  a}}, {{-a,  a,  a}}
    }};

    rubikWallCoordinates3D = {{

        {{-a + rubikPoint, -a, -a}}, {{-a + rubikPoint, -a, a}},
        {{ a - rubikPoint, -a, -a}}, {{ a - rubikPoint, -a, a}},
        {{ a, -a, -a + rubikPoint}}, {{-a, -a, -a + rubikPoint}},
        {{ a,  -a,  a - rubikPoint}}, {{-a,  -a,  a - rubikPoint}}, //up

        {{ a - rubikPoint,  a, -a}}, {{ a - rubikPoint,  a, a}},
        {{-a + rubikPoint,  a, -a}}, {{-a + rubikPoint,  a, a}},
        {{a,  a, a - rubikPoint}}, {{-a,  a, a - rubikPoint}},
        {{a,  a, -a + rubikPoint}}, {{-a,  a, -a + rubikPoint}}, //down

        {{ a, -a + rubikPoint, -a}}, {{ a, -a + rubikPoint, a}},
        {{ a,  a - rubikPoint, -a}}, {{ a,  a - rubikPoint, a}}, // right
        {{a,  a, a - rubikPoint}}, {{ a,  -a,  a - rubikPoint}},
        {{ a, -a, -a + rubikPoint}}, {{a,  a, -a + rubikPoint}},

        {{-a,  a - rubikPoint, -a}}, {{-a,  a - rubikPoint, a}},
        {{-a,  -a + rubikPoint , -a}}, {{-a,  -a + rubikPoint , a}}, //left
        {{-a,  -a,  a - rubikPoint}}, {{-a,  a, a - rubikPoint}},
        {{-a, -a, -a + rubikPoint}}, {{-a,  a, -a + rubikPoint}},

        {{-a + rubikPoint, -a, -a}}, {{-a + rubikPoint,  a, -a}},
        {{ a - rubikPoint, -a, -a}}, {{ a - rubikPoint,  a, -a}},
        {{ a, -a + rubikPoint, -a}}, {{-a,  -a + rubikPoint , -a}},
        {{ a,  a - rubikPoint, -a}}, {{-a,  a - rubikPoint, -a}}, //front


        {{ a,  a - rubikPoint, a}}, {{-a,  a - rubikPoint, a}},
        {{ a, -a + rubikPoint, a}}, {{-a,  -a + rubikPoint , a}},
        {{ a - rubikPoint, -a, a}}, {{ a - rubikPoint,  a, a}},
        {{-a + rubikPoint, -a, a}}, {{-a + rubikPoint,  a, a}},

        {{-a, -a, -a}}, {{ a, -a, -a}}, {{ a,  a, -a}}, {{-a,  a, -a}},
        {{-a, -a,  a}}, {{ a, -a,  a}}, {{ a,  a,  a}}, {{-a,  a,  a}}

    }};

    coordinatesTo2D();


    edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    walls = {{
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {0, 4, 5, 1},
        {2, 6, 7, 3},
        {0, 3, 7, 4},
        {1, 2, 6, 5}
    }};



}


void MainWindow::coordinatesTo2D(){
    for(int i = 0; i < cubeCoordinates3D.size(); i++){
        int x = cubeCoordinates3D[i][0];
        int y = cubeCoordinates3D[i][1];
        int z = cubeCoordinates3D[i][2];
        depths.push_back(z);

        int x2D = cx + (x * d) / (-z + d);
        int y2D = cy + (y * d) / (-z + d);

        cubeCoordinates2D.push_back({x2D, y2D});
    }


    for(int i = 0; i < rubikWallCoordinates3D.size(); i++){
        int x = rubikWallCoordinates3D[i][0];
        int y = rubikWallCoordinates3D[i][1];
        int z = rubikWallCoordinates3D[i][2];

        rubikDepths.push_back(z);
        int x2D = cx + (x * d) / (-z + d);
        int y2D = cy + (y * d) / (-z + d);

        rubikWallCoordinates2D.push_back({x2D, y2D});
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    clear(layerBehindImg);

    switch (event->key()) {
    case Qt::Key_W:
        isWPressed = true;
        break;
    case Qt::Key_S:
        isSPressed = true;
        break;
    case Qt::Key_A:
        isAPressed = true;
        break;
    case Qt::Key_D:
        isDPressed = true;
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }

    updatePosition();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    clear(layerBehindImg);

    switch (event->key()) {
    case Qt::Key_W:
        isWPressed = false;
        break;
    case Qt::Key_S:
        isSPressed = false;
        break;
    case Qt::Key_A:
        isAPressed = false;
        break;
    case Qt::Key_D:
        isDPressed = false;
        break;
    default:
        QMainWindow::keyReleaseEvent(event);
    }

    updatePosition();
}

void MainWindow::updatePosition() {

    if (isWPressed && isDPressed) {
        OZpositionWSAD += 5;
        OXpositionWSAD += 5;
    }
    else if (isWPressed && isAPressed) {
        OZpositionWSAD += 5;
        OXpositionWSAD -= 5;
    }
    else if (isSPressed && isDPressed) {
        OZpositionWSAD -= 5;
        OXpositionWSAD += 5;
    }
    else if (isSPressed && isAPressed) {
        OZpositionWSAD -= 5;
        OXpositionWSAD -= 5;
    }
    // Zwykłe ruchy na osiach
    else {
        if (isWPressed) {
            OZpositionWSAD += 5;
        }
        if (isSPressed) {
            OZpositionWSAD -= 5;
        }
        if (isAPressed) {
            OXpositionWSAD -= 5;
        }
        if (isDPressed) {
            OXpositionWSAD += 5;
        }
    }

    translateMatrix[0][3] = -OXpositionWSAD;
    translateMatrix[2][3] = -OZpositionWSAD;
    multiplicateMatrix();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

    int currentVal;

    QPoint currentPos = event->pos();

        int dx = currentPos.x() - lastPosition.x();
        int dy = currentPos.y() - lastPosition.y();

        if (dx > 0){
            currentVal = ui->rotationSliderOY->value();
            sliderRotateOY(currentVal + 1);

        }

        else if (dx < 0){
            currentVal = ui->rotationSliderOY->value();
            sliderRotateOY(currentVal - 1);

        }

        if (dy > 0){
            currentVal = ui->rotationSliderOX->value();
            sliderRotateOX(currentVal - 1);

        }
        else if (dy < 0){
            currentVal = ui->rotationSliderOX->value();
            sliderRotateOX(currentVal + 1);

        }

    lastPosition = currentPos;
}

void MainWindow::copy(QImage* copied, QImage* edited) {
    unsigned char *ptrCopied = copied->bits();
    unsigned char *ptrEdited = edited->bits();

    int moveY;
    int moveX;

    for (int y = 0; y < copied->height(); y++) {
        for (int x = 0; x < copied->width(); x++) {
            moveY = y + imgBeginX;
            moveX = x + imgBeginY;
            ptrEdited[width * 4 * moveY + 4 * moveX] = ptrCopied[copied->width() * 4 * y + 4 * x];
            ptrEdited[width * 4 * moveY + 4 * moveX + 1] = ptrCopied[copied->width() * 4 * y + 4 * x + 1];
            ptrEdited[width * 4 * moveY + 4 * moveX + 2] = ptrCopied[copied->width() * 4 * y + 4 * x + 2];
        }
    }
    update();
}


void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(freeSpaceX, freeSpaceY, *layerBehindImg);
    //p.drawImage((width - img->width()) / 2 + freeSpaceX, (height - img->height()) / 2 + freeSpaceY, *img);
}

void MainWindow::resetSliders()
{
    ui->translationSliderOX->setValue(0);
    ui->translationSliderOY->setValue(0);
    ui->translationSliderOZ->setValue(0);
    ui->rotationSliderOX->setValue(0);
    ui->rotationSliderOY->setValue(0);
    ui->rotationSliderOZ->setValue(0);
    ui->scalingSliderOX->setValue(0);
    ui->scalingSliderOY->setValue(0);
    ui->scalingSliderOZ->setValue(0);
    ui->shearingSliderOX->setValue(0);
    ui->shearingSliderOY->setValue(0);

    setUpCube();
}

void MainWindow::sliderTranslateOX(int value) {
    ui->translationSliderOX->setValue(value);
    clear(layerBehindImg);

    double valueToDouble = static_cast<double>(value);

    translateMatrix[0][3] = -valueToDouble;
    multiplicateMatrix();


}

void MainWindow::sliderTranslateOY(int value) {
    ui->translationSliderOY->setValue(value);
    clear(layerBehindImg);

    double valueToDouble = static_cast<double>(value);

    translateMatrix[1][3] = -valueToDouble;

    multiplicateMatrix();

}

void MainWindow::sliderTranslateOZ(int value){
    ui->translationSliderOZ->setValue(value);

    clear(layerBehindImg);

    double valueToDouble = static_cast<double>(value);

    translateMatrix[2][3] = -valueToDouble;

    multiplicateMatrix();
}

void MainWindow::sliderRotateOX(int value){
    ui-> rotationSliderOX->setValue(value);
    double valueToDouble = static_cast<double>(value) * M_PI / 180.0f;
    clear(layerBehindImg);


    rotateMatrix[1] = {0, cos(valueToDouble), -sin(valueToDouble), 0};
    rotateMatrix[2] = {0, sin(valueToDouble), cos(valueToDouble), 0};

    multiplicateMatrix();

}

void MainWindow::sliderRotateOY(int value){
    ui-> rotationSliderOY->setValue(value);
    double valueToDouble = static_cast<double>(value) * M_PI / 180.0f;
    clear(layerBehindImg);


    rotateMatrixY[0] = {cos(valueToDouble), 0,  sin(valueToDouble), 0};
    rotateMatrixY[2] = {-sin(valueToDouble), 0,  cos(valueToDouble), 0};

    multiplicateMatrix();
}

void MainWindow::sliderRotateOZ(int value){
    ui-> rotationSliderOZ->setValue(value);
    double valueToDouble = static_cast<double>(value) * M_PI / 180.0f;
    clear(layerBehindImg);


    rotateMatrixZ[0] = {cos(valueToDouble), -sin(valueToDouble), 0, 0};
    rotateMatrixZ[1] = {sin(valueToDouble), cos(valueToDouble), 0, 0};

    multiplicateMatrix();
}

void MainWindow::sliderScaleOX(int value){
    ui->scalingSliderOX->setValue(value);
    double valueToDouble = static_cast<double>(value/ 100.0f);

    clear(layerBehindImg);

    scaleMatrix[0][0] = std::max(valueToDouble + 1.0, 0.1);

    multiplicateMatrix();
}

void MainWindow::sliderScaleOY(int value){
    ui->scalingSliderOY->setValue(value);
    double valueToDouble = static_cast<double>(value / 100.0f);
    clear(layerBehindImg);


    scaleMatrix[1][1] = std::max(valueToDouble + 1.0, 0.1);

    multiplicateMatrix();
}

void MainWindow::sliderScaleOZ(int value){
    ui->scalingSliderOZ->setValue(value);
    double valueToDouble = static_cast<double>(value / 100.0f);
    clear(layerBehindImg);


    scaleMatrix[2][2] = std::max(valueToDouble + 1.0, 0.1);

    multiplicateMatrix();
}

void MainWindow::sliderShearingOX(int value){
    ui->shearingSliderOX->setValue(value);
    double valueToDouble = static_cast<double>(value / 100.0f);
    clear(layerBehindImg);

    shearingMatrixOX[2][0] = -valueToDouble;

    multiplicateMatrix();
}

void MainWindow::sliderShearingOY(int value){
    ui->shearingSliderOY->setValue(value);
    double valueToDouble = static_cast<double>(value / 100.0f);
    clear(layerBehindImg);

    shearingMatrixOX[2][1] = -valueToDouble;


    multiplicateMatrix();
}

void MainWindow::clear(QImage *image){
    unsigned char *ptr;
    ptr = image->bits();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ptr[width * 4 *y + 4 * x] = 0;
            ptr[width * 4 *y + 4 * x + 1] = 0;
            ptr[width * 4 * y + 4 * x+ 2] = 0;
        }
    }

}

void MainWindow::multiplicateMatrix() {
    double resultMatrix[4] = {0, 0, 0, 1};
    double rubikResultMatrix[4] = {0, 0, 0, 1};
    std::array<std::array<double, 4>, 4> calculatedMatrix;
    double adjustedZ = 1.0;

    calculatedMatrix[0] = {1, 0, 0, 0};
    calculatedMatrix[1] = {0, 1, 0, 0};
    calculatedMatrix[2] = {0, 0, 1, 0};
    calculatedMatrix[3] = {0, 0, 0, 1};

    cubeCoordinates2D.clear();
    rubikWallCoordinates2D.clear();
    depths.clear();
    zbuffer->clear();

    calculatedMatrix = getBiggerMatrix(calculatedMatrix, translateMatrix);
    calculatedMatrix = getBiggerMatrix(calculatedMatrix, rotateMatrix);
    calculatedMatrix = getBiggerMatrix(calculatedMatrix, rotateMatrixY);
    calculatedMatrix = getBiggerMatrix(calculatedMatrix, rotateMatrixZ);
    calculatedMatrix = getBiggerMatrix(calculatedMatrix, scaleMatrix);
    calculatedMatrix = getBiggerMatrix(calculatedMatrix, shearingMatrixOX);
    calculatedMatrix = getBiggerMatrix(calculatedMatrix, shearingMatrixOY);


    for (const auto& coord : cubeCoordinates3D) {
        double pixelX = coord[0];
        double pixelY = coord[1];
        double pixelZ = coord[2];

        resultMatrix[0] = calculatedMatrix[0][0] * pixelX + calculatedMatrix[0][1] * pixelY + calculatedMatrix[0][2] * pixelZ + calculatedMatrix[0][3];
        resultMatrix[1] = calculatedMatrix[1][0] * pixelX + calculatedMatrix[1][1] * pixelY + calculatedMatrix[1][2] * pixelZ + calculatedMatrix[1][3];
        resultMatrix[2] = calculatedMatrix[2][0] * pixelX + calculatedMatrix[2][1] * pixelY + calculatedMatrix[2][2] * pixelZ + calculatedMatrix[2][3];
        resultMatrix[3] = calculatedMatrix[3][0] * pixelX + calculatedMatrix[3][1] * pixelY + calculatedMatrix[3][2] * pixelZ + calculatedMatrix[3][3];

        movePixel(resultMatrix, &cubeCoordinates2D);
    }

    for(const auto& coord: rubikWallCoordinates3D){
        double pixelX = coord[0];
        double pixelY = coord[1];
        double pixelZ = coord[2];

        rubikResultMatrix[0] = calculatedMatrix[0][0] * pixelX + calculatedMatrix[0][1] * pixelY + calculatedMatrix[0][2] * pixelZ + calculatedMatrix[0][3];
        rubikResultMatrix[1] = calculatedMatrix[1][0] * pixelX + calculatedMatrix[1][1] * pixelY + calculatedMatrix[1][2] * pixelZ + calculatedMatrix[1][3];
        rubikResultMatrix[2] = calculatedMatrix[2][0] * pixelX + calculatedMatrix[2][1] * pixelY + calculatedMatrix[2][2] * pixelZ + calculatedMatrix[2][3];
        rubikResultMatrix[3] = calculatedMatrix[3][0] * pixelX + calculatedMatrix[3][1] * pixelY + calculatedMatrix[3][2] * pixelZ + calculatedMatrix[3][3];

        movePixel(rubikResultMatrix, &rubikWallCoordinates2D);
    }

    drawCube();
    update();
}

std::array<std::array<double, 4>, 4> MainWindow::getBiggerMatrix(std::array<std::array<double, 4>, 4> m1, std::array<std::array<double, 4>, 4> calculatedMatrix){
    std::array<std::array<double, 4>, 4> result = {};

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                result[i][j] += m1[i][k] * calculatedMatrix[k][j];
            }
        }
    }

    return result;
}

void MainWindow::movePixel(double m[4], std::vector<std::array<int, 2>>* coords2D) {
    int x2D = cx + (m[0] * d) / (m[2] + d);
    int y2D = cy + (m[1] * d) / (m[2] + d);


    depths.push_back(m[2]);
    coords2D->push_back({x2D, y2D});
}

void MainWindow::drawCube(){

    zbuffer->renderObject(cubeCoordinates2D, depths, walls);


    for(int i = 0; i < rubikWallCoordinates2D.size() - 1; i+=2){
        int next = i + 1;
        QPoint point = QPoint(rubikWallCoordinates2D[i][0], rubikWallCoordinates2D[i][1]);
        QPoint oppositePoint = QPoint(rubikWallCoordinates2D[next][0], rubikWallCoordinates2D[next][1]);
        drawline->paintLine(point, oppositePoint, 255, 255, 255);
    }
}


