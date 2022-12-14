// ÛèNo.07-A
/*
#include <stdio.h>
#include <opencv/highgui.h>

void main()
{
    IplImage* img;

    // æTCY 200~200, channels = 3 : J[æ
    img = cvCreateImage(cvSize(200, 200), IPL_DEPTH_8U, 3);

    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            if (x < img->width / 2) {
                if (y < img->height / 2) { // : (R,G,B)=(255,255,255)
                    img->imageData[img->widthStep * y + x * 3 + 2] = 255;   // R
                    img->imageData[img->widthStep * y + x * 3 + 1] = 255;   // G
                    img->imageData[img->widthStep * y + x * 3 + 0] = 255;   // B
                }
                else {                    // Ô: (R,G,B)=(255,0,0)
                    img->imageData[img->widthStep * y + x * 3 + 2] = 255;   // R
                    img->imageData[img->widthStep * y + x * 3 + 1] = 0;     // G
                    img->imageData[img->widthStep * y + x * 3 + 0] = 0;     // B
                }
            }
            else {
                if (y < img->height / 2) { // Î: (R,G,B)=(0,255,0)
                    img->imageData[img->widthStep * y + x * 3 + 2] = 0;     // R
                    img->imageData[img->widthStep * y + x * 3 + 1] = 255;   // G
                    img->imageData[img->widthStep * y + x * 3 + 0] = 0;     // B
                }
                else {                     // Â: (R,G,B)=(0,0,255)
                    img->imageData[img->widthStep * y + x * 3 + 2] = 0;     // R
                    img->imageData[img->widthStep * y + x * 3 + 1] = 0;     // G
                    img->imageData[img->widthStep * y + x * 3 + 0] = 255;   // B
                }
            }

        }
    }
    cvNamedWindow("Color");
    cvShowImage("Color", img);
    cvSaveImage("color.bmp", img);


    cvWaitKey(0);
    cvDestroyAllWindows();
    cvReleaseImage(&img);
}
*/