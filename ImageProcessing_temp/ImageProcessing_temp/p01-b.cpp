#include <stdio.h>
#include <opencv/highgui.h>
/*
void main()
{
	CvSize size;
	size.width = 200;
	size.height = 100;
	
	IplImage* img = cvCreateImage(size, IPL_DEPTH_8U, 1);	// 1: �O���C�X�P�[���摜
	IplImage* img_g = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage* img_b = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage* img_w = cvCreateImage(size, IPL_DEPTH_8U, 1);

	cvSetZero(img);

	// -----�摜�̐��� -----
	for (int y = 0; y < img->height; y++)
	{
		for (int x = 0; x < img->width; x++)
		{
			img_g->imageData[img_b->widthStep * y + x] = 128;	// �s�N�Z������ 0~255
			img_b->imageData[img_b->widthStep * y + x] = 0;
			img_w->imageData[img_w->widthStep * y + x] = 255;
		}
	}
	
	cvNamedWindow("Gray");
	cvNamedWindow("Black");
	cvNamedWindow("White");
	cvShowImage("Gray", img_g);
	cvShowImage("Black", img_b);
	cvShowImage("White", img_w);
	cvSaveImage("Gray.bmp", img_g);	// Bitmap�摜�Ƃ��ĕۑ�
	cvSaveImage("Black.bmp", img_b);
	cvSaveImage("White.bmp", img_w);

	// -----
	cvWaitKey(0);	// �Ȃɂ��L�[���������܂ő҂�

	cvDestroyAllWindows();
	cvReleaseImage(&img);
	cvReleaseImage(&img);
	cvReleaseImage(&img);
	cvReleaseImage(&img);
}
*/