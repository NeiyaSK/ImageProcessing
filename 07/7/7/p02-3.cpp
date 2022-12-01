/*

// p02-3 : �ǂݍ��񂾉摜��G�`���l����0�ɂ����摜��\��
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

    // G�`���l����0�� ----------------
    IplImage* img2;
    img2 = cvCreateImage(cvSize(img->width, img->height), img->depth, img->nChannels);  // �ǂݍ��񂾉摜�Ɠ����T�C�Y�̉摜�𐶐�
    cvCopy(img, img2);            // ���摜���R�s�[
    for (int y = 0; y < img2->height; y++) {
        for (int x = 0; x < img2->width; x++) {
            img2->imageData[img2->widthStep * y + x * 3 + 0] = 0;
        }
    }
    cvNamedWindow("G=0");
    cvShowImage("G=0", img2);

    // �`�`�c��̌㏈���� p02-2.cpp �Ƃقړ��l�`�`
    cvWaitKey(0);
    cvDestroyAllWindows();
    cvReleaseImage(&img2);   // ���������ǉ�
    cvReleaseImage(&img);
    return;

}*/