#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv.hpp"
#include "QString"
#include <qtimer.h>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>
#include <iostream>


using namespace cv;
using namespace std;

typedef uint8_t uint8 ;

//输入图片尺寸
#define CAMERA_H  120
#define CAMERA_W  188

//输出图片尺寸
#define OUT_H  120
#define OUT_W  188



uint8 img[CAMERA_H][CAMERA_W];
uint8 img_t[CAMERA_H][CAMERA_W];
uint8 img_out[OUT_H][OUT_W];
double map_square[CAMERA_H][CAMERA_W][2];//图像——》现实映射///
int map_int[OUT_H][OUT_W][2];//现实——》图像映射
uint8 left_side[OUT_H];//左边界
uint8 right_side[OUT_H];//右边界
uint8 j_fix[120][188];
uint8 i_fix[120];

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer* pTimer = new QTimer(this);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(reNew()));
    pTimer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reNew()
{
    if(isChanged==true&&changeCont>=10&&!image.empty())
    {
        cameraMatrix.at<double>(0, 0) = fx;
        cameraMatrix.at<double>(0, 1) = skew;
        cameraMatrix.at<double>(0, 2) = u0;
        cameraMatrix.at<double>(1, 1) = fy;
        cameraMatrix.at<double>(1, 2) = v0;

        distCoeffs.at<double>(0, 0) = k1;
        distCoeffs.at<double>(1, 0) = k2;
        distCoeffs.at<double>(2, 0) = p1;
        distCoeffs.at<double>(3, 0) = p2;
        distCoeffs.at<double>(4, 0) = k3;

        Mat view, rview;
        Size imageSize;
        imageSize = Size(188, 120);
        initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(),
            cameraMatrix,
            imageSize, CV_16SC2, map1, map2);
        remap(image, image2, map1, map2, INTER_LINEAR);
        showImage(image2);
        isChanged=false;
    }
    if(isReverse==true&&changeCont2>=4&&!image.empty())
    {
        Mat temp,rimg;
        rimg = Mat(120,188,CV_8UC1);
        if(!image2.empty())
        {
            temp = image2.clone();
        }
        else
        {
            temp = image.clone();
        }
        uint8 i;//图像从上到下行数
        uint8 j;//图像从左到右行数
        uint8 ii;
        //图片坐标
        double xg;
        double yg;
        //原始坐标
        double x0;
        double y0;

        double zt;

        double sin_a;
        double cos_a;
        sin_a = sin(angle);
        cos_a = cos(angle);

        //初始化摄像头坐标系
        for (i = 0; i<CAMERA_H; i++)
        {
            for (j = 0; j<CAMERA_W; j++)
            {
                map_square[i][j][0] = ((float)CAMERA_H / 2 - (float)i + 0.5) / 10;//为什么要除10！！！！想不起来了！！！！
                map_square[i][j][1] = ((float)j - (float)CAMERA_W / 2 + 0.5) / 10;
            }
        }

        //横向拉伸（微调）
        for (i = 0; i<CAMERA_H; i++)
        {
            for (j = 0; j<CAMERA_W; j++)
            {
                map_square[i][j][1] = map_square[i][j][1] * (1 * (CAMERA_H - 1 - i) + (1 / prop_j)*i) / (CAMERA_H - 1);
            }
        }

        //逆透视变换……直接套公式
        for (i = 0; i<CAMERA_H; i++)
        {
            for (j = 0; j<CAMERA_W; j++)
            {
                xg = map_square[i][j][1];
                yg = map_square[i][j][0];
                y0 = (yg*dep + hight*cos_a*yg + hight*dep*sin_a) / (dep*cos_a - yg*sin_a);
                zt = -y0*sin_a - hight*cos_a;
                x0 = xg * (dep - zt) / dep;
                map_square[i][j][1] = x0;
                map_square[i][j][0] = y0;
            }
        }
        //打印四个角的坐标
        //    printf("\n\n");
        //    print_xy(0,0);
        //    print_xy(0,CAMERA_W-1);
        //    printf("\n");
        //    print_xy(CAMERA_H-1,0);
        //    print_xy(CAMERA_H-1,CAMERA_W-1);
        //    printf("\n");

        //图像坐标转化为实际坐标之后，需要进行调整，以适应新图片的尺寸
        //坐标平移、放大、缩小
        //左右方向
        double prop_x;//横坐标缩放比例
        prop_x = (OUT_W - 1) / (map_square[i_abodon][CAMERA_W - 1][1] - map_square[i_abodon][0][1]);
        for (i = 0; i<CAMERA_H; i++)
        {
            for (j = 0; j<CAMERA_W; j++)
            {
                map_square[i][j][1] *= prop_x;
                map_square[i][j][1] *= j_large;
                map_square[i][j][1] = map_square[i][j][1] + OUT_W / 2 - 0.5*OUT_W / CAMERA_W;
            }
        }



        //前后方向
        double move_y;
        double prop_y;
        move_y = map_square[CAMERA_H - 1][0][0];
        for (i = 0; i<CAMERA_H; i++)
        {
            for (j = 0; j<CAMERA_W; j++)
            {
                map_square[i][j][0] -= move_y;
            }
        }
        prop_y = (OUT_H - 1) / map_square[i_abodon][0][0];
        for (i = 0; i<CAMERA_H; i++)
        {
            for (j = 0; j<CAMERA_W; j++)
            {
                map_square[i][j][0] *= prop_y;
                map_square[i][j][0] = OUT_H - OUT_H / CAMERA_H - map_square[i][j][0];
            }
        }

        //    printf("\n\n");
        //    print_xy(0,0);
        //    print_xy(0,CAMERA_W-1);
        //    printf("\n");
        //    print_xy(CAMERA_H-1,0);
        //    print_xy(CAMERA_H-1,CAMERA_W-1);
        //    printf("\n");

        //前后拉伸
        double dis_ever[CAMERA_H];
        double dis_add[CAMERA_H];
        double adjust_y[CAMERA_H];//每一行调整的值

        //计算每行代表的宽度（原为1）
        for (i = 0; i<CAMERA_H; i++)
        {
            dis_ever[i] = ((1 + prop_i)*(CAMERA_H - 1 - i) + (1 - prop_i)*i) / (CAMERA_H - 1);
        }
        dis_add[0] = 0;
        for (i = 0; i<CAMERA_H; i++)
        {
            if (i == 0)
            {
                dis_add[i] = 0;
            }
            else
            {
                dis_add[i] = dis_add[i - 1] + dis_ever[i - 1];
            }
        }
        adjust_y[0] = 1;
        for (i = 1; i<CAMERA_H; i++)
        {
            adjust_y[i] = dis_add[i] / i;
        }

        for (i = 0; i<CAMERA_H; i++)
        {
            for (j = 0; j<CAMERA_W; j++)
            {
                map_square[i][j][0] *= adjust_y[i];
            }
        }
        double y_fix;
        y_fix = (OUT_H - 1) / map_square[CAMERA_H - 1][0][0];
        for (i = 0; i<CAMERA_H; i++)
        {
            for (j = 0; j<CAMERA_W; j++)
            {
                map_square[i][j][0] *= y_fix;
            }
        }
        //逆映射,开始投入新尺寸的图像
        //前后方向
        double far;
        double far_min;
        int near;

        for (i = 0; i<OUT_H; i++)
        {
            far_min = OUT_H;
            for (ii = 0; ii<CAMERA_H; ii++)
            {
                far = (double)i - (double)(map_square[ii][CAMERA_H / 2][0]);
                if (far<0)
                {
                    far = -far;
                }
                if (far<far_min)
                {
                    far_min = far;
                    near = ii;
                }
            }
            for (j = 0; j<OUT_W; j++)
            {
                map_int[i][j][0] = near;
            }

        }
        //左右方向
        int jj;
        double left_lim;
        double right_lim;
        for (i = 0; i<OUT_H; i++)
        {
            //计算每一行要按照哪一行来取
            ii = map_int[i][OUT_W / 2][0];
            left_lim = map_square[ii][0][1];
            right_lim = map_square[ii][CAMERA_W - 1][1];
            for (j = 0; j<OUT_W; j++)
            {
                if (j<left_lim - 1 || j>right_lim + 1)
                {
                    map_int[i][j][1] = 255;
                }
                else
                {
                    far_min = CAMERA_W;
                    for (jj = 0; jj<CAMERA_W; jj++)
                    {
                        far = (double)j - (double)(map_square[ii][jj][1]);
                        if (far<0)
                        {
                            far = -far;
                        }

                        if (far<far_min)
                        {
                            far_min = far;
                            near = jj;
                        }

                    }
                    map_int[i][j][1] = near;

                }

            }

        }


        //修改图像
        for (i = 0; i<OUT_H; i++)
        {
            for (j = 0; j<OUT_W; j++)
            {
                if (map_int[i][j][1] == 255)
                {
                    rimg.ptr<uint8_t>(i)[j] = 0x77;
                }
                else
                {
                    rimg.ptr<uint8_t>(i)[j] = temp.ptr<uint8_t>(map_int[i][j][0])[map_int[i][j][1]];
                    //img_out[i][j] = img[y[i][j]][x[i][j]];
                }
            }
        }

        //计算

        uint8 start_flag;//右边界
        for (i = 0; i<OUT_H; i++)
        {
            start_flag = 0;
            for (j = 0; j<OUT_W; j++)
            {
                if (!start_flag)
                {
                    if (map_int[i][j][1] == 255)
                    {
                        continue;
                    }
                    else
                    {
                        left_side[i] = j;
                        start_flag = 1;
                    }
                }
                else
                {
                    if (
                        j == OUT_W - 1
                        )
                    {
                        right_side[i] = j;
                        break;
                    }
                    if (map_int[i][j][1] == 255)
                    {
                        right_side[i] = j - 1;
                        break;
                    }
                }
            }
        }
        for (i = 0; i<OUT_H; i++)
        {
            i_fix[i] = map_int[i][0][0];
        }
        for (i = 0; i<OUT_H; i++)
        {
            for (j = 0; j<OUT_W; j++)
            {
                j_fix[i][j] = map_int[i][j][1];
            }
        }
        showImage(rimg);
        isReverse = false;
    }
}

