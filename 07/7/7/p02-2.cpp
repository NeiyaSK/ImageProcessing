// p02-2 : �摜�t�@�C����ǂݍ���ŕ\������
/*
#include <stdio.h>
#include <opencv/highgui.h>

void main()
{
    IplImage* img;
    char filename[] = "Mandrill.bmp";

    // �摜�f�[�^�̓ǂݍ���
    if ((img = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED)) == NULL) {
        printf("�摜�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B\n");
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