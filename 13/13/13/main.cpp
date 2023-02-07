// No.13 : ���f�B�A���t�B���^ (OPE_SIZE = 1 ==> 3x3 �T�C�Y, OPE_SIZE = 2 ==> 5x5 �T�C�Y)
//
#include <stdio.h>
#include <opencv/highgui.h>


#define OPE_SIZE 2

// �v���g�^�C�v�錾
IplImage* subImage(IplImage* subImg, IplImage* img, int x, int y, int w, int h);
unsigned char medianFilter(IplImage* subImg, int ch);
void filterImage(IplImage* img1, IplImage* img2);




// �摜�̈ꕔ��(�摜�u���b�N)��؂�o��
IplImage* subImage(IplImage* subImg, IplImage* img, int x, int y, int w, int h) {

    // ��������0�ŏ�����(img�̕��⍂���𒴂����ꍇ�̑΍�)
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



// ���f�B�A���l(�����l)�����߂� (�J���[�^�O���C�X�P�[�����Ή��̂��߁Ach ���w��B(BGR�̃`���l�����ɏ�������))
// ���O���C�X�P�[���摜(nChannel=1) �̏ꍇ�́Ach �͏��0
unsigned char medianFilter(IplImage* subImg, int ch) {
    unsigned char median = 0;
    unsigned char neighbor[(OPE_SIZE * 2 + 1) * (OPE_SIZE * 2 + 1)];
    int n = (OPE_SIZE * 2 + 1) * (OPE_SIZE * 2 + 1);
    int i = 0;
    double tmp = 0;

    // �ߖT�̃s�N�Z���l�� neighbor[] �Ɏ��W
    for (int y = 0; y < subImg->height; y++) {
        for (int x = 0; x < subImg->width; x++) {
            neighbor[i++] = (unsigned char)subImg->imageData[y * subImg->widthStep + subImg->nChannels * x + ch];
        }
    }

    // ===========================================
    // �y�������쐬!!�z
    for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
            if (neighbor[j] < neighbor[k]) {
                tmp = neighbor[j];
                neighbor[j] = neighbor[k];
                neighbor[k] = tmp;
            }
        }
    }
    median = neighbor[i / 2];
    // ===========================================


    return median;
}



void filterImage(IplImage* img1, IplImage* img2) {
    IplImage* buff = cvCreateImage(cvSize(OPE_SIZE * 2 + 1, OPE_SIZE * 2 + 1), img1->depth, img1->nChannels);

    for (int y = OPE_SIZE; y < img1->height - OPE_SIZE - 1; y++) {
        for (int x = OPE_SIZE; x < img1->width - OPE_SIZE - 1; x++) {
            for (int ch = 0; ch < img2->nChannels; ch++) {    // �O���C�X�P�[���^�J���[���Ή��̂��߂̃��[�v
                img2->imageData[y * img2->widthStep + x * img2->nChannels + ch] = medianFilter(subImage(buff, img1, x - OPE_SIZE, y - OPE_SIZE, OPE_SIZE * 2 + 1, OPE_SIZE * 2 + 1), ch);
            }
        }
    }
}


// �t�B���^���ʂ̉摜�����o��(�t�@�C��������������)
void writeFile(IplImage* img, char* imgFilename, const char* addName) {
    char filename[256];
    char* ext_p;

    strcpy_s(filename, 256, imgFilename); // �ǂݍ��񂾉摜�̃t�@�C�������R�s�[
    ext_p = strrchr(filename, '.');
    *ext_p = '\0';   // �t�@�C��������g���q������
    sprintf_s(filename, 255, "%s+%s(%dx%d).bmp", filename, addName, OPE_SIZE * 2 + 1, OPE_SIZE * 2 + 1); // �m�C�Y����t�������t�@�C�����𐶐�

    cvSaveImage(filename, img);
}




void main(int argc, char* argv[])
{
    IplImage* img1;
    IplImage* img2;

    // �t�@�C���� Drag&Drop�ŏ����ł���悤�ɂ���ɂ́A�@���̉��̈�A�̃R�����g�A�E�g���O���A
    /*
    char fn[256];

    // �N���I�v�V�����̃`�F�b�N
    printf("argc = %d\n", argc);
    for (int k = 0; k < argc; k++) {
        printf("argv[%d] = %s\n", k, argv[k]);
    }
    printf("\n\n");

    if (argc < 2) {
        printf("�t�@�C�������w�肵�Ă��������B\n");
        return;
    }s
    strcpy_s(fn, 256, argv[1]);
    */

    char fn[] = "C:/Users/hotar/Documents/Git/ImageProcessing/SampleImage/color/Parrots+WhiteNoise.bmp"; // Drag&Drop�ŏ�������ꍇ�́@�A�������R�����g�A�E�g����



    // �摜�f�[�^�̓ǂݍ���
    if ((img1 = cvLoadImage(fn, CV_LOAD_IMAGE_UNCHANGED)) == NULL) {   // �ǂݍ��񂾉摜�̓J���[�̏ꍇ���A�O���C�X�P�[���摜�̏ꍇ������
        printf("�摜�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B\n");
        return;
    }
    // �ǂݍ��񂾉摜�̕\��
    cvNamedWindow("Original");
    cvShowImage("Original", img1);
    printf("File Name = %s\n", fn);
    printf("OPE_SIZE = %d (%d x %d)\n", OPE_SIZE, OPE_SIZE * 2 + 1, OPE_SIZE * 2 + 1);

    img2 = cvCreateImage(cvSize(img1->width, img1->height), img1->depth, img1->nChannels);   // �ǂݍ��񂾉摜�Ɠ����傫���̉摜�𐶐�;

    // -------------------------------------------------------------
    cvSetZero(img2);   // 0(��)�ŏ��������Ă���

    filterImage(img1, img2);
    cvNamedWindow("Median Filter");
    cvShowImage("Median Filter", img2);

    writeFile(img2, fn, "_Median");         // �t�B���^���ʂ��摜�t�@�C���Ƃ��ďo��

    // -------------------------------------------------------------
    cvWaitKey(0);
    cvDestroyAllWindows();
}
