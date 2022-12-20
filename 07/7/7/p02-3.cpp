/*

// p02-3 : 読み込んだ画像のGチャネルを0にした画像を表示
#include <stdio.h>
#include <opencv/highgui.h>

void main()
{
    IplImage* img;
    char filename[] = "C:/Users/hotar/Downloads/photo.jpg";

    // 画像データの読み込み
    if ((img = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED)) == NULL) {
        printf("画像ファイルの読み込みに失敗しました。\n");
        return;
    }

    cvNamedWindow("Image");
    cvShowImage("Image", img);

    printf("nChannels = %d\n", img->nChannels);


    // ～～カラー画像を表示するところまでは p02-2.cpp と同じ～～

    if (img->nChannels == 3) {
        printf("---Color Image\n");
    }
    else if (img->nChannels == 1) {
        printf("---Grayscale Image\n");
        return;  // ここだけ追加 (カラー画像じゃなかったら終了)
    }

    // Gチャネルを0に ----------------
    IplImage* img2;
    img2 = cvCreateImage(cvSize(img->width, img->height), img->depth, img->nChannels);  // 読み込んだ画像と同じサイズの画像を生成
    cvCopy(img, img2);            // 元画像をコピー
    for (int y = 0; y < img2->height; y++) {
        for (int x = 0; x < img2->width; x++) {
            img2->imageData[img2->widthStep * y + x * 3 + 0] = 0;
        }
    }
    cvNamedWindow("G=0");
    cvShowImage("G=0", img2);

    // ～～残りの後処理は p02-2.cpp とほぼ同様～～
    cvWaitKey(0);
    cvDestroyAllWindows();
    cvReleaseImage(&img2);   // ここだけ追加
    cvReleaseImage(&img);
    return;

}*/