void MainWindow::showImage(Mat pic)
{
    uint8_t x[120 * 188] = { 0 };
    for (int i = 0; i < 120; i++)
    {
        for (int j = 0; j < 188; j++)
        {
            x[i * 188 + j] = pic.ptr<uint8_t>(i)[j];
        }
    }
    QImage img = QImage(x,pic.cols,pic.rows,QImage::Format_Grayscale8);
    QPixmap map = QPixmap::fromImage(img);
    ui->labelPic->setPixmap(map.scaled(ui->labelPic->size()));
}

void MainWindow::on_pushButtonLoad_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "choose src File","D:\\CODE\\");
    image = imread(path.toStdString(),IMREAD_GRAYSCALE);
    showImage(image);
}

void MainWindow::on_lineEditK1_editingFinished()
{
    k1 = ui->lineEditK1->text().toDouble();
    isChanged = true;
    changeCont++;
}

void MainWindow::on_lineEditK2_editingFinished()
{
    k2 = ui->lineEditK2->text().toDouble();
    isChanged = true;
    changeCont++;
}

void MainWindow::on_lineEditK3_editingFinished()
{
    k3 = ui->lineEditK3->text().toDouble();
    isChanged = true;
    changeCont++;
}

void MainWindow::on_lineEditP1_editingFinished()
{
    p1 = ui->lineEditP1->text().toDouble();
    isChanged = true;
    changeCont++;
}

