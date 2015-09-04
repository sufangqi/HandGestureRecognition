#ifndef HANGGUSTURECONTROL_H
#define HANGGUSTURECONTROL_H

#include <QWidget>
#include<QImage>
#include<QTimer>
#include<vector>
#include<opencv2/opencv.hpp>
using namespace cv;
enum MODES{detect_Palm,detect_Fist,Up,Down,Right,Left};
namespace Ui {
class HangGustureControl;
}

class HangGustureControl : public QWidget
{
    Q_OBJECT

public:
    explicit HangGustureControl(QWidget *parent = 0);
    ~HangGustureControl();
    QImage img;

private:
    Ui::HangGustureControl *ui;
    QTimer *timer;
    Mat frame;
    Mat displayedFrame;
    Mat binary_img;
    VideoCapture videoCapture;
    void HandGustureControlResult(Mat&inputimg,Mat&Result_RGB,Mat&Result_binary);
	MODES model;
	CascadeClassifier detector;


    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    double tmpara;
    vector<double> Area;
    Mat Area_t;
    Rect r0;
    Mat hand,gray_binary_copy;
    Point cogpt,PreviousCogpt;//当前帧重心的位置;
    Point right,left,up,down;
    Mat gray_binary;

    vector<Rect> facesRegionOne(Mat&im,int scaledWidth );
    void skin_detection(Mat&input,Mat &dist,int lowerCr,int upperCr,int lowerCb,int upperCb);
    void findContoursofimg(Mat&img,Mat&dst);
    void extractContourInfo(Mat&skinArea,Point &cogPt);
    double RecognitizeGesture(Mat&img);
    MODES drawButton(Mat &img,Point &cogpt,Point&currentGravity,Point&right,Point&left,Point&up,Point&down);

   


    void initWebcam();
    void showwarningmsg(QString MSG);
private slots:
    void readFrame();
    void changeSlidevalue(int value);
};

#endif // HANGGUSTURECONTROL_H
