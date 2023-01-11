// No.10-03 : 疑似カラー画像変換

#include <stdio.h>
#include <opencv/highgui.h>

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

// グレイスケール値 g から、疑似カラーの R 値を求める
unsigned char gray2pseudoR(unsigned char g) {
	unsigned char ret = 0;
	// ここを実装
	if (g <= 96)
		ret = 0;
	else if (g <= 160)
		ret = 255.0 / (160 - 96) * (g - 96);
	else if (g <= 224)
		ret = 255;
	else
		ret = (128.0 - 255.0) / (255 - 224) * (g -255) - 128;

	return ret;
}

// グレイスケール値 g から、疑似カラーの G 値を求める
unsigned char gray2pseudoG(unsigned char g) {
	unsigned char ret = 0;
	// ここを実装
	if (g <= 32)
		ret = 0;
	else if (g <= 96)
		ret = 255.0 / (96 - 32) * (g - 32);
	else if (g <= 160)
		ret = 255;
	else if (g <= 224)
		ret = -255.0 / (224 - 160) * (g - 224);
	else
		ret = 0;

	return ret;
}

// グレイスケール値 g から、疑似カラーの B 値を求める
unsigned char gray2pseudoB(unsigned char g) {
	unsigned char ret = 0;
	// ここを実装
	if (g <= 32)
		ret = (255.0 - 128.0) / 32 * g + 128;
	else if (g <= 96)
		ret = 255;
	else if (g <= 160)
		ret = -255.0 / (160 - 96) * (g - 160);
	else
		ret = 0;
	
	return ret;
}

// グレイスケール画像を疑似カラー化
void gray2pseudoIm(IplImage* pseudo, IplImage* gray) {
	unsigned char g;
	for (int y = 0; y < gray->height; y++) {
		for (int x = 0; x < gray->width; x++) {
			g = (unsigned char)gray->imageData[gray->widthStep * y + x];
			pseudo->imageData[pseudo->widthStep * y + x * 3 + 2] = gray2pseudoR(g); // R
			pseudo->imageData[pseudo->widthStep * y + x * 3 + 1] = gray2pseudoG(g); // G
			pseudo->imageData[pseudo->widthStep * y + x * 3 + 0] = gray2pseudoB(g); // B
		}
	}
}

void main()
{
	IplImage* img;
	IplImage* gray;
	IplImage* pseudo;

	char filename[] = "C:/Users/hotar/Documents/Git/ImageProcessing/10/Gray.bmp";
	//char filename[] = "Gray.bmp";

	// 画像データの読み込み
	if ((img = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED)) == NULL) {
		printf("画像ファイルの読み込みに失敗しました。¥n");
		return;
	}

	// 読み込んだ画像と同じサイズのグレイスケール画像(nChannels=1)を生成
	gray = cvCreateImage(cvSize(img->width, img->height), img->depth, 1);
	// 読み込んだ画像と同じサイズのカラー画像(nChannels=3)を生成
	pseudo = cvCreateImage(cvSize(img->width, img->height), img->depth, 3);
	cvNamedWindow("Original");
	cvShowImage("Original", img);
	if (img->nChannels == 3) {
		// カラー画像だった場合、グレイスケール化した画像を表示
		bgr2gray(gray, img); // グレイスケール化
		cvNamedWindow("Grayscale");
		cvShowImage("Grayscale", gray);
	}
	else if (img->nChannels == 1) {
		// グレイスケール画像だった場合はは、img_gray に元画像をコピーする
		cvCopy(img, gray);
	}

	// ここまでで、カラー画像であればグレイスケール化したものが、
	// もとからグレイスケール画像であれば、それをコピーしたものが、
	// gray に入っている状態になる。
	gray2pseudoIm(pseudo, gray); // グレイスケール画像を疑似カラー化

	cvNamedWindow("Pseudo Color");
	cvShowImage("Pseudo Color", pseudo);
	cvWaitKey(0);
	cvDestroyAllWindows();
	cvReleaseImage(&gray);
	cvReleaseImage(&img);
	return;
}
