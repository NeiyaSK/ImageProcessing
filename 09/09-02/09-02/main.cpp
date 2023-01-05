// No.09-02：濃度変換（γ変換）

#include<stdio.h>
#include<opencv/highgui.h>
#include<math.h>

// double型のピクセル値を，unsigned char型で返す．０未満の値は０に，２５５以上の値は２５５にクリップする
unsigned char clip(double v) {
	return (v > 255) ? 255 : (v < 0) ? 0 : (unsigned char)v;
}

// ガンマ変換(Gamma Stretch)
// dst: 変換結果の画像
// src: 変換元の画像
// dst = 255 * (src/255)^(1/g)
void gamma(IplImage* dst, IplImage* src, double g) {
	double k, v;
	for (int y = 0; y < src->height; y++) {
		for (int x = 0; x < src->width; x++) {
			for (int ch = 0; ch <src->nChannels; ch++) {
				k= (unsigned char)src->imageData[src->widthStep * y + x * src->nChannels + ch];
				v = 255 * pow(k / 255, 1/g);
				dst->imageData[dst->widthStep * y + x * dst->nChannels + ch] = clip(v);
			}
		}
	}
}

void main() {
	IplImage* src;
	IplImage* dst;
	double g = 1.5; // 係数(ここを調整)
	char filename[] = "C:/Users/hotar/Documents/Git/ImageProcessing/SampleImage/color/Mandrill.bmp";
	// 画像データの読み込み
	if ((src = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED)) == NULL) {
		printf("画像ファイルの読み込みに失敗しました。\n");
		return;
	}
	printf("%s\nChannels = %d\n\ngamma = %f\n", filename, src->nChannels, g);

	// 読み込んだ画像と同じサイズ, 同じチャンネル数(nChannels)の画像を生成
	dst = cvCreateImage(cvSize(src->width, src->height), src->depth, src->nChannels);
	cvNamedWindow("Source");
	cvShowImage("Source", src);
	gamma(dst, src, g);
	cvNamedWindow("Destination");
	cvShowImage("Destination", dst);

	cvWaitKey(0);
	cvDestroyAllWindows();
	cvReleaseImage(&dst);
	cvReleaseImage(&src);
	return;
}