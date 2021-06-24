/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBoxPic;
    QLabel *labelPic;
    QGroupBox *groupBoxPrams;
    QLabel *labelK1;
    QLabel *labelK2;
    QLabel *labelK3;
    QLabel *labelP1;
    QLabel *labelP2;
    QLabel *labelSKEW;
    QLabel *labelFX;
    QLabel *labelFY;
    QLabel *labelOX;
    QLineEdit *lineEditK1;
    QLineEdit *lineEditK2;
    QLineEdit *lineEditK3;
    QLineEdit *lineEditP1;
    QLineEdit *lineEditP2;
    QLineEdit *lineEditSKEW;
    QLineEdit *lineEditFX;
    QLineEdit *lineEditFY;
    QLineEdit *lineEditOX;
    QLabel *labelOY;
    QLineEdit *lineEditOY;
    QFrame *line;
    QLabel *labelAngle;
    QLabel *labelDep;
    QLabel *labelLarge;
    QLabel *labelAbodon;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QGroupBox *groupBoxActs;
    QPushButton *pushButtonLoad;
    QPushButton *pushButtonSave;
    QProgressBar *progressBar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1096, 675);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBoxPic = new QGroupBox(centralwidget);
        groupBoxPic->setObjectName(QString::fromUtf8("groupBoxPic"));
        groupBoxPic->setGeometry(QRect(10, 0, 831, 611));
        labelPic = new QLabel(groupBoxPic);
        labelPic->setObjectName(QString::fromUtf8("labelPic"));
        labelPic->setGeometry(QRect(10, 20, 811, 581));
        groupBoxPrams = new QGroupBox(centralwidget);
        groupBoxPrams->setObjectName(QString::fromUtf8("groupBoxPrams"));
        groupBoxPrams->setGeometry(QRect(850, 0, 231, 461));
        labelK1 = new QLabel(groupBoxPrams);
        labelK1->setObjectName(QString::fromUtf8("labelK1"));
        labelK1->setGeometry(QRect(10, 30, 72, 15));
        labelK2 = new QLabel(groupBoxPrams);
        labelK2->setObjectName(QString::fromUtf8("labelK2"));
        labelK2->setGeometry(QRect(10, 60, 72, 15));
        labelK3 = new QLabel(groupBoxPrams);
        labelK3->setObjectName(QString::fromUtf8("labelK3"));
        labelK3->setGeometry(QRect(10, 90, 72, 15));
        labelP1 = new QLabel(groupBoxPrams);
        labelP1->setObjectName(QString::fromUtf8("labelP1"));
        labelP1->setGeometry(QRect(10, 120, 72, 15));
        labelP2 = new QLabel(groupBoxPrams);
        labelP2->setObjectName(QString::fromUtf8("labelP2"));
        labelP2->setGeometry(QRect(10, 150, 72, 15));
        labelSKEW = new QLabel(groupBoxPrams);
        labelSKEW->setObjectName(QString::fromUtf8("labelSKEW"));
        labelSKEW->setGeometry(QRect(10, 180, 72, 15));
        labelFX = new QLabel(groupBoxPrams);
        labelFX->setObjectName(QString::fromUtf8("labelFX"));
        labelFX->setGeometry(QRect(10, 210, 72, 15));
        labelFY = new QLabel(groupBoxPrams);
        labelFY->setObjectName(QString::fromUtf8("labelFY"));
        labelFY->setGeometry(QRect(10, 240, 72, 15));
        labelOX = new QLabel(groupBoxPrams);
        labelOX->setObjectName(QString::fromUtf8("labelOX"));
        labelOX->setGeometry(QRect(10, 270, 72, 15));
        lineEditK1 = new QLineEdit(groupBoxPrams);
        lineEditK1->setObjectName(QString::fromUtf8("lineEditK1"));
        lineEditK1->setGeometry(QRect(90, 30, 113, 21));
        lineEditK2 = new QLineEdit(groupBoxPrams);
        lineEditK2->setObjectName(QString::fromUtf8("lineEditK2"));
        lineEditK2->setGeometry(QRect(90, 60, 113, 21));
        lineEditK3 = new QLineEdit(groupBoxPrams);
        lineEditK3->setObjectName(QString::fromUtf8("lineEditK3"));
        lineEditK3->setGeometry(QRect(90, 90, 113, 21));
        lineEditP1 = new QLineEdit(groupBoxPrams);
        lineEditP1->setObjectName(QString::fromUtf8("lineEditP1"));
        lineEditP1->setGeometry(QRect(90, 120, 113, 21));
        lineEditP2 = new QLineEdit(groupBoxPrams);
        lineEditP2->setObjectName(QString::fromUtf8("lineEditP2"));
        lineEditP2->setGeometry(QRect(90, 150, 113, 21));
        lineEditSKEW = new QLineEdit(groupBoxPrams);
        lineEditSKEW->setObjectName(QString::fromUtf8("lineEditSKEW"));
        lineEditSKEW->setGeometry(QRect(90, 180, 113, 21));
        lineEditFX = new QLineEdit(groupBoxPrams);
        lineEditFX->setObjectName(QString::fromUtf8("lineEditFX"));
        lineEditFX->setGeometry(QRect(90, 210, 113, 21));
        lineEditFY = new QLineEdit(groupBoxPrams);
        lineEditFY->setObjectName(QString::fromUtf8("lineEditFY"));
        lineEditFY->setGeometry(QRect(90, 240, 113, 21));
        lineEditOX = new QLineEdit(groupBoxPrams);
        lineEditOX->setObjectName(QString::fromUtf8("lineEditOX"));
        lineEditOX->setGeometry(QRect(90, 270, 113, 21));
        labelOY = new QLabel(groupBoxPrams);
        labelOY->setObjectName(QString::fromUtf8("labelOY"));
        labelOY->setGeometry(QRect(10, 300, 72, 15));
        lineEditOY = new QLineEdit(groupBoxPrams);
        lineEditOY->setObjectName(QString::fromUtf8("lineEditOY"));
        lineEditOY->setGeometry(QRect(90, 300, 113, 21));
        line = new QFrame(groupBoxPrams);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 320, 231, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        labelAngle = new QLabel(groupBoxPrams);
        labelAngle->setObjectName(QString::fromUtf8("labelAngle"));
        labelAngle->setGeometry(QRect(10, 340, 72, 15));
        labelDep = new QLabel(groupBoxPrams);
        labelDep->setObjectName(QString::fromUtf8("labelDep"));
        labelDep->setGeometry(QRect(10, 370, 72, 15));
        labelLarge = new QLabel(groupBoxPrams);
        labelLarge->setObjectName(QString::fromUtf8("labelLarge"));
        labelLarge->setGeometry(QRect(10, 400, 72, 15));
        labelAbodon = new QLabel(groupBoxPrams);
        labelAbodon->setObjectName(QString::fromUtf8("labelAbodon"));
        labelAbodon->setGeometry(QRect(10, 430, 72, 15));
        lineEdit = new QLineEdit(groupBoxPrams);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(90, 340, 113, 21));
        lineEdit_2 = new QLineEdit(groupBoxPrams);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(90, 370, 113, 21));
        lineEdit_3 = new QLineEdit(groupBoxPrams);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(90, 400, 113, 21));
        lineEdit_4 = new QLineEdit(groupBoxPrams);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(90, 430, 113, 21));
        groupBoxActs = new QGroupBox(centralwidget);
        groupBoxActs->setObjectName(QString::fromUtf8("groupBoxActs"));
        groupBoxActs->setGeometry(QRect(850, 460, 231, 151));
        pushButtonLoad = new QPushButton(groupBoxActs);
        pushButtonLoad->setObjectName(QString::fromUtf8("pushButtonLoad"));
        pushButtonLoad->setGeometry(QRect(20, 30, 93, 28));
        pushButtonSave = new QPushButton(groupBoxActs);
        pushButtonSave->setObjectName(QString::fromUtf8("pushButtonSave"));
        pushButtonSave->setGeometry(QRect(130, 30, 93, 28));
        progressBar = new QProgressBar(groupBoxActs);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(30, 90, 191, 23));
        progressBar->setValue(0);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1096, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBoxPic->setTitle(QCoreApplication::translate("MainWindow", "picture", nullptr));
        labelPic->setText(QString());
        groupBoxPrams->setTitle(QCoreApplication::translate("MainWindow", "parameters", nullptr));
        labelK1->setText(QCoreApplication::translate("MainWindow", "K1", nullptr));
        labelK2->setText(QCoreApplication::translate("MainWindow", "K2", nullptr));
        labelK3->setText(QCoreApplication::translate("MainWindow", "K3", nullptr));
        labelP1->setText(QCoreApplication::translate("MainWindow", "P1", nullptr));
        labelP2->setText(QCoreApplication::translate("MainWindow", "P2", nullptr));
        labelSKEW->setText(QCoreApplication::translate("MainWindow", "SKEW", nullptr));
        labelFX->setText(QCoreApplication::translate("MainWindow", "FX", nullptr));
        labelFY->setText(QCoreApplication::translate("MainWindow", "FY", nullptr));
        labelOX->setText(QCoreApplication::translate("MainWindow", "OX", nullptr));
        labelOY->setText(QCoreApplication::translate("MainWindow", "OY", nullptr));
        labelAngle->setText(QCoreApplication::translate("MainWindow", "angle", nullptr));
        labelDep->setText(QCoreApplication::translate("MainWindow", "dep", nullptr));
        labelLarge->setText(QCoreApplication::translate("MainWindow", "large", nullptr));
        labelAbodon->setText(QCoreApplication::translate("MainWindow", "abodon", nullptr));
        groupBoxActs->setTitle(QCoreApplication::translate("MainWindow", "save and load", nullptr));
        pushButtonLoad->setText(QCoreApplication::translate("MainWindow", "loadPic", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("MainWindow", "saveParam", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
