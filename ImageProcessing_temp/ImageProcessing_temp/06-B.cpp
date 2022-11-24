// �ۑ�No.06-B

#include<stdio.h>
#include<opencv/highgui.h>

void main()
{
	CvSize size;
	size.width = 256;
	size.height = 100;
	IplImage* img = cvCreateImage(size, IPL_DEPTH_8U, 1); // 1: �O���C�X�P�[���摜
	cvSetZero(img); // �摜�f�[�^�� 0(��) �ŏ�����
	// ------ �D�F�摜(���ׂĂ̔Z�x�l=128)�̐��� ---------
	for (int y = 0; y < img->height; y++) {
		for (int x = 0; x < img->width; x++) {
			img->imageData[img->widthStep * y + x] = x;	// �s�N�Z���l�� 0�`255
		}
	}
	cvNamedWindow("Gray");
	cvShowImage("Gray", img);
	cvSaveImage("Gray.bmp", img); // Bitmap�摜�Ƃ��ĕۑ�
	// ---------------------------
	cvWaitKey(0); // �����L�[���������܂ő҂�
	cvDestroyAllWindows();
	cvReleaseImage(&img);
}