#include<stdio.h>
#include<opencv/highgui.h>


// VisualStudio環境のみ：fopen()を使えるようにする
#pragma warning(disable: 4996)

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

void calc_histogram(unsigned int hist[], IplImage* gray) {
	int data = 0;
	for (int y = 0; y < gray->height; y++) {
		for (int x = 0; x < gray->width; x++) {
				data = (unsigned char)gray->imageData[gray->widthStep * y + x];
				hist[data]++;
		}
	}
}

void main() {
	IplImage* img;
	IplImage* gray;
	unsigned int hist[256] = { 0 };		// ヒストグラムを入れる

	char filename[] = "C:/Users/hotar/Documents/Git/ImageProcessing/SampleImage/color/Mandrill.bmp";
	char outputFilename[] = "Hitogram.csv";

	// 画像データの読み込み
	if ((img = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED)) == NULL) {
		printf("画像ファイルの読み込みに失敗しました．\n");
		return;
	}
	// 読み込んだ画像と同じサイズのグレイスケール画像(nChannels=1)を生成
	gray = cvCreateImage(cvSize(img->width, img->height), img->depth, 1);

	cvNamedWindow("Original");
	cvShowImage("Original", img);

	if (img->nChannels == 3) {
		// カラー画像だった場合，グレイスケール化した画像を表示
		bgr2gray(gray, img);	// グレイスケール化

		cvNamedWindow("Grayscale");
		cvShowImage("Grayscale", gray);
	}
	else if (img->nChannels == 1) {
		// グレイスケール画像だった場合には，img_gray二本画像をコピーする
		cvCopy(img, gray);
	}

	// ここまでで，カラー画像であればグレイスケール化したものが，
	// もとからグレイスケール画像であれば，それをコピーしたものが，grayに入っている状態になる．

	calc_histogram(hist, gray);		// ヒストグラムを計算

	FILE* fp = fopen(outputFilename, "w");	// 書き込み（上書き）モードでファイルオープン
	for (int i = 0; i < 256; i++) {
		printf("%d, %u\n",i, hist[i]);
		fprintf(fp, "%d, %u\n", i, hist[i]);
	}
	fclose(fp);

	cvWaitKey(0);
	cvDestroyAllWindows();
	cvReleaseImage(&gray);
	cvReleaseImage(&img);
	return;
}