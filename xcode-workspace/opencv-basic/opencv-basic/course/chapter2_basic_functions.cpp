//
//  chapter2_basic_functions.cpp
//  opencv-basic
//
//  Created by Ngo Thai on 03/03/2021.
//

#include "chapter2_basic_functions.hpp"


void someBasicFunctionOnImage(string path) {
    Mat img = imread(path);
    Mat imgGray, imgBlur;
    
    //Convert to Gray
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    
    /**
     Making blur
     More info about blur:
     https://thigiacmaytinh.com/lam-min-anh-smoothing/
     https://docs.opencv.org/2.4/doc/tutorials/imgproc/gausian_median_blur_bilateral_filter/gausian_median_blur_bilateral_filter.html#gaussian-filter
     */
    GaussianBlur(img, imgBlur, Size(7,7), 5,0);
    
    imshow("Image", img);
    imshow("Image Gray", imgGray);
    imshow("Image Blur", imgBlur);
    waitKey(0);
}
