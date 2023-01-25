﻿// No.11 : 近傍演算による画像処理(単純移動平均)
//
#include <stdio.h>
#include <math.h>
#include <opencv/highgui.h>
#define M_E


// フィルタ係数等のフィルタのパラメータを保持する構造体
typedef struct {
    int size;           // フィルタの大きさ。テキストでいうところの w
    int widthStep;       // imageData[] と同様の方法で係数配列にアクセスが出来るようにするための変数
    double* weight;     // 係数の配列が入る
    double sigma;       // ガウシアンフィルタ用(σ)
} Operator;

// プロトタイプ宣言
IplImage* subImage(IplImage* subImg, IplImage* img, int x, int y, int w, int h);
unsigned char linearFilter(IplImage* subImg, int ch, Operator* ope);
void filterImage(IplImage* img1, IplImage* img2, Operator ope);
void makeMovingAverageOpe(Operator* ope);
void makeGaussianOpe(Operator* ope);



// 画像の一部分(画像ブロック)を切り出す
IplImage* subImage(IplImage* subImg, IplImage* img, int x, int y, int w, int h) {

    // いったん0で初期化(imgの幅や高さを超えた場合の対策)
    cvSetZero(subImg);

    for (int i = y; i < y + h && i < img->height; i++) {
        for (int j = x; j < x + w && j < img->width; j++) {
            for (int ch = 0; ch < img->nChannels; ch++) {
                subImg->imageData[(i - y) * subImg->widthStep + (j - x) * img->nChannels + ch] = img->imageData[img->widthStep * i + j * img->nChannels + ch];
            }
        }
    }
    return subImg;
}




// 畳み込み積分を行う (カラー／グレイスケール両対応のため、ch を指定。(BGRのチャネル毎に処理する))
// ※グレイスケール画像(nChannel=1) の場合は、ch は常に0
// ヒント: (x,y)の位置のフィルタ係数は、「　ope->weight[y * ope->widthStep + x]　」 としてアクセスできる
unsigned char linearFilter(IplImage* subImg, int ch, Operator* ope) {
    double sum = 0.0;

    for (int y = 0; y < subImg->height; y++) {
        for (int x = 0; x < subImg->width; x++) {
            // ここを作る!! ・・・のは無しにしました。
            sum += (unsigned char)subImg->imageData[y * subImg->widthStep + subImg->nChannels * x + ch] * ope->weight[y * ope->widthStep + x];
        }
    }
    return sum;
}

// img1 に ope で設定したフィルタをかけたものを img2 として出力
void filterImage(IplImage* img1, IplImage* img2, Operator ope) {

    IplImage* buff = cvCreateImage(cvSize(ope.size * 2 + 1, ope.size * 2 + 1), img1->depth, img1->nChannels);

    // 線形フィルタの場合は全てここ
    for (int y = ope.size; y < img1->height - ope.size - 1; y++) {
        for (int x = ope.size; x < img1->width - ope.size - 1; x++) {
            for (int ch = 0; ch < img2->nChannels; ch++) {    // グレイスケール／カラー両対応のためのループ
                img2->imageData[y * img2->widthStep + x * img2->nChannels + ch]
                    = linearFilter(subImage(buff, img1, x - ope.size, y - ope.size, ope.size * 2 + 1, ope.size * 2 + 1), ch, &ope);
            }
        }
    }
}


// フィルタ係数(weight)を表示する
void showWeight(Operator* ope) {
    printf("<<Operator>>\n");
    for (int y = 0; y < ope->widthStep; y++) {
        for (int x = 0; x < ope->widthStep; x++) {
            printf("[%01.4f] ", ope->weight[y * ope->widthStep + x]);
        }
        printf("\n");
    }
}


