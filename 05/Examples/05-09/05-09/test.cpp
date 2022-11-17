// Example 05-09: OpenCV check
#include <stdio.h>
#include <opencv/highgui.h>

int main(void)
{
    IplImage* img;
    cvNamedWindow("Test Window");
    img = cvLoadImage("C:/.../mono/LENNA.bmp", CV_LOAD_IMAGE_UNCHANGED);

    if (img == NULL) {
        printf("Load Error.\n");
        cvWaitKey(0);
    }
    else {
        cvShowImage("Test Window", img);
        printf("nChannels = %d\ndepth = %d\nwidth = %d, height = %d\n"
            , img->nChannels, img->depth, img->width, img->height);
        cvWaitKey(0);

        cvDestroyAllWindows();
        cvReleaseImage(&img);
    }
    return 0;
}
