// No.12 : �ߖT���Z�ɂ��摜����(�֊s���o�A�N�s��)
//
#include <stdio.h>
#include <opencv/highgui.h>

// �t�B���^�W�����̃t�B���^�̃p�����[�^��ێ�����\����
typedef struct {
    int size;           // �t�B���^�̑傫���B�e�L�X�g�ł����Ƃ���� w
    int widthStep;       // imageData[] �Ɠ��l�̕��@�ŌW���z��ɃA�N�Z�X���o����悤�ɂ��邽�߂̕ϐ�
    double* weight;     // �W���̔z�񂪓���
    double sigma;       // �K�E�V�A���t�B���^�p(��)
    char stretch;       // �ŏ��l=0, �ő�l=255 �ɂȂ�悤�ɕϊ����邩�ǂ��� (0:�ϊ����Ȃ� / 0�ȊO:�ϊ�����)
} Operator;

// �v���g�^�C�v�錾
IplImage* subImage(IplImage* subImg, IplImage* img, int x, int y, int w, int h);
double linearFilter(IplImage* subImg, int ch, Operator* ope);  // No.11 ����A�Ԃ�l�̌^��ύX
unsigned char clip(double v);
void filterImageDbl(IplImage* img1, IplImage* img2, Operator ope);
void makeXDiffOpe(Operator* ope);
void makeYDiffOpe(Operator* ope);
void makeXPrewittOpe(Operator* ope);
void makeYPrewittOpe(Operator* ope);
void makeXSobelOpe(Operator* ope);
void makeYSobelOpe(Operator* ope);
void makeLaplacianOpe(Operator* ope);
void makeSharpenOpe(Operator* ope);
void showWeight(Operator* ope);




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



// ��ݍ��ݐϕ����s�� (�J���[�^�O���C�X�P�[�����Ή��̂��߁Ach ���w��B(BGR�̃`���l�����ɏ�������))
// ���O���C�X�P�[���摜(nChannel=1) �̏ꍇ�́Ach �͏��0
// �q���g: (x,y)�̈ʒu�̃t�B���^�W���́A�u�@ope->weight[y * ope->widthStep + x]�@�v �Ƃ��ăA�N�Z�X�ł���
double linearFilter(IplImage* subImg, int ch, Operator* ope) {
    double sum = 0;

    for (int y = 0; y < subImg->height; y++) {
        for (int x = 0; x < subImg->width; x++) {
            // ���������!! �E�E�E�͖̂����ɂ��܂����B
            sum += (unsigned char)subImg->imageData[y * subImg->widthStep + subImg->nChannels * x + ch] * ope->weight[y * ope->widthStep + x];
        }
    }
    return sum;
}



unsigned char clip(double v) {
    return (v > 255.0) ? 255 : (v < 0.0) ? 0 : v;
}