void MainWindow::on_lineEditP2_editingFinished()
{
    p2 = ui->lineEditP2->text().toDouble();
    isChanged = true;
    changeCont++;
}

void MainWindow::on_lineEditSKEW_editingFinished()
{
    skew = ui->lineEditSKEW->text().toDouble();
    isChanged = true;
    changeCont++;
}

void MainWindow::on_lineEditFX_editingFinished()
{
    fx = ui->lineEditFX->text().toDouble();
    isChanged = true;
    changeCont++;
}

void MainWindow::on_lineEditFY_editingFinished()
{
    fy = ui->lineEditFY->text().toDouble();
    isChanged = true;
    changeCont++;
}

void MainWindow::on_lineEditOX_editingFinished()
{
    u0 = ui->lineEditOX->text().toDouble();
    isChanged = true;
    changeCont++;
}

void MainWindow::on_lineEditOY_editingFinished()
{
    v0 = ui->lineEditOY->text().toDouble();
    isChanged = true;
    changeCont++;
}

void MainWindow::on_lineEdit_editingFinished()
{
    angle = ui->lineEdit->text().toDouble();
    isReverse = true;
    changeCont2++;
}

void MainWindow::on_lineEdit_2_editingFinished()
{
    dep = ui->lineEdit_2->text().toDouble();
    isReverse = true;
    changeCont2++;
}

