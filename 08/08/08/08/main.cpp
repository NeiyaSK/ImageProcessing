// No.08 : カラー画像/グレイスケール画像を二値化する

#include <stdio.h>
#include <opencv/highgui.h>

// グレイスケール画像を二値化
void gray2bin(IplImage* bin, IplImage* gray, char th)
{

}

// カラー画像をグレイスケール化
void bgr2gray(IplImage* gray, IplImage* bgr)
{

}

void main()
{
	// 前半はp03と同じ
	IplImage* img_bin;
	char th = 127;	// 閾値

	printf("nChannels = %d\n", img->nChannels);
}