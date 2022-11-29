// 課題No.06-A


/*
include <stdio.h>
#include <opencv/highgui.h>

void main()
{
	CvSize size;
	size.width = 200;
	size.height = 100;
	IplImage* img = cvCreateImage(size, IPL_DEPTH_8U, 1); // 1: グレイスケール画像
	cvSetZero(img); // 画像データを 0(黒) で初期化
	// ------ 灰色画像(すべての濃度値=128)の生成 ---------
	for (int y = 0; y < img->height; y++) {
		for (int x = 0; x < img->width; x++) {
			img->imageData[img->widthStep * y + x] = 128;// ピクセル値は 0～255
			// ----- 黒い縦線の生成 -----
			if (x == 50)	// x座標が50の位置に生成
			{
				img->imageData[img->widthStep * y + x] = 0;
			}
			else
				;

		}
	}
	cvNamedWindow("Gray");
	cvShowImage("Gray", img);
	cvSaveImage("Gray.bmp", img); // Bitmap画像として保存
	// ---------------------------
	cvWaitKey(0); // 何かキーが押されるまで待つ
	cvDestroyAllWindows();
	cvReleaseImage(&img);
}
*/