// 移動平均フィルタの係数を作る【この関数を完成する(ope-weight[] の各値を設定する)】
void makeMovingAverageOpe(Operator* ope) {
    ope->widthStep = ope->size * 2 + 1;
    ope->weight = (double*)malloc(sizeof(double) * ope->widthStep * ope->widthStep);

    // この部分で、ope->weight[] を設定する。
    // なお、ope->weight[] はすぐ上のmalloc()で生成している通り、 1次元配列なので、
    // IplImage の imageData でのアクセスと同様の方法(widthStep を使う)でアクセスする

    // ----
    for (int i = 0; i < ope->size; i++) {
        ope->weight[(int)ope->widthStep + i] = 1.0 / 9.0;
    }
    // ----

    printf("MovingAverage :\n\tope.size = %d (%d x %d)\n", ope->size, ope->size * 2 + 1, ope->size * 2 + 1);
}


// ガウシアンフィルタの係数を作る【この関数を完成する(ope-weight[] の各値を設定する)】
void makeGaussianOpe(Operator* ope) {
    ope->widthStep = ope->size * 2 + 1;
    ope->weight = (double*)malloc(sizeof(double) * ope->widthStep * ope->widthStep);

    // ----
    // ここにコードを追加

    // ヒント : 以下のようなループを使うと楽(※この通りにしなくてもOK)
    int m, n;
    double s = 0, h2= 0;

    for (int y = 0; y < ope->widthStep; y++) {
        for (int x = 0; x < ope->widthStep; x++) {
            m = x - ope->size;
            n = y - ope->size;

            h2 = exp(pow(m, 2.0) + (n, 2.0) / 2 * pow(ope->sigma, 2.0));
            s += h2;
            ope->weight[y * (int)ope->widthStep + x] = h2 / s;
        }
    }
 

    // ----

    printf("Gausisian :\n\tope.size = %d (%d x %d)\n\tope.sigma=%f\n", ope->size, ope->size * 2 + 1, ope->size * 2 + 1, ope->sigma);
}




void main(int argc, char* argv[])
{
    IplImage* img1;
    IplImage* img2;
    Operator ope;

    // ファイルを Drag&Dropで処理できるようにするには、①この下の一連のコメントアウトを外し、
    /*
    char fn[256];

    // 起動オプションのチェック
    printf("argc = %d\n", argc);
    for (int k = 0; k < argc; k++) {
        printf("argv[%d] = %s\n", k, argv[k]);
    }
    printf("\n\n");

    if (argc < 2) {
        printf("ファイル名を指定してください。\n");
        return;
    }
    strcpy_s(fn, 256, argv[1]);
    */

    char fn[] = "C:/Users/hotar/Documents/Git/ImageProcessing/12/SampleImage_12-20230119/Pattern/26.png"; // Drag&Dropで処理する場合は　②ここをコメントアウトする



    // 画像データの読み込み
    if ((img1 = cvLoadImage(fn, CV_LOAD_IMAGE_UNCHANGED)) == NULL) {   // 読み込んだ画像はカラーの場合も、グレイスケール画像の場合もある
        printf("画像ファイルの読み込みに失敗しました。\n");
        return;
    }
    // 読み込んだ画像の表示
    cvNamedWindow("Original");
    cvShowImage("Original", img1);
    printf("File Name = %s\n", fn);

    img2 = cvCreateImage(cvSize(img1->width, img1->height), img1->depth, img1->nChannels);   // 読み込んだ画像と同じ大きさの画像を生成;

    // -------------------------------------------------------------
    cvSetZero(img2);   // 0(黒)で初期化しておく


    ope.size = 1;  // ここを調整 -- 単純移動平均
    makeMovingAverageOpe(&ope);   // ここで移動平均用の係数等のパラメータを作成。
    showWeight(&ope);             // 作成したフィルタ係数を表示

    filterImage(img1, img2, ope);
    cvNamedWindow("Moving Average");
    cvShowImage("Moving Average", img2);

    printf("\n");
    // -------------------------------------------------------------
    cvSetZero(img2);   // 一旦消す

    ope.size = 1;      // ここを調整(1) -- ガウシアン
    ope.sigma = 1.0;   // ここを調整(2) -- ガウシアン
    makeGaussianOpe(&ope);        // ここでガウシアンフィルタ用の係数等のパラメータを作成。
    showWeight(&ope);             // 作成したフィルタ係数を表示

    filterImage(img1, img2, ope);
    cvNamedWindow("Gaussian");
    cvShowImage("Gaussian", img2);

    cvWaitKey(0);
    cvDestroyAllWindows();
}

