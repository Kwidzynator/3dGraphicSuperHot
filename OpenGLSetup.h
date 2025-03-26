#ifndef OPENGLSETUP_H
#define OPENGLSETUP_H

#include <QApplication>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>


class OpenGLSetup : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    explicit OpenGLSetup(QWidget* parent = nullptr);
    ~OpenGLSetup();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void drawFloor();


private:
    void initOpenGL();
    void cleanupOpenGL();
    GLuint textureID;
};

#endif
