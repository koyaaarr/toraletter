#include <iostream>

#include <opencv2/opencv.hpp> // �C���N���[�h�t�@�C���w��

using namespace cv; // ���O��Ԃ̎w��

int main()
{
	//width220, height150�̉摜���쐬
	Mat src = Mat::zeros(150, 220, CV_8UC3);

	//�ԐF�ŉ摜��Hello World��`��
	putText(src, "Hello World", Point(5, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 200), 2, CV_AA);

	//�ΐF�ŉ摜�ɐ���`��
	line(src, Point(190, 25), Point(190, 45), Scalar(0, 200, 0), 3);

	//�v�f�𒼐ڑ��삵�摜�ɓ_��`��
	for (int x = 188; x < 192; x++) {
		for (int y = 53; y < 57; y++) { // y���W
			for (int i = 0; i < 2; i++) { // i < 3�ɂ����BGR���ׂĂ̗v�f��200�ɂ���
				src.at<uchar>(Point(x * 3 + i, y)) = saturate_cast<uchar>(200);
			}
		}
	}

	//�摜��\��
	imshow("", src);

	//�E�C���h�E�̕\������(0�̓L�[���������܂ŕ��Ȃ�)
	waitKey(0);

	return 0;
}