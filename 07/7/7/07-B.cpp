// �ۑ�No.07-B
/*
#include <stdio.h>
#include <opencv/highgui.h>

void main()
{
    IplImage* img;
    char filename[] = "C:/Users/hotar/Downloads/photo.jpg";

    // �摜�f�[�^�̓ǂݍ���
    if ((img = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED)) == NULL) {
        printf("�摜�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B\n");
        return;
    }

    cvNamedWindow("Image");
    cvShowImage("Image", img);

    printf("nChannels = %d\n", img->nChannels);


    // �`�`�J���[�摜��\������Ƃ���܂ł� p02-2.cpp �Ɠ����`�`

    if (img->nChannels == 3) {
        printf("---Color Image\n");
    }
    else if (img->nChannels == 1) {
        printf("---Grayscale Image\n");
        return;  // ���������ǉ� (�J���[�摜����Ȃ�������I��)
    }

    // B�`���l����256�� ----------------
    IplImage* img2;
    IplImage* img3;
    IplImage* img4;

    img2 = cvCreateImage(cvSize(img->width, img->height), img->depth, img->nChannels);  // �ǂݍ��񂾉摜�Ɠ����T�C�Y�̉摜�𐶐�
    img3 = cvCreateImage(cvSize(img->width, img->height), img->depth, img->nChannels);
    img4 = cvCreateImage(cvSize(img->width, img->height), img->depth, img->nChannels);

    cvCopy(img, img2);// ���摜���R�s�[
    cvCopy(img, img3);
    cvCopy(img, img4);

    for (int y = 0; y < img2->height; y++) {
        for (int x = 0; x < img2->width; x++) {
            img2->imageData[img2->widthStep * y + x * 3 + 1] = 0;
            img2->imageData[img2->widthStep * y + x * 3 + 2] = 0;
        }
    }
    for (int y = 0; y < img3->height; y++) {
        for (int x = 0; x < img3->width; x++) {
            img3->imageData[img3->widthStep * y + x * 3 + 0] = 0;
            img3->imageData[img3->widthStep * y + x * 3 + 2] = 0;
        }
    }
    for (int y = 0; y < img4->height; y++) {
        for (int x = 0; x < img4->width; x++) {
            img4->imageData[img4->widthStep * y + x * 3 + 0] = 0;
            img4->imageData[img4->widthStep * y + x * 3 + 1] = 0;
        }
    }
    cvNamedWindow("B");
    cvShowImage("B", img2);
    cvNamedWindow("G");
    cvShowImage("G", img3);
    cvNamedWindow("R");
    cvShowImage("R", img4);

    // �`�`�c��̌㏈���� p02-2.cpp �Ƃقړ��l�`�`
    cvWaitKey(0);
    cvDestroyAllWindows();
    cvReleaseImage(&img2);   // ���������ǉ�
    cvReleaseImage(&img3);
    cvReleaseImage(&img4);
    cvReleaseImage(&img);
    return;

}*/