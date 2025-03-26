#include "OpenGLSetup.h"
#include <QSurfaceFormat>
#include <QMatrix4x4>  // Dodajemy ten nagłówek
#include <iostream>

OpenGLSetup::OpenGLSetup(QWidget* parent)
    : QOpenGLWidget(parent) {
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    setFormat(format);
}

OpenGLSetup::~OpenGLSetup() {
    cleanupOpenGL();
}
void OpenGLSetup::initializeGL()
{
    initializeOpenGLFunctions();

    // Wczytywanie tekstury
    QImage texture = QImage(":/new/wallsImages/missingTexture.jpg");
    texture = texture.convertToFormat(QImage::Format_RGBA8888);

    // Tworzenie tekstury
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Ustawienie parametrów tekstury
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width(), texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Włączenie testowania głębokości
    glEnable(GL_DEPTH_TEST);

    // Inicjalizacja macierzy projektowania
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);  // Powrót do macierzy modelu
}

void OpenGLSetup::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);


}

void OpenGLSetup::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Wyczyść ekran i bufor głębokości

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);  // Przesuwamy widok

    // Aktywujemy teksturę
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Rysowanie podłogi (tekstura)
    glBegin(GL_QUADS);  // Rysowanie prostokąta
    // Ustawianie współrzędnych tekstury
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, 0.0f, -2.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.0f, 0.0f, -2.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f, 0.0f,  2.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 0.0f,  2.0f);
    glEnd();
}




void OpenGLSetup::cleanupOpenGL() {

}
