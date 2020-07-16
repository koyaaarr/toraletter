//
//  camera_test.cpp
//  OpenCV_test
//
//  Created by rk on 2014/07/27.
//  Copyright (c) 2014年 rk. All rights reserved.
//

#include "headers.h"

using namespace std;
using namespace cv;



int main()
{
    /* 画像変数 */
    Mat src, gray, bin;

    /* 動画ファイルの指定 */
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        fprintf(stderr, "cannot open\n");
        exit(1);
    }

    
    while(1)
    {    
        /* キャプチャ */
        cap >> src;
        
		//グレースケール変換
		cvtColor(src, gray, CV_BGR2GRAY);
        
        //2値化
		threshold(gray, bin, 100, 255, cv::THRESH_BINARY|cv::THRESH_OTSU);
        
		//収縮・膨張
//		erode(bin, bin, cv::Mat(), cv::Point(-1,-1), 3);
//		erode(bin, bin, cv::Mat(), cv::Point(-1,-1), 3);
//		dilate(bin, bin, cv::Mat(), cv::Point(-1,-1), 1);
//		dilate(bin, bin, cv::Mat(), cv::Point(-1,-1), 1);
        
        /* 輪郭検出 */
        vector< vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::findContours (bin, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
		cv::drawContours (src, contours, -1, cv::Scalar(100), 2, 8);
        
        /* 描画 */
        imshow("src", src);
//      imshow("gray", gray);
//      imshow("bin", bin);

        
        /* キー入力があれば終了．なければ 30 ms 待って継続 */
        if (waitKey(2) > 0)
        {
                break;
        }
    
    }
    
    return 0;
}