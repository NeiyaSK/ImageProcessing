#include<stdio.h>
#include<opencv/highgui.h>

// �J���[�摜���O���C�X�P�[����
void bgr2gray(IplImage* gray, IplImage* bgr) {
	for (int y = 0; y < gray->height; y++) {
		for (int x = 0; x < gray->width; x++) {
			int b = (unsigned char)bgr->imageData[bgr->widthStep * y + x * 3 + 0];
			int g = (unsigned char)bgr->imageData[bgr->widthStep * y + x * 3 + 1];
			int r = (unsigned char)bgr->imageData[bgr->widthStep * y + x * 3 + 2];
			gray->imageData[gray->widthStep * y + x] = 0.298912 * r + 0.586611 * g + 0.11447 * b;
		}
	}
}

// �O���C�X�P�[���摜���l��
void gray2bin(IplImage* bin, IplImage* gray, char th) {
	for (int y = 0; y < bin->height; y++) {
		for (int x = 0; x < bin->width; x++) {
			int n = (unsigned char)gray->imageData[gray->widthStep * y + x];
			if (n < 127) {
				bin->imageData[bin->widthStep * y + x] = 0;
			}
			else {
				bin->imageData[bin->widthStep * y + x] = 255;
			}
		}
	}
}

void main() {
	IplImage* img;
	IplImage* img_gray;
	IplImage* img_bin;
	char th = 127;
	char filename[] = "C:/Users/hotar/Downloads/photo.jpg";

	 // �摜�f�[�^�̓ǂݍ���
	if ((img = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED)) == NULL) {
		printf("�摜�t�@�C���̓ǂݍ��݂Ɏ��s���܂����D \n");
		return;
	}
	// �ǂݍ��񂾉摜�Ɠ����T�C�Y�̃O���C�X�P�[���摜(nChannels=1)�𐶐�
	img_gray = cvCreateImage(cvSize(img->width, img->height), img->depth, 1);

	cvNamedWindow("Original");
	cvShowImage("Original", img);

	printf("nChannels = %d\n", img->nChannels);
	if (img->nChannels == 3) {
		// �J���[�摜�������ꍇ�C�O���C�X�P�[���������摜��\��
		printf("---Color Image\n");
		bgr2gray(img_gray, img);	// �O���C�X�P�[����

		cvNamedWindow("Grayscale");
		cvShowImage("Grayscale", img_gray);
	}
	else if (img->nChannels == 1) {
		// �O���C�X�P�[���摜�������ꍇ�́Cimg_gray�Ɍ��摜���R�s�[����
		printf("---Graysacle Image\n");
		cvCopy(img, img_gray);
	}

	// �O���C�X�P�[���摜�Ɠ����傫���̉摜�𐶐� (���O�C�P�̓O���C�X�P�[���摜�̂O�C�Q�T�T�ŕ\��)
	img_bin = cvCreateImage(cvSize(img->width, img->height), img->depth, img_gray->nChannels);
	gray2bin(img_bin, img_gray, th);

	cvNamedWindow("Binary");
	cvShowImage("Binary", img_bin);
	printf("Threshold%d\n", th);

	cvWaitKey(0);
	cvDestroyAllWindows();
	cvReleaseImage(&img);
	return;

}