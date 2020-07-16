#include <iostream>
#include <opencv2/opencv.hpp>

//using namespace cv;

int main(int, char**)
{
	cv::VideoCapture cap(0); // デフォルトカメラをオープン
	if (!cap.isOpened())  // 成功したかどうかをチェック
		return -1;

	cv::Mat input_image;
	cv::namedWindow("window1", 1);
	for (;;)
	{
		cv::Mat frame;
		cap >> frame; // カメラから新しいフレームを取得
		input_image = frame;      //matのコピーは普通に=で結べば良いみたい．
		imshow("window1", input_image);
		//if (cv::waitKey(30) >= 0) break;

		int key = cv::waitKey(1);
		if (key == 113)//qボタンが押されたとき
		{
			break;//whileループから抜ける．
		}
		if (key == 115)//sが押されたとき
		{
			std::cout << "take photo" << std::endl;
			//フレーム画像を保存する．
			imwrite("imd.png", input_image);
		}
	}
	// VideoCapture デストラクタにより，カメラは自動的に終了処理されます
	return 0;
}