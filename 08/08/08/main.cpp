#include<stdio.h>
#include<opencv/highgui.h>

// カラー画像をグレイスケール化
void bgr2gray(IplImage* gray, IplImage* bgr) {
	for (int y = 0; y < gray->height; y++) {
		for (int x = 0; x < gray->width; x++) {
			int b = (unsigned char)bgr->imageData[bgr->widthStep * y + x * 3 + 0];
			int g = (unsigned char)bgr->imageData[bgr->widthStep * y + x * 3 + 1];
			int r = (unsigned char)bgr->imageData[bgr->widthStep * y + x * 3 + 2];
			gray->imageData[gray->widthStep * y + x] = 0.298912 * r + 0.586611 * g + 0.114478 * b;
		}
	}
}

// グレイスケール画像を二値化
void gray2bin(IplImage* bin, IplImage* gray, char th) {
	for (int y = 0; y < bin->height; y++) {
		for (int x = 0; x < bin->width; x++) {
			int n = (unsigned char)gray->imageData[gray->widthStep * y + x];
			if (n < 127) {
				bin->imageData[bin->widthStep * y + x] = 0;
			}
			else {
				bin->imageData[bin->widthStep * y + x] = 255;
			}
		}
	}
}

void main() {
	IplImage* img;
	IplImage* img_gray;
	IplImage* img_bin;
	char th = 127;
	char filename[] = "C:/Users/hotar/Documents/Git/ImageProcessing/SampleImage/color/Mandrill.bmp";

	 // 画像データの読み込み
	if ((img = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED)) == NULL) {
		printf("画像ファイルの読み込みに失敗しました． /n");
		return;
	}
	// 読み込んだ画像と同じサイズのグレイスケール画像(nChannels=1)を生成
	img_gray = cvCreateImage(cvSize(img->width, img->height), img->depth, 1);

	cvNamedWindow("Original");
	cvShowImage("Original", img);

	printf("nChannels = %d/n", img->nChannels);
	if (img->nChannels == 3) {
		// カラー画像だった場合，グレイスケール化した画像を表示
		printf("---Color Image\n");
		bgr2gray(img_gray, img);	// グレイスケール化

		cvNamedWindow("Grayscale");
		cvShowImage("Grayscale", img_gray);
	}
	else if (img->nChannels == 1) {
		// グレイスケール画像だった場合は，img_grayに元画像をコピーする
		printf("---Graysacle Image\n");
		cvCopy(img, img_gray);
	}

	// グレイスケール画像と同じ大きさの画像を生成 (※０，１はグレイスケール画像の０，２５５で表現)
	img_bin = cvCreateImage(cvSize(img->width, img->height), img->depth, img_gray->nChannels);
	gray2bin(img_bin, img_gray, th);

	cvNamedWindow("Binary");
	cvShowImage("Binary", img_bin);
	printf("Threshold%d\n", th);

	cvWaitKey(0);
	cvDestroyAllWindows();
	cvReleaseImage(&img);
	return;

}