// img1 �� ope �Őݒ肵���t�B���^�����������̂� img2 �Ƃ��ďo��
// �����v�Z�� double �ōs���A�s�N�Z���l�͈̔͂�ch���� �ŏ��l0, �ő�l255�ƂȂ�悤�����L�΂�(���J���[�摜�̏ꍇ�F���ς��ꍇ����)
void filterImageDbl(IplImage* img1, IplImage* img2, Operator ope) {

    IplImage* buff = cvCreateImage(cvSize(ope.size * 2 + 1, ope.size * 2 + 1), img1->depth, img1->nChannels);



    if (ope.stretch) { // 0-255 �̒l�ɕϊ�����ꍇ
        double* tmp = (double*)malloc(sizeof(double) * img2->width * img2->height * img2->nChannels);
        double v;

        double* minV = (double*)malloc(sizeof(double) * img2->nChannels);
        double* maxV = (double*)malloc(sizeof(double) * img2->nChannels);
        for (int ch = 0; ch < img2->nChannels; ch++) {
            minV[ch] = DBL_MAX;  // ��肤��ő�l�ŏ�����
            maxV[ch] = DBL_MIN;  // ��肤��ŏ��l�ŏ�����
        }

        // �������� double �Ōv�Z���Ach���Ƃ̍ő�l�ƍŏ��l�������ɋ��߂�
        for (int y = ope.size; y < img1->height - ope.size - 1; y++) {
            for (int x = ope.size; x < img1->width - ope.size - 1; x++) {
                for (int ch = 0; ch < img2->nChannels; ch++) {    // �O���C�X�P�[���^�J���[���Ή��̂��߂̃��[�v
                    v = linearFilter(subImage(buff, img1, x - ope.size, y - ope.size, ope.size * 2 + 1, ope.size * 2 + 1), ch, &ope); // ��������double�Ōv�Z
                    tmp[y * img2->widthStep + x * img2->nChannels + ch] = v;
                    minV[ch] = (minV[ch] > v) ? v : minV[ch];
                    maxV[ch] = (maxV[ch] < v) ? v : maxV[ch];
                }
            }
        }

        // ch���ɁA�ő�l=255�A�ŏ��l=0�A�ɂȂ�悤�ɕϊ����āAimg2 �ɑ��
        for (int ch = 0; ch < img2->nChannels; ch++) {
            for (int y = 0; y < img2->height; y++) {
                for (int x = 0; x < img2->width; x++) {
                    img2->imageData[y * img2->widthStep + x * img2->nChannels + ch] = (unsigned char)((tmp[y * (img2->width * img2->nChannels) + x * img2->nChannels + ch] - minV[ch]) / (maxV[ch] - minV[ch]) * 255);
                }
            }
        }

        // �ϊ��O�̍ő�l�A�ŏ��l��ch���Ƃɕ\��
        for (int ch = 0; ch < img2->nChannels; ch++)
            printf("\tMinV[%d] = %f", ch, minV[ch]);
        printf("\n");
        for (int ch = 0; ch < img2->nChannels; ch++)
            printf("\tMaxV[%d] = %f", ch, maxV[ch]);
    }
    else { // �t�B���^�W���̍��v�� 1.0 �̏ꍇ�Ȃǂ͂��ꂾ���ŗǂ�
        for (int y = ope.size; y < img1->height - ope.size - 1; y++) {
            for (int x = ope.size; x < img1->width - ope.size - 1; x++) {
                for (int ch = 0; ch < img2->nChannels; ch++) {    // �O���C�X�P�[���^�J���[���Ή��̂��߂̃��[�v
                    img2->imageData[y * img2->widthStep + x * img2->nChannels + ch] = clip(linearFilter(subImage(buff, img1, x - ope.size, y - ope.size, ope.size * 2 + 1, ope.size * 2 + 1), ch, &ope));
                }
            }
        }
    }
}



// x�����̈ꎟ�����t�B���^�̌W������� (������Q�l�ɁE�E�E!!)
void makeXDiffOpe(Operator* ope) {
    ope->size = 1;     // ����́@ope->size = 1 �Œ�Ƃ��Ă悢
    ope->widthStep = ope->size * 2 + 1;
    free(ope->weight);
    ope->weight = (double*)malloc(sizeof(double) * ope->widthStep * ope->widthStep);
    ope->stretch = 1;  // �ϊ����K�v

    // ----
    ope->weight[0] = 0;    ope->weight[1] = 0;    ope->weight[2] = 0;
    ope->weight[3] = 0;    ope->weight[4] = -1;    ope->weight[5] = 1;
    ope->weight[6] = 0;    ope->weight[7] = 0;    ope->weight[8] = 0;
}


// y�����̈ꎟ�����t�B���^�̌W�������
void makeYDiffOpe(Operator* ope) {
    // �y�������쐬�z
    ope->size = 1;
    ope->widthStep = ope->size * 2 + 1;
    free(ope->weight);
    ope->weight = (double*)malloc(sizeof(double) * ope->widthStep * ope->widthStep);
    ope->stretch = 1;

    ope->weight[0] = 0; ope->weight[1] = 0;     ope->weight[2] = 0;
    ope->weight[3] = 0; ope->weight[4] = -1;    ope->weight[5] = 0;
    ope->weight[6] = 0; ope->weight[7] = 1;     ope->weight[8] = 0;
}

