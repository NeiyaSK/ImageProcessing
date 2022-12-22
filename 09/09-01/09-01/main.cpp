#include <stdio.h>
#include <opencv/highgui.h>

// double型のピクセル値を, unsigned char型で返す. 0未満の値は0に，255以上の値は255にクリップする
unsigned char clip(double v)
{
	return (v > 255) ? 255 : (v < 0) ? 0 : (unsigned char)v;
}

// 線形変換(Linear Stretch)
// dst: 変換結果の画像
// src: 変換元の画像
// dst = src * a + b
void linear(IplImage* dst, IplImage* src, double a, double b)
{
	double v;
	for (int y = 0; y < src->height; y++)
	{
		for (int x = 0; x < src->width; x++)
		{
			// グレイスケールカラー両方まとめて処理するためのループ
			for (int ch = 0; ch < src->nChannels; ch++)
			{
				v = (unsigned char)src->imageData[src->widthStep * y + x * src->nChannels + ch] * a + b;
				dst->imageData[dst->widthStep * y + x * dst->nChannels + ch] = clip(v);
			}
		}
	}
}

void main()
{
	IplImage* src;
	IplImage* dst;
	double a, b;	// 係数

	int mode = 5;	// この値でモードを切り替える

	char filename[] = "C:/Users/hotar/Downloads/photo.jpg";

	switch (mode)
	{
		// a, bの値をそれぞれ設定する
	case 0:		// 無変換
		a = 1.0;
		b = 0.0;
		break;
	case 1:		// ①明るく
		a = 1.0;
		b = 50.0;
		break;
	case 2:		// ②暗く
		a = 1.0;
		b = -50.0;
		break;
	case 3:		// ③コントラストを強く
		a = 5.0;
		b = 0.0;
		break;
	case 4:		// ④コントラストを弱く
		a = 0.5;
		b = 0.0;
		break;
	case 5:		// ⑤階調反転
		a = -1.0;
		b = 100.0;
		break;
	default:	// 
		printf("modeが範囲外の値です\n");
		return;
	}

	// 画像データの読み込み
	if ((src = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED)) == NULL)
	{
		printf("画像ファイルの読み込みに失敗しました．");
		return;
	}
	printf("%snnChannels = %d\n\nMode = %d\n\ta = %f\n\tb = %f\n", filename, src->nChannels, mode, a, b);

	// 読み込んだ画像と同じサイズ，同じチャンネル数（nChannels)の画像を生成
	dst = cvCreateImage(cvSize(src->width, src->height), src->depth, src->nChannels);

	cvNamedWindow("Source");
	cvShowImage("Source", src);

	linear(dst, src, a, b);

	cvNamedWindow("Destination");
	cvShowImage("Destination", dst);

	cvWaitKey(0);
	cvDestroyAllWindows();
	cvReleaseImage(&dst);
	cvReleaseImage(&src);
	return;
}