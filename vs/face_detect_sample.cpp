//
//  face_detect_sample.cpp
//  OpenCV_test
//
//  Created by rk on 2014/07/29.
//  Copyright (c) 2014年 rk. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**)
{
    cv::VideoCapture cap(0); // デフォルトカメラをオープン
    if(!cap.isOpened())  // 成功したかどうかをチェック
        return -1;
    cv::namedWindow("window1",1);
    
    // 分類器の読み込み
    std::string cascadeName = "C:\\Users\\rk\\Documents\\codes\\hitachi_hackathon\\haarcascade_frontalface_default.xml";
    cv::CascadeClassifier cascade;
    if(!cascade.load(cascadeName))
    {
        return -1;
    }
    
    std::vector<cv::Rect> faces;
    
    while(1)
    {
        cv::Mat frame;
        cv::Mat input_image;
        cv::Mat output_image;
        cap >> frame; // カメラから新しいフレームを取得
        cvtColor(frame, input_image, CV_BGR2GRAY);//顔検出はグレーでok
        cv::equalizeHist( input_image, input_image);
        output_image=frame.clone();     //outputはカラーで．
        
        //(画像,出力短形,縮小スケール,最低短形数,フラグ？,最小短形)
        cascade.detectMultiScale(input_image, faces,
                                 1.3, 2,
                                 CV_HAAR_SCALE_IMAGE
                                 ,
                                 cv::Size(50, 50));
        
        // 結果の描画
        std::vector<cv::Rect>::const_iterator r = faces.begin();
        for(; r != faces.end(); ++r) {
            cv::Point center;
            int radius;
            center.x = cv::saturate_cast<int>((r->x + r->width*0.5));
            center.y = cv::saturate_cast<int>((r->y + r->height*0.5));
            radius = cv::saturate_cast<int>((r->width + r->height)*0.25);
            cv::circle( output_image, center, radius, cv::Scalar(80,80,255), 3, 8, 0 );
            //printf("faceID%d,x=%d,y=%d,width=%d,height=%d\n",r,r->x,r->y,r->width,r->height);
            //cv::rectangle(output_image, r.tl(), faces.br(), cv::Scalar(100, 100, 200), 2, CV_AA);

        }
        //鏡にするため反転させる
        flip(output_image,output_image,1);
        imshow("window1", output_image);
        
        if(cv::waitKey(30) >= 0) break;
        
    }
    // VideoCapture デストラクタにより，カメラは自動的に終了処理されます
    return 0;
}