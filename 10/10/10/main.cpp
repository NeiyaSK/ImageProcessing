#include<stdio.h>
#include<opencv/highgui.h>


// VisualStudio���̂݁Ffopen()���g����悤�ɂ���
#pragma warning(disable: 4996)

// �J���[�摜���O���C�X�P�[����
void bgr2gray(IplImage* gray, IplImage* bgr) {
	for (int y = 0; y < gray->height; y++) {
		for (int x = 0; x < gray->width; x++) {
			int b = (unsigned char)bgr->imageData[bgr->widthStep * y + x * 3 + 0];
			int g = (unsigned char)bgr->imageData[bgr->widthStep * y + x * 3 + 1];
			int r = (unsigned char)bgr->imageData[bgr->widthStep * y + x * 3 + 2];
			//gray->imageData[gray->widthStep * y + x] = 0.298912 * r + 0.586611 * g + 0.11447 * b;
		
		}
	}
}

void calc_histogram(unsigned int hist[], IplImage* gray) {
	for (int y = 0; y < gray->height; y++) {
		for (int x = 0; x < gray->width; x++) {
			for (int i = 0; i < 256; i++) {
				hist[i]++;
			}
		}
	}
}

void main() {
	IplImage* img;
	IplImage* gray;
	unsigned int hist[256] = { 0 };		// �q�X�g�O����������

	char filename[] = "C:/Users/hotar/Downloads/photo.jpg";
	char outputFilename[] = "Hitogram.csv";

	// �摜�f�[�^�̓ǂݍ���
	if ((img = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED)) == NULL) {
		printf("�摜�t�@�C���̓ǂݍ��݂Ɏ��s���܂����D\n");
		return;
	}
	// �ǂݍ��񂾉摜�Ɠ����T�C�Y�̃O���C�X�G�[���摜(nChannels=1)�𐶐�
	gray = cvCreateImage(cvSize(img->width, img->height), img->depth, 1);

	cvNamedWindow("Original");
	cvShowImage("Original", img);

	if (img->nChannels == 3) {
		// �J���[�摜�������ꍇ�C�O���C�X�P�[���������摜��\��
		bgr2gray(gray, img);	// �O���C�X�P�[����

		cvNamedWindow("Grayscale");
		cvShowImage("Grayscale", gray);
	}
	else if (img->nChannels == 1) {
		// �O���C�X�P�[���摜�������ꍇ�ɂ́Cimg_gray��{�摜���R�s�[����
		cvCopy(img, gray);
	}

	// �����܂łŁC�J���[�摜�ł���΃O���C�X�P�[�����������̂��C
	// ���Ƃ���O���C�X�P�[���摜�ł���΁C������R�s�[�������̂��Cgray�ɓ����Ă����ԂɂȂ�D

	calc_histogram(hist, gray);		// �q�X�g�O�������v�Z

	FILE* fp = fopen(outputFilename, "w");	// �������݁i�㏑���j���[�h�Ńt�@�C���I�[�v��
	for (int i = 0; i < 256; i++) {
		printf("%d, %u\n")
	}
}