#include "hanggusturecontrol.h"
#include "ui_hanggusturecontrol.h"
#include<Windows.h>
#include<opencv2/opencv.hpp>
#include<QMessageBox>
#include <vector>
using namespace std;
using namespace cv;
HangGustureControl::HangGustureControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HangGustureControl)
{
    ui->setupUi(this);
    timer   = new QTimer(this);
	model=detect_Palm;
    Sleep(1000);
    initWebcam();
    ui->Slider->setMinimum(0);
    ui->Slider_2->setMinimum(0);
    ui->Slider_3->setMinimum(0);
    ui->Slider_4->setMinimum(0);
    ui->Slider->setMaximum(255);
    ui->Slider_2->setMaximum(255);
    ui->Slider_3->setMaximum(255);
    ui->Slider_4->setMaximum(255);
    ui->Slider->setValue(140);
    ui->Slider_2->setValue(200);
    ui->Slider_3->setValue(80);
    ui->Slider_4->setValue(200);
	int pos = ui->Slider->value();
    int pos_2=ui->Slider_2->value();
    int pos_3=ui->Slider_3->value();
    int pos_4=ui->Slider_4->value();
    QString str = QString("%1").arg(pos);
    QString str_2 = QString("%1").arg(pos_2);
    QString str_3 = QString("%1").arg(pos_3);
    QString str_4 = QString("%1").arg(pos_4);
    ui->label->setText(str);
    ui->label_2->setText(str_2);
    ui->label_3->setText(str_3);
    ui->label_4->setText(str_4);
    detector.load("haarcascade_frontalface_alt2.xml");
    connect(timer, SIGNAL(timeout()), this, SLOT(readFrame()));  // 时间到，读取当前摄像头信息
    connect(ui->Slider, SIGNAL(valueChanged(int)), this, SLOT(changeSlidevalue(int)));
    connect(ui->Slider_2, SIGNAL(valueChanged(int)), this, SLOT(changeSlidevalue(int)));
    connect(ui->Slider_3, SIGNAL(valueChanged(int)), this, SLOT(changeSlidevalue(int)));
    connect(ui->Slider_4, SIGNAL(valueChanged(int)), this, SLOT(changeSlidevalue(int)));

}
void HangGustureControl::initWebcam()
{   // Load the face and 1 or 2 eye detection XML classifiers.
    //initDetectors(faceCascade, eyeCascade1, eyeCascade2);
    // Get access to the default camera.
        videoCapture.open(0);
        videoCapture.set(CV_CAP_PROP_FRAME_WIDTH,640);
        videoCapture.set(CV_CAP_PROP_FRAME_HEIGHT,480);
    if ( !videoCapture.isOpened() )
	{
        //cerr << "ERROR: Could not access the camera!" << endl;
        showwarningmsg(tr("ERROR: Could not access the camera!"));
        exit(1);
    }
    //cout << "Loaded camera " << cameraNumber << "." << endl;
    timer->start(0);
}
void HangGustureControl::readFrame()
{
    videoCapture.read(frame);// 从摄像头中抓取并返回每一帧
    flip(frame,frame,1);

    if( frame.empty() ) {
        showwarningmsg("ERROR: Couldn't grab the next camera frame.");
        exit(1);
    }
    frame.copyTo(displayedFrame);

    HandGustureControlResult(displayedFrame, displayedFrame,binary_img);

    cv::resize(displayedFrame,displayedFrame,cv::Size(640,480));
    cv::cvtColor(displayedFrame,displayedFrame,CV_RGB2BGR);
    cv::cvtColor(binary_img,binary_img,CV_RGB2BGR);
    // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式。

    QImage image_RGB((const uchar*)displayedFrame.data, displayedFrame.cols, displayedFrame.rows,displayedFrame.cols*displayedFrame.channels(), QImage::Format_RGB888);
    ui->label_RGB->setPixmap(QPixmap::fromImage(image_RGB));  // 将图片显示到label上
    ui->label_RGB->resize(ui->label_RGB->pixmap()->size());

    QImage image_binary((const uchar*)binary_img.data, binary_img.cols, binary_img.rows,displayedFrame.cols*binary_img.channels(),QImage::Format_RGB888);
    ui->label_binary->setPixmap(QPixmap::fromImage(image_binary));  // 将二值图片显示到label上
    ui->label_binary->resize(ui->label_binary->pixmap()->size());


}
vector<Rect> HangGustureControl::facesRegionOne(Mat&im,int scaledWidth )
{
    Mat gray;
    
     if(detector.empty())
    {
        std::cout<<0;
    }
    if(im.channels()==1){gray=im;}else{cvtColor(im,gray,CV_BGR2GRAY);}
    Mat inputImg;

  // Enlarge the results if the image was temporarily shrunk before detection.
  float scales=im.cols/scaledWidth;
  if(im.cols>scaledWidth)
  {
      int scaledHeight=cvRound(im.rows/scales);
      cv::resize(gray,inputImg,Size(scaledWidth,scaledHeight));
    // equalizeHist(inputImg,inputImg);
  }
  else
  {
      inputImg=gray;
     // equalizeHist(inputImg,inputImg);
  }
    vector<Rect>faces;
    detector.detectMultiScale(inputImg,faces,1.1,4,CV_HAAR_SCALE_IMAGE
                ,Size(30,30));


if(faces.size()>0)
{
    //还原人脸坐标
    if(im.cols>scaledWidth)
  {
      for(int i=0;i<(int)faces.size();i++)
      {
          faces[i].x=cvRound(faces[i].x*scales);
          faces[i].y=cvRound(faces[i].y*scales);
          faces[i].width=cvRound(faces[i].width*scales);
          faces[i].height=cvRound(faces[i].height*scales);
      }
  }
   // Make sure the object is completely within the image, in case it was on a border.
  for (int i = 0; i < (int)faces.size(); i++ ) {
      if (faces[i].x < 0)
            faces[i].x = 0;
        if (faces[i].y < 0)
            faces[i].y = 0;
        if (faces[i].x + faces[i].width > im.cols)
            faces[i].x = im.cols - faces[i].width;
        if (faces[i].y + faces[i].height > im.rows)
            faces[i].y = im.rows - faces[i].height;
    }
        return faces;
}
else
{return vector<Rect>();}
}
void HangGustureControl::changeSlidevalue(int value)
{
    int pos = ui->Slider->value();
    int pos_2=ui->Slider_2->value();
    int pos_3=ui->Slider_3->value();
    int pos_4=ui->Slider_4->value();


    QString str = QString("%1").arg(pos);
    QString str_2 = QString("%1").arg(pos_2);
    QString str_3 = QString("%1").arg(pos_3);
    QString str_4 = QString("%1").arg(pos_4);

    ui->label->setText(str);
    ui->label_2->setText(str_2);
    ui->label_3->setText(str_3);
    ui->label_4->setText(str_4);
}
void HangGustureControl::skin_detection(Mat&input,Mat &dist,int lowerCr,int upperCr,int lowerCb,int upperCb)
{

    Mat img0;
    cvtColor(input,img0,CV_BGR2YCrCb);
    vector<Mat> Ycbcr;
    split(img0,Ycbcr);
    Mat imgCr=Ycbcr[1];
    Mat imgCb=Ycbcr[2];
    int nr=imgCr.rows;
    int nc=imgCb.cols;
    dist.create(imgCb.size(),CV_8UC1);
     if(imgCb.isContinuous()&&dist.isContinuous())
    {
        nr=1;
        nc=nc*imgCb.rows*imgCb.channels();
    }
    for(int i=0;i<nr;i++)
    {
        const uchar*inDataCr=imgCr.ptr<uchar>(i);
        const uchar*inDataCb=imgCr.ptr<uchar>(i);
              uchar*outData=dist.ptr<uchar>(i);
       for(int j=0;j<nc;j++)
 {
     if((*inDataCr<=upperCr&&*inDataCr>=lowerCr&&*inDataCb<=upperCb&&*inDataCb>=lowerCb))
        {
            *outData=255;
        }
        else
        {
            *outData=0;
        }
        *inDataCr++;
        *inDataCb++;
        *outData++;
    }
    }
    Mat element = getStructuringElement(MORPH_RECT,
                                        Size(3,3)
                                  );
    //腐蚀操作
    medianBlur(dist,dist,3);
    erode(dist,dist,element,Point(-1, -1),3);
    dilate(dist,dist,element,Point(-1, -1),3);

}
void HangGustureControl::findContoursofimg(Mat&img,Mat&dst)
{
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    dst = Mat::zeros(img.rows, img.cols, CV_8UC3);
    findContours(img,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE);
    int idx = 0;

    for( ; idx >= 0; idx = hierarchy[idx][0] )
    {
        Scalar color( rand()&255, rand()&255, rand()&255 );


    }
}
void HangGustureControl::extractContourInfo(Mat&skinArea,Point &cogPt)
{
    Moments moment=moments(skinArea,true);
    double m00=moment.m00;
    double m10=moment.m10;
    double m01=moment.m01;
    if(m00!=0)
    {
        int xCenter=(int)cvRound(m10/m00);
        int yCenter=(int)cvRound(m01/m00);
        cogPt.x=xCenter;
        cogPt.y=yCenter;
    }


}
double HangGustureControl::RecognitizeGesture(Mat&img)
{
    Mat gray_img;
    if(img.channels()==3)
    {
        cvtColor(img,gray_img,CV_BGR2GRAY);
    }
    else
    {
        gray_img=img;
    }
    int validStep=10;
    int lineCount=10;
    int nr=gray_img.rows;
    int nc=gray_img.cols;
    int lineDistance=gray_img.cols/(lineCount+1);
    int numberofinger=0;
    vector<int> NumberOfingerAline;//在扫描过程中，每一行手指的个数
    if(gray_img.isContinuous())
    {
        nr=1;
        nc=nc*gray_img.rows*gray_img.channels();
    }
    for(int h=0;h<nr;h=h+lineDistance)
    {
        int acc=0;
        bool stratCount=false;
        int lastPixel=0;

        for(int w=0;w<nc;w++)
        {
            double currentPixel=gray_img.at<uchar>(h,w);
            if(lastPixel==currentPixel)
            {
                acc++;
            }
            else//change,i.e.boarder
            {
                if(lastPixel==255)
                {//white to black
                }
                else//black to white
                {
                    if(stratCount==false)
                    {
                        stratCount=true;
                    }
                    else
                    {
                        if(acc>=validStep)
                        {
                            numberofinger++;
                        }
                    }
                }
                lastPixel=currentPixel;
                acc=0;
            }
        }
        NumberOfingerAline.push_back(numberofinger);

    }
    Scalar meanvalue=mean(NumberOfingerAline);
    double value=meanvalue(0);
    return value;

}
MODES HangGustureControl:: drawButton(Mat &img,Point &cogpt,Point&currentGravity,Point&right,Point&left,Point&up,Point&down)
{
   
    int distance=80;
    if(cogpt.y-distance>0)
     {up.x=cogpt.x;
      up.y=cogpt.y-distance;
     }
    else
    {up.x=cogpt.x;
     up.y=10;
    }//上面的圆点

    if(cogpt.y+distance<img.rows)
    {
        down.x=cogpt.x;
        down.y=cogpt.y+distance;
    }
    else
    {
        down.x=cogpt.x;
        down.y=img.rows-10;
    }//重心下面的圆点


    if(cogpt.x-distance>0)
    {left.y=cogpt.y;
    left.x=cogpt.x-distance;
    }
    else
    {
        left.y=cogpt.y;
        left.x=10;
    }//重心左面的点


    if(cogpt.x+distance<img.cols)
    {
        right.y=cogpt.y;
        right.x=cogpt.x+distance;
    }
    else
    {
        right.y=cogpt.y;
        right.x=img.cols-10;
    }//重心右面的点

    //画出重心前后左右的点
    circle(img, up, 20 ,Scalar(0, 0, 255));
    circle(img, down, 20 ,Scalar(0, 0, 255));
    circle(img, left, 20 ,Scalar(0, 0, 255));
    circle(img, right, 20 ,Scalar(0, 0, 255));

    if(currentGravity.x-right.x>0)
    {
        //向右运动
       // circle(img, right, 20 ,Scalar(0, 255, 255),CV_FILLED);
		//putText(img,"Right",right,FONT_HERSHEY_PLAIN,5.0,CV_RGB(0,255,0),8.0);
        return Right;
    }
    else if(currentGravity.x-left.x<0)
    {//向左运动
		//putText(img,"Left",left,FONT_HERSHEY_PLAIN,5.0,CV_RGB(0,255,0),8.0);
        //circle(img, left, 20 ,Scalar(255, 0, 255),CV_FILLED);
        return Left;
    }
    else if(currentGravity.y-up.y<0)
    {//向上运动
		//putText(img,"Up",up,FONT_HERSHEY_PLAIN,5.0,CV_RGB(0,255,0),8.0);
        //circle(img, up, 20 ,Scalar(255, 255, 0),CV_FILLED);
        return Up;
    }
    else if(currentGravity.y-down.y>0)
    {
        //向下运动
		//putText(img,"Down",down,FONT_HERSHEY_PLAIN,5.0,CV_RGB(0,255,0),8.0);
       // circle(img, down, 20 ,Scalar(255, 255, 255),CV_FILLED);
        return Down;
    }
    else
    {
        return detect_Fist;
    }


}
void HangGustureControl::HandGustureControlResult(Mat &inputimg, Mat &Result_RGB, Mat &Result_binary)
{
        skin_detection(inputimg,gray_binary,ui->Slider->value(),ui->Slider_2->value(),ui->Slider_3->value(),ui->Slider_4->value());
       vector<Rect> face=facesRegionOne(inputimg,160);
	   for(int i=0;i<face.size();i++)
			{
		gray_binary(face[i])=0;
	   }
	
		inputimg.copyTo(Result_RGB);
		gray_binary.copyTo(gray_binary_copy);

        Result_binary = Mat::zeros(gray_binary.rows, gray_binary.cols, CV_8UC3);
                findContours(gray_binary, contours, hierarchy,
                CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE );

        // iterate through all the top-level contours,
        // draw each connected component with its own random color
                Point idxmax=Point(-1,-1);
				 tmpara=0;
            if(contours.size()>0)
            {
                for( int idx = 0; idx <contours.size();idx ++ )
                {
					Rect FaceROI=boundingRect(Mat(contours[idx]));
					
                  
				    tmpara=contourArea(contours[idx]);
                    Area.push_back(tmpara);
					
                    //if(tmpara>5000)
                    //{
                       // drawContours( Result_binary, contours, idx, color,0, 8, hierarchy );

                    //}


                }
                Mat(Area).copyTo(Area_t);
                minMaxLoc(Area_t,NULL,NULL,NULL,&idxmax);
				
                tmpara=contourArea(contours[idxmax.y]);
                vector<Point> couPoint = contours[idxmax.y];
                Point fingerTips;

                if(tmpara>5000)
                    {
				    Scalar color( rand()&255, rand()&255, rand()&255 );
			        drawContours( Result_binary, contours, idxmax.y, color,0, 8, hierarchy );//画出面积最大的连通域
                    r0 = boundingRect(Mat(contours[idxmax.y]));
                    hand=gray_binary_copy(r0);

                     extractContourInfo(hand,cogpt);//寻找重心

                     double value=RecognitizeGesture(hand(Rect(0,0,hand.cols,cogpt.y)));

                    std::cout<<value<<std::endl;

                    //寻找指尖
                    Point tmp;
                    int max=0,notice(0),sumDistance(0),meanDistance(0);
                    for (int i = 0; i < couPoint.size(); i++)
                    {
                        tmp = couPoint[i];
                        int dist = sqrt((tmp.x -cogpt.x-r0.x) * (tmp.x - cogpt.x-r0.x) + (tmp.y - cogpt.y-r0.y) * (tmp.y - cogpt.y-r0.y));
                        sumDistance=sumDistance+dist;
                        if (dist > max&&tmp.y<cogpt.y)//  寻找距离最大点
                        {
                            max = dist;
                            notice = i;
                        }


                    }
                    meanDistance=sumDistance/couPoint.size();//平均距离
                    fingerTips=couPoint[notice];//指尖位置
                     //寻找指尖
					//画出指尖所在位置
                     if(sqrt((fingerTips.x -cogpt.x-r0.x) * (fingerTips.x - cogpt.x-r0.x) + (fingerTips.y - cogpt.y-r0.y) * (fingerTips.y - cogpt.y-r0.y))/(double)meanDistance>1.6)
                     {
                       circle(Result_RGB, Point(fingerTips.x,fingerTips.y), 10 ,Scalar(180, 255, 0), CV_FILLED);
                       circle(Result_RGB, Point(cogpt.x+r0.x,cogpt.y+r0.y), 10 ,Scalar(255, 0, 0), CV_FILLED);//重心
					    model=detect_Palm;
                      }
                     //画出指尖所在位置

                    if(value>3&&value<9)
                     {
                     model=detect_Fist;
					 circle(Result_RGB, Point(cogpt.x+r0.x,cogpt.y+r0.y), meanDistance ,Scalar(0, 0, 255));//重心与平均距离
                     circle(Result_RGB, Point(cogpt.x+r0.x,cogpt.y+r0.y), 10 ,Scalar(255, 0, 0), CV_FILLED);//重心
					 putText(Result_RGB,"Plam",Point(r0.x,r0.y),FONT_HERSHEY_PLAIN,5.0,CV_RGB(0,255,0),8.0);
                    // rectangle(Result_RGB,Rect(r0.x,r0.y,r0.width,cogpt.y),Scalar(0),2);//手掌找到
                     
                     
                     PreviousCogpt=Point(cogpt.x+r0.x,cogpt.y+r0.y);
                    }
                    else  if (model==detect_Fist&&value<1)
                    {
						 putText(Result_RGB,"Fist",Point(r0.x,r0.y),FONT_HERSHEY_PLAIN,5.0,CV_RGB(0,255,0),8.0);
                         circle(Result_RGB, Point(cogpt.x+r0.x,cogpt.y+r0.y), 10 ,Scalar(255, 0, 0), CV_FILLED);//重心
                         //circle(frame, Point(PreviousCogpt.x+r0.x,PreviousCogpt.y+r0.y), 10 ,Scalar(255, 255, 0), CV_FILLED);//重心
                         model=drawButton(Result_RGB,PreviousCogpt,Point(cogpt.x+r0.x,cogpt.y+r0.y),right,left,up,down);
                    }
					 if (model==Right)
					{
					 putText(Result_RGB,"Right",up,FONT_HERSHEY_PLAIN,5.0,CV_RGB(0,255,180),5.0);
					 }
					 else if(model==Left)
					 {
						 putText(Result_RGB,"Left",up,FONT_HERSHEY_PLAIN,5.0,CV_RGB(0,255,180),5.0);
					 }
					 else if(model==Up)
					 {
						  putText(Result_RGB,"Up",up,FONT_HERSHEY_PLAIN,5.0,CV_RGB(0,255,180),5.0);
					 }
					 else if(model==Down)
					 {
						  putText(Result_RGB,"Down",up,FONT_HERSHEY_PLAIN,5.0,CV_RGB(0,255,180),5.0);
					 }

            }
                    Area.clear();

                }
			
}
void HangGustureControl::showwarningmsg(QString MSG)
{
   QMessageBox::warning(this,tr("Warning"),MSG);
}
HangGustureControl::~HangGustureControl()
{
    delete ui;
}
