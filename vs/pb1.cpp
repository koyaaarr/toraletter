#include <Windows.h>
#include<iostream>
#include <BluetoothAPIs.h>
#include <opencv2/opencv.hpp>

#pragma comment(lib, "Bthprops")



int main() {

	wchar_t b1_wchar[] = L"Toraletter-0001";

	BLUETOOTH_DEVICE_SEARCH_PARAMS params = { 0 };
	params.fReturnAuthenticated = TRUE;
	params.fReturnRemembered = TRUE;
	params.fReturnUnknown = TRUE;
	params.fReturnConnected = TRUE;
	params.fIssueInquiry = TRUE;
	params.cTimeoutMultiplier = 5;
	params.dwSize = sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS);

	BLUETOOTH_DEVICE_INFO info = { 0 };

	int photo_num = 1;


	cv::VideoCapture cap(1); // デフォルトカメラをオープン
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

		

		

		
		info.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);
		HBLUETOOTH_DEVICE_FIND find = BluetoothFindFirstDevice(&params, &info);


		if (find) {
			do {
				if (wcscmp(info.szName, b1_wchar) == 0) {
					std::wcout << info.szName;
					std::cout << ":登録済みユーザです!" << std::endl;
					std::string photo_name = std::to_string(photo_num) + ".jpg";
					cv::imwrite(photo_name, frame);
					std::cout << "写真を撮影しました:" << photo_name << std::endl;
					photo_num++;
				}
				else {
					std::wcout << info.szName << std::endl;
				}
			} while (BluetoothFindNextDevice(find, &info));
		}

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