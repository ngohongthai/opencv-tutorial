#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgHSV, mask, imgColor;
int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;

VideoCapture cap(0);
Mat img;

int main() {
    //Tạo track bar
    namedWindow("Trackbars", (640, 200));
    createTrackbar("Hue max", "Trackbars", &hmax, 179);
    createTrackbar("Hue min", "Trackbars", &hmin, 179); // 179 is max value
    createTrackbar("Sat max", "Trackbars", &smax, 255);
    createTrackbar("Sat min", "Trackbars", &smin, 255);
    createTrackbar("Val max", "Trackbars", &vmax, 255);
    createTrackbar("Val min", "Trackbars", &vmin, 255);

    while (true)
    {
        cap.read(img);
        cvtColor(img, imgHSV, COLOR_BGR2HSV);
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(imgHSV, lower, upper, mask);

        imshow("Original Image", img);
        imshow("Image mask", mask);
        waitKey(1);
    }

    return 0;
}