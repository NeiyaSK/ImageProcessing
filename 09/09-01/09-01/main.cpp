#include <stdio.h>
#include <opencv/highgui.h>

// double�^�̃s�N�Z���l��, unsigned char�^�ŕԂ�. 0�����̒l��0�ɁC255�ȏ�̒l��255�ɃN���b�v����
unsigned char clip(double v)
{
	return (v > 255) ? 255 : (v < 0) ? 0 : (unsigned char)v;
}

// ���`�ϊ�(Linear Stretch)
// dst: �ϊ����ʂ̉摜
// src: �ϊ����̉摜
// dst = src * a + b
void linear(IplImage* dst, IplImage* src, double a, double b)
{
	double v;
	for (int y = 0; y < src->height; y++)
	{
		for (int x = 0; x < src->width; x++)
		{
			// �O���C�X�P�[���J���[�����܂Ƃ߂ď������邽�߂̃��[�v
			for (int ch = 0; ch < src->nChannels; ch++)
			{
				v = (unsigned char)src->imageData[src->widthStep * y + x * src->nChannels + ch] * a + b;
				dst->imageData[dst->widthStep * y + x * dst->nChannels + ch] = clip(v);
			}
		}
	}
}

void main()
{
	IplImage* src;
	IplImage* dst;
	double a, b;	// �W��

	int mode = 5;	// ���̒l�Ń��[�h��؂�ւ���

	char filename[] = "C:/Users/hotar/Documents/Git/ImageProcessing/SampleImage/color/Mandrill.bmp";

	switch (mode)
	{
		// a, b�̒l�����ꂼ��ݒ肷��
	case 0:		// ���ϊ�
		a = 1.0;
		b = 0.0;
		break;
	case 1:		// �@���邭
		a = 1.0;
		b = 50.0;
		break;
	case 2:		// �A�Â�
		a = 1.0;
		b = -50.0;
		break;
	case 3:		// �B�R���g���X�g������
		a = 1.5;
		b = 0.0;
		break;
	case 4:		// �C�R���g���X�g���キ
		a = 0.5;
		b = 0.0;
		break;
	case 5:		// �D�K�����]
		a = -1.0;
		b = 100.0;
		break;
	default:	// 
		printf("mode���͈͊O�̒l�ł�\n");
		return;
	}

	// �摜�f�[�^�̓ǂݍ���
	if ((src = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED)) == NULL)
	{
		printf("�摜�t�@�C���̓ǂݍ��݂Ɏ��s���܂����D");
		return;
	}
	printf("%snnChannels = %d\n\nMode = %d\n\ta = %f\n\tb = %f\n", filename, src->nChannels, mode, a, b);

	// �ǂݍ��񂾉摜�Ɠ����T�C�Y�C�����`�����l�����inChannels)�̉摜�𐶐�
	dst = cvCreateImage(cvSize(src->width, src->height), src->depth, src->nChannels);

	cvNamedWindow("Source");
	cvShowImage("Source", src);

	linear(dst, src, a, b);

	cvNamedWindow("Destination");
	cvShowImage("Destination", dst);

	cvWaitKey(0);
	cvDestroyAllWindows();
	cvReleaseImage(&dst);
	cvReleaseImage(&src);
	return;
}