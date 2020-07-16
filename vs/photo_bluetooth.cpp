#include <Windows.h>
#include<iostream>
#include <BluetoothAPIs.h>

#pragma comment(lib, "Bthprops")

#include <opencv2/opencv.hpp>

//using namespace cv;

int main(int, char**)
{

	BLUETOOTH_DEVICE_SEARCH_PARAMS params = { 0 };
	params.fReturnAuthenticated = TRUE;
	params.fReturnRemembered = TRUE;
	params.fReturnUnknown = TRUE;
	params.fReturnConnected = TRUE;
	params.fIssueInquiry = TRUE;
	params.cTimeoutMultiplier = 5;
	params.dwSize = sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS);

	BLUETOOTH_DEVICE_INFO info = { 0 };
	info.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);
	HBLUETOOTH_DEVICE_FIND find = BluetoothFindFirstDevice(&params, &info);

	//wchar_t b1_wchar[50];/*
	char b1_char[20] = "Bourne_Ultimatum";
	//setlocale(LC_ALL, "japanese");
	//size_t wLen = 0;
	//errno_t err = 0;
	//err = mbstowcs_s(&wLen, b1_wchar, 20, b1_char, _TRUNCATE);*/


	cv::VideoCapture cap(0); // デフォルトカメラをオープン
	if (!cap.isOpened())  // 成功したかどうかをチェック
		return -1;

	cv::Mat input_image;
	cv::namedWindow("window1", 1);
	for(;;)
	{
		cv::Mat frame;
		cap >> frame; // カメラから新しいフレームを取得
		input_image = frame;      //matのコピーは普通に=で結べば良いみたい．
		imshow("window1", input_image);

		if (find) {
			do {
				std::cout << info.szName << std::endl;
				//if (info.szName == b1_wchar) {
					//std::cout << "yes" << std::endl;
					//cv::imwrite("C:/Users/rk/Pictures/img.png", frame);
				//}
			} while (BluetoothFindNextDevice(find, &info));

			//BluetoothFindDeviceClose(find);
			//break;
		}

		int key = cv::waitKey(10);
		if (key == 113)//qボタンが押されたとき
		{
			break;//whileループから抜ける．
		}
	}
	// VideoCapture デストラクタにより，カメラは自動的に終了処理されます
	return 0;
}