void MainWindow::on_lineEdit_3_editingFinished()
{
    j_large = ui->lineEdit_3->text().toDouble();
    isReverse = true;
    changeCont2++;
}

void MainWindow::on_lineEdit_4_editingFinished()
{
    i_abodon = ui->lineEdit_4->text().toUShort();
    isReverse = true;
    changeCont2++;
}

void MainWindow::on_pushButtonSave_clicked()
{
    int x[120 * 188] = { 0 };
    int y[120 * 188] = { 0 };
    for (int i = 0; i < 120; i++)
    {
        for (int j = 0; j < 188; j++)
        {
            x[i * 188 + j] = map1.at<Vec<int16_t, 2>>(119-i, 187-j)[0];
            y[i * 188 + j] = map1.at<Vec<int16_t, 2>>(119-i, 187-j)[1];
            if (x[i * 188 + j] > 187)x[i * 188 + j] = 187;
            if (x[i * 188 + j] < 0)x[i * 188 + j] = 0;
            if (y[i * 188 + j] > 119)y[i * 188 + j] = 119;
            if (y[i * 188 + j] < 0)y[i * 188 + j] = 0;
        }
    }
    int x_new[120][188];
    int y_new[120][188];
    Point2i points_out[120][188];
    Point2i points[120][188];
    for (int i = 0; i < 120; i++)
    {
        for (int j = 0; j < 188; j++)
        {
            points[i][j].x = x[i * 188 + j];
            points[i][j].y = y[i * 188 + j];
        }
    }
    int i;
    int j;
    uint8_t* pp = NULL;
    uint8_t* ss = NULL;
    pp = &left_side[0];
    ss = &right_side[0];
    Point2i* str = NULL;
    Point2i* ptr = NULL;
    str = &points_out[0][0];//变换后数组
    ptr = &points[0][0];//变换前数组
    uint8_t* pptr = NULL;
    uint8_t* sstr = NULL;
    pptr = &i_fix[0];
    sstr = &j_fix[0][0];
    int j_begin, j_end;
    Point2i* tstr = NULL;
    uint8_t* tsstr = NULL;
    Point2i* tptr = NULL;
    for (i = 0; i < 120; i++)
    {
        j_begin = *(pp + i);
        j_end = *(ss + i);
        tstr = str + i * 188;
        tsstr = sstr + i * 188;
        tptr = ptr + *(pptr + i) * 188;
        for (j = j_begin; j <= j_end; j++)
        {
            *(tstr + j) = *(tptr + *(tsstr + j));
        }
    }
    for (int i = 0; i < 120; i++)
    {
        for (int j = 0; j < 188; j++)
        {
            x_new[i][j] = points_out[i][j].x;
            y_new[i][j] = points_out[i][j].y;
        }
    }
    ui->progressBar->setValue(10);
    QString path = QFileDialog::getSaveFileName(this, "choose dst File","D:\\CODE\\");
    QFile file(path);
    file.open(QIODevice::ReadWrite);
    QDataStream stm(&file);
    file.write( "uint8_t left_side[120] = {",sizeof ("uint8_t left_side[120] = {"));
    for(int i = 0;i<120;i++)
    {
        file.write( QString("%1").arg(left_side[i]).toStdString().data(),QString("%1").arg(left_side[i]).toStdString().length());
        if(i!=119) file.write( ",",sizeof (","));
        else file.write( "};\n",sizeof ("};\n"));
        ui->progressBar->setValue(10+i/12);
    }
    file.write( "uint8_t right_side[120] = {",sizeof("uint8_t right_side[120] = {"));
    for(int i = 0;i<120;i++)
    {
        file.write( QString("%1").arg(right_side[i]).toStdString().data(),QString("%1").arg(right_side[i]).toStdString().length());
        if(i!=119) file.write( ",",sizeof (","));
        else file.write( "};\n",sizeof("};\n"));
        ui->progressBar->setValue(20+i/12);
    }

    file.write( "int x[120][188] = {",sizeof("int x[120][188] = {"));
    for (int i = 0; i < 120; i++)
    {
        for (int j = 0; j < 188; j++)
        {
            file.write( QString("%1").arg(x_new[i][j]).toStdString().data(),QString("%1").arg(x_new[i][j]).toStdString().length());
            if (i != 119 || j != 187)file.write( ",",sizeof(","));
        }
        if (i != 119)file.write( "\n",sizeof("\n"));
        else file.write( "};\n",sizeof("};\n"));
    }
    ui->progressBar->setValue(65);
    file.write( "int y[120][188] = {",sizeof("int y[120][188] = {"));
    for (int i = 0; i < 120; i++)
    {
        for (int j = 0; j < 188; j++)
        {
            file.write( QString("%1").arg(y_new[i][j]).toStdString().data(), QString("%1").arg(y_new[i][j]).toStdString().length());
            if (i != 119 || j != 187)file.write( ",",sizeof(","));
        }
        if (i != 119)file.write( "\n",sizeof("\n"));
        else file.write( "};\n",sizeof ("};\n"));
    }
    ui->progressBar->setValue(100);
    file.close();
    QMessageBox msg;
    msg.about(NULL,"INFO","The argument has been saved");
    ui->progressBar->setValue(0);
}

void MainWindow::on_pushButtonUndistort_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, "choose dst File","D:\\CODE\\");
    QDir dir(path);
    //要判断路径是否存在
    if(!dir.exists())
    {
        qDebug() << "it is not true path";
        return ;
    }
    QStringList filters;
        filters<<QString("*.jpeg")<<QString("*.jpg");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);//实现对文件的过滤
    dir.setSorting(QDir::Size | QDir::Reversed);//实现对文件输出的排序
    dir.setNameFilters(filters);  //设置文件名称过滤器，只为filters格式（后缀为.jpeg等图片格式）

    QFileInfoList list = dir.entryInfoList();
    vector<Mat> imgs;

    for (int i = 0; i < list.size(); ++i)
    {
         QFileInfo fileInfo = list.at(i);
         QString absolute_file_path = fileInfo.absoluteFilePath();
         imgs.push_back(imread(absolute_file_path.toStdString(),IMREAD_GRAYSCALE));
    }
    QMessageBox msg;
    msg.about(NULL,"INFO",QString("%1").arg(list.size()));
    QInputDialog log;
    int row = log.getInt(NULL,"row","row");
    int col = log.getInt(NULL,"col","col");
    Size board_size = Size(row, col);  //方格标定板内角点数目（行，列）
    vector<vector<Point2f>> imgsPoints;
    for (unsigned long long i = 0; i < imgs.size(); i++)
    {
        try
        {
            //Mat img1 = imgs[i];
            Mat gray1 = imgs[i];
            //cvtColor(img1, gray1, COLOR_BGR2GRAY);
            vector<Point2f> img1_points;
            findChessboardCorners(gray1, board_size, img1_points);  //计算方格标定板角点
            find4QuadCornerSubpix(gray1, img1_points, Size(5, 5));  //细化方格标定板角点坐标
            imgsPoints.push_back(img1_points);
        }
        catch (exception& e)
        {
            imgs.erase(imgs.begin()+i);
            i--;
        }

    }
    msg.about(NULL,"INFO",QString("%1").arg(imgs.size()));
    //生成棋盘格每个内角点的空间三维坐标
    int length = log.getInt(NULL,"length","length");
    Size squareSize = Size(length, length);  //棋盘格每个方格的真实尺寸
    vector<vector<Point3f>> objectPoints;
    for (unsigned long long i = 0; i < imgsPoints.size(); i++)
    {
        vector<Point3f> tempPointSet;
        for (int j = 0; j < board_size.height; j++)
        {
            for (int k = 0; k < board_size.width; k++)
            {
                Point3f realPoint;
                // 假设标定板为世界坐标系的z平面，即z=0
                realPoint.x = j*squareSize.width;
                realPoint.y = k*squareSize.height;
                realPoint.z = 0;
                tempPointSet.push_back(realPoint);
            }
        }
        objectPoints.push_back(tempPointSet);
    }

    /* 初始化每幅图像中的角点数量，假定每幅图像中都可以看到完整的标定板 */
    vector<int> point_number;
    for (unsigned long long i = 0; i<imgsPoints.size(); i++)
    {
        point_number.push_back(board_size.width*board_size.height);
    }

    //图像尺寸
    Size imageSize;
    imageSize.width = imgs[0].cols;
    imageSize.height = imgs[0].rows;

   // Mat Matrix = Mat(3, 3, CV_32FC1, Scalar::all(0));  //摄像机内参数矩阵
    //Mat Coeffs = Mat(1, 5, CV_32FC1, Scalar::all(0));  //摄像机的5个畸变系数：k1,k2,p1,p2,k3
    vector<Mat> rvecs;  //每幅图像的旋转向量
    vector<Mat> tvecs;  //每张图像的平移量
    calibrateCamera(objectPoints, imgsPoints, imageSize, cameraMatrix, distCoeffs, rvecs, tvecs, 0);

    /*cout << "相机的内参矩阵=" << endl << cameraMatrix << endl;
    cout << "相机畸变系数" << distCoeffs << endl;*/
    fx = cameraMatrix.at<double>(0, 0);
    skew = cameraMatrix.at<double>(0, 1);
    u0 = cameraMatrix.at<double>(0, 2);
    fy = cameraMatrix.at<double>(1, 1);
    v0 = cameraMatrix.at<double>(1, 2);

    k1 = distCoeffs.at<double>(0, 0);
    k2 = distCoeffs.at<double>(1, 0);
    p1 = distCoeffs.at<double>(2, 0);
    p2 = distCoeffs.at<double>(3, 0);
    k3 = distCoeffs.at<double>(4, 0);

    ui->lineEditFX->setText(QString("%1").arg(fx));
    ui->lineEditSKEW->setText(QString("%1").arg(skew));
    ui->lineEditOX->setText(QString("%1").arg(u0));
    ui->lineEditFY->setText(QString("%1").arg(fy));
    ui->lineEditOY->setText(QString("%1").arg(v0));
    ui->lineEditK1->setText(QString("%1").arg(k1));
    ui->lineEditK2->setText(QString("%1").arg(k2));
    ui->lineEditP1->setText(QString("%1").arg(p1));
    ui->lineEditP2->setText(QString("%1").arg(p2));
    ui->lineEditK3->setText(QString("%1").arg(k3));

    isChanged = true;
    changeCont+=11;
}