// x�����Ɉꎟ�������� Prewitt �t�B���^�̌W�������
void makeXPrewittOpe(Operator* ope) {
    // �y�������쐬�z
    ope->size = 1;
    ope->widthStep = ope->size * 2 + 1;
    free(ope->weight);
    ope->weight = (double*)malloc(sizeof(double) * ope->widthStep * ope->widthStep);
    ope->stretch = 1;

    ope->weight[0] = -1;    ope->weight[1] = 0; ope->weight[2] = 1;
    ope->weight[3] = -1;    ope->weight[4] = 0; ope->weight[5] = 1;
    ope->weight[6] = -1;    ope->weight[7] = 0; ope->weight[8] = 1;
}

// y�����Ɉꎟ�������� Prewitt �t�B���^�̌W�������
void makeYPrewittOpe(Operator * ope) {
    // �y�������쐬�z
    ope->size = 1;
    ope->widthStep = ope->size * 2 + 1;
    free(ope->weight);
    ope->weight = (double*)malloc(sizeof(double) * ope->widthStep * ope->widthStep);
    ope->stretch = 1;

    ope->weight[0] = -1;    ope->weight[1] = -1;    ope->weight[2] = -1;
    ope->weight[3] = 0;     ope->weight[4] = 0;      ope->weight[5] = 0;
    ope->weight[6] = 1;     ope->weight[7] = 1;      ope->weight[8] = 1;
}

// x�����Ɉꎟ�������� Sobel �t�B���^�̌W�������
void makeXSobelOpe(Operator* ope) {
    // �y�������쐬�z
    ope->size = 1;
    ope->widthStep = ope->size * 2 + 1;
    free(ope->weight);
    ope->weight = (double*)malloc(sizeof(double) * ope->widthStep * ope->widthStep);
    ope->stretch = 1;

    ope->weight[0] = -1;    ope->weight[1] = 0;    ope->weight[2] = 1;
    ope->weight[3] = -2;     ope->weight[4] = 0;      ope->weight[5] = 2;
    ope->weight[6] = -1;     ope->weight[7] = 0;      ope->weight[8] = 1;
}

// y�����Ɉꎟ�������� Sobel �t�B���^�̌W�������
void makeYSobelOpe(Operator* ope) {
    // �y�������쐬�z
    ope->size = 1;
    ope->widthStep = ope->size * 2 + 1;
    free(ope->weight);
    ope->weight = (double*)malloc(sizeof(double) * ope->widthStep * ope->widthStep);
    ope->stretch = 1;

    ope->weight[0] = -1;    ope->weight[1] = -2;    ope->weight[2] = -1;
    ope->weight[3] = 0;     ope->weight[4] = 0;      ope->weight[5] = 0;
    ope->weight[6] = 1;     ope->weight[7] = 2;      ope->weight[8] = 1;
}


// 4�ߖT�̃��v���V�A���t�B���^�̌W�������
void makeLaplacianOpe(Operator* ope) {
    // �y�������쐬�z
    ope->size = 1;
    ope->widthStep = ope->size * 2 + 1;
    free(ope->weight);
    ope->weight = (double*)malloc(sizeof(double) * ope->widthStep * ope->widthStep);
    ope->stretch = 1;

    ope->weight[0] = 0;    ope->weight[1] = 1;    ope->weight[2] = 0;
    ope->weight[3] = 1;     ope->weight[4] = -4;      ope->weight[5] = 1;
    ope->weight[6] = 0;     ope->weight[7] = 1;      ope->weight[8] = 0;
}


