// No. 10-02 : 各種統計量の計算

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

void main() {
	IplImage* img;
	IplImage* gray;

	char filename[] = "C:/Users/hotar/Documents/Git/ImageProcessing/10/05_LowCnt.bmp";

	// 画像ファイルの読み込み
	if ((img = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED)) == NULL) {
		printf("画像ファイルの読み込みに失敗しました． \n");
		return;
	}
	// 読み込んだ画像と同じサイズのグレイスケール画像(nChannels=1)を作成
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
		// グレイスケール画像だった場合は，img_grayに元画像をコピーする
		cvCopy(img, gray);
	}

	// ここまでで、カラー画像であればグレイスケール化したものが、
	// もとからグレイスケール画像であれば、それをコピーしたものが、
	// gray に入っている状態になる。
	int minV = 255; // 最小値 : とりあえず最大値で初期化(より小さな値が見つかったら更新する)
	int maxV = 0; // 最大値 : とりあえず最小値で初期化(より大きな値が見つかったら更新する)
	int range = 0; // 範囲 : 未初期化なので要注意
	double mean = 0; // 平均値 : 未初期化なので要注意
	// その他計算に必要な変数をここで宣言する
	int count = 0;	// 平均の計算で使用
	double sum = 0;
	

	for (int y = 0; y < gray->height; y++) {
		for (int x = 0; x < gray->width; x++) {
			// このループを使って、各種統計量を求める
			double data = (unsigned char)gray->imageData[gray->widthStep * y + x];

			// Min
			if (data <= minV)
				minV = data;
			else
				;

			// Max
			if (data >= maxV)
				maxV = data;
			else
				;

			// Range
			range = maxV - minV;

			// Mean
			count = gray->height * gray->width;
			sum += data;
			mean = sum / count;
			//printf("sum = %f\n", sum);
			//printf("count = %d\n\n", count);
		}
	}
	// 計算結果の表示
	printf("minV = %d\n", minV);
	printf("maxV = %d\n", maxV);
	printf("range = %d\n", range);
	printf("mean = %f\n\n", mean);

	cvWaitKey(0);
	cvDestroyAllWindows();
	cvReleaseImage(&gray);
	cvReleaseImage(&img);
	return;

	return ;
}