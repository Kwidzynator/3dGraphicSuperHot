/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QSlider *translationSliderOX;
    QSlider *translationSliderOY;
    QSlider *rotationSliderOX;
    QSlider *scalingSliderOX;
    QSlider *scalingSliderOY;
    QSlider *shearingSliderOX;
    QSlider *shearingSliderOY;
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QSlider *translationSliderOZ;
    QSlider *scalingSliderOZ;
    QSlider *rotationSliderOY;
    QSlider *rotationSliderOZ;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(867, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        translationSliderOX = new QSlider(centralwidget);
        translationSliderOX->setObjectName("translationSliderOX");
        translationSliderOX->setGeometry(QRect(680, 30, 160, 22));
        translationSliderOX->setOrientation(Qt::Orientation::Horizontal);
        translationSliderOY = new QSlider(centralwidget);
        translationSliderOY->setObjectName("translationSliderOY");
        translationSliderOY->setGeometry(QRect(680, 60, 160, 22));
        translationSliderOY->setOrientation(Qt::Orientation::Horizontal);
        rotationSliderOX = new QSlider(centralwidget);
        rotationSliderOX->setObjectName("rotationSliderOX");
        rotationSliderOX->setGeometry(QRect(680, 140, 160, 22));
        rotationSliderOX->setOrientation(Qt::Orientation::Horizontal);
        scalingSliderOX = new QSlider(centralwidget);
        scalingSliderOX->setObjectName("scalingSliderOX");
        scalingSliderOX->setGeometry(QRect(680, 250, 160, 22));
        scalingSliderOX->setOrientation(Qt::Orientation::Horizontal);
        scalingSliderOY = new QSlider(centralwidget);
        scalingSliderOY->setObjectName("scalingSliderOY");
        scalingSliderOY->setGeometry(QRect(680, 280, 160, 22));
        scalingSliderOY->setOrientation(Qt::Orientation::Horizontal);
        shearingSliderOX = new QSlider(centralwidget);
        shearingSliderOX->setObjectName("shearingSliderOX");
        shearingSliderOX->setGeometry(QRect(680, 360, 160, 22));
        shearingSliderOX->setOrientation(Qt::Orientation::Horizontal);
        shearingSliderOY = new QSlider(centralwidget);
        shearingSliderOY->setObjectName("shearingSliderOY");
        shearingSliderOY->setGeometry(QRect(680, 390, 160, 22));
        shearingSliderOY->setOrientation(Qt::Orientation::Horizontal);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(680, 480, 75, 24));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(680, 10, 61, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(680, 120, 71, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(680, 230, 49, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(680, 340, 49, 16));
        translationSliderOZ = new QSlider(centralwidget);
        translationSliderOZ->setObjectName("translationSliderOZ");
        translationSliderOZ->setGeometry(QRect(680, 90, 160, 22));
        translationSliderOZ->setOrientation(Qt::Orientation::Horizontal);
        scalingSliderOZ = new QSlider(centralwidget);
        scalingSliderOZ->setObjectName("scalingSliderOZ");
        scalingSliderOZ->setGeometry(QRect(680, 310, 160, 22));
        scalingSliderOZ->setOrientation(Qt::Orientation::Horizontal);
        rotationSliderOY = new QSlider(centralwidget);
        rotationSliderOY->setObjectName("rotationSliderOY");
        rotationSliderOY->setGeometry(QRect(680, 170, 160, 22));
        rotationSliderOY->setOrientation(Qt::Orientation::Horizontal);
        rotationSliderOZ = new QSlider(centralwidget);
        rotationSliderOZ->setObjectName("rotationSliderOZ");
        rotationSliderOZ->setGeometry(QRect(680, 200, 160, 22));
        rotationSliderOZ->setOrientation(Qt::Orientation::Horizontal);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 867, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "reset", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "translation", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "rotation", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "scaling", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "shearing", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
