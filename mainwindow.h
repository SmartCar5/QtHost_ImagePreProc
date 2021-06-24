#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "opencv.hpp"
#include <math.h>
#include <iostream>
using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void reNew();
    void on_pushButtonLoad_clicked();

    void on_lineEditK1_editingFinished();

    void on_lineEditK2_editingFinished();

    void on_lineEditK3_editingFinished();

    void on_lineEditP1_editingFinished();

    void on_lineEditP2_editingFinished();

    void on_lineEditSKEW_editingFinished();

    void on_lineEditFX_editingFinished();

    void on_lineEditFY_editingFinished();

    void on_lineEditOX_editingFinished();

    void on_lineEditOY_editingFinished();

    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_lineEdit_3_editingFinished();

    void on_lineEdit_4_editingFinished();

    void on_pushButtonSave_clicked();

private:
    void showImage(Mat pic);

private:
    Ui::MainWindow *ui;

    bool isChanged = false;
    bool isReverse = false;
    int changeCont = 0;
    int changeCont2 = 0;

    double fx;  //x轴焦距
    double fy;  //y轴焦距
    double u0;  //光心位置x
    double v0;  //光心位置y
    double k1;  //径向畸变
    double k2;
    double k3;
    double p1;  //切向畸变
    double p2;
    double skew;    //桶形畸变

    double angle;//摄像头俯仰角
    double dep;//视点到投影面距离
    double prop_j = 1;//上下宽度矫正，大于1				//不能调！！！！！！！！
    double prop_i = 0;//密度修正系数，大于-1，小于1	    //不能调！！！！！！！！
    double j_large = 1;//横向放大倍数
    uint8_t i_abodon = 0;//上方舍弃的行距离
    double hight = 9.5;//摄像头高度（调节也没有效果，只改变参数坐标）

    Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
    Mat distCoeffs = Mat::zeros(5, 1, CV_64F);
    Mat image,image2, map1, map2;
};
#endif // MAINWINDOW_H