// �N�s���t�B���^�̌W�������
void makeSharpenOpe(Operator* ope) {
    ope->size = 1;     // ����́@ope->sie = 1 �Œ�Ƃ��Ă悢
    ope->widthStep = ope->size * 2 + 1;
    free(ope->weight);
    ope->weight = (double*)malloc(sizeof(double) * ope->widthStep * ope->widthStep);
    ope->stretch = 0; // �t�B���^�W���̍��v�� 1.0 �ɂȂ�t�B���^�̏ꍇ�́A�ϊ��s�v

    // �y�������쐬�z
    ope->weight[0] = 0;    ope->weight[1] = -1;    ope->weight[2] = 0;
    ope->weight[3] = -1;     ope->weight[4] = 5;      ope->weight[5] = -1;
    ope->weight[6] = 0;     ope->weight[7] = 1;      ope->weight[8] = 0;
}



// �t�B���^�W��(weight)��\������
void showWeight(Operator* ope) {
    printf("<<Operator>>\n");
    for (int y = 0; y < ope->widthStep; y++) {
        for (int x = 0; x < ope->widthStep; x++) {
            printf("[%01.4f] ", ope->weight[y * ope->widthStep + x]);
        }
        printf("\n");
    }
}


void main(int argc, char* argv[])
{
    IplImage* img1;
    IplImage* img2;
    Operator ope;
    ope.weight = NULL;  // NULL�ŏ����� (make????Ope() ���� free() �����̂�)

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
    }
    strcpy_s(fn, 256, argv[1]);
    */

    char fn[] = "C:/Users/hotar/Documents/Git/ImageProcessing/12/SampleImage_12-20230119/Photo/Lenna.bmp"; // Drag&Drop�ŏ�������ꍇ�́@�A�������R�����g�A�E�g����



    // �摜�f�[�^�̓ǂݍ���
    if ((img1 = cvLoadImage(fn, CV_LOAD_IMAGE_UNCHANGED)) == NULL) {   // �ǂݍ��񂾉摜�̓J���[�̏ꍇ���A�O���C�X�P�[���摜�̏ꍇ������
        printf("�摜�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B\n");
        return;
    }
    // �ǂݍ��񂾉摜�̕\��
    cvNamedWindow("Original");
    cvShowImage("Original", img1);
    printf("File Name = %s\n", fn);

    img2 = cvCreateImage(cvSize(img1->width, img1->height), img1->depth, img1->nChannels);   // �ǂݍ��񂾉摜�Ɠ����傫���̉摜�𐶐�;

    // -------------------------------------------------------------
    cvSetZero(img2);   // 0(��)�ŏ��������Ă���

    makeXDiffOpe(&ope);
    showWeight(&ope);             // �쐬�����t�B���^�W����\��

    filterImageDbl(img1, img2, ope);
    cvNamedWindow("XDiff");
    cvShowImage("XDiff", img2);
    printf("\n");


    // -------------------------------------------------------------
    // -------------------------------------------------------------
    // -------------------------------------------------------------
    // -------------------------------------------------------------
    // ������ make???Ope() ���Ăяo���āA���ʂ�\������R�[�h����
    // �y�������쐬�z
    // -------------------------------------------------------------
    // -------------------------------------------------------------
    // -------------------------------------------------------------


    // -------------------------------------------------------------
    cvSetZero(img2);   // 0(��)�ŏ��������Ă���

    makeLaplacianOpe(&ope);       // �����Ń��v���V�A���t�B���^�p�̌W�����̃p�����[�^���쐬�B
    showWeight(&ope);             // �쐬�����t�B���^�W����\��

    filterImageDbl(img1, img2, ope);
    cvNamedWindow("Laplacian");
    cvShowImage("Laplacian", img2);
    printf("\n");

    // -------------------------------------------------------------
    cvSetZero(img2);   // ��U����

    makeSharpenOpe(&ope);        // �����őN�s���t�B���^�p�̌W�����̃p�����[�^���쐬�B
    showWeight(&ope);            // �쐬�����t�B���^�W����\��

    filterImageDbl(img1, img2, ope);
    cvNamedWindow("Sharpen");
    cvShowImage("Sharpen", img2);



    // -------------------------------------------------------------
    free(ope.weight);
    cvWaitKey(0);
    cvDestroyAllWindows();
}
