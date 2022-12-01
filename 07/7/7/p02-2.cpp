// p02-2 : 画像ファイルを読み込んで表示する
/*
#include <stdio.h>
#include <opencv/highgui.h>

void main()
{
    IplImage* img;
    char filename[] = "Mandrill.bmp";

    // 画像データの読み込み
    if ((img = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED)) == NULL) {
        printf("画像ファイルの読み込みに失敗しました。\n");
        return;
    }

    cvNamedWindow("Image");
    cvShowImage("Image", img);

    printf("nChannels = %d\n", img->nChannels);
    if (img->nChannels == 3) {
        printf("---Color Image\n");
    }
    else if (img->nChannels == 1) {
        printf("---Grayscale Image\n");
    }

    cvWaitKey(0);
    cvDestroyAllWindows();
    cvReleaseImage(&img);
    return;
}
*/