//
//  c3_resize_crop.cpp
//  opencv-basic
//
//  Created by Ngo Thai on 04/03/2021.
//

#include "c3_resize_crop.hpp"

void testResize(string imagePath) {
    Mat img = imread(imagePath);
    Mat imgResize;
    
    //resize(img, imgResize, Size(640, 480));
    //or scale 50%
    resize(img, imgResize, Size(), 0.5, 0.5);
    
    imshow("Original Image", img);
    imshow("Resize image", imgResize);
    waitKey(0);
}
void testCrop(string imagePath) {
    Mat img = imread(imagePath);
    Mat imgCrop;
    
    //Crop image
    Rect roi(100, 100, 300, 250); // (x, y, width, height)
    imgCrop = img(roi);
    
    imshow("Original Image", img);
    imshow("Croped Image", imgCrop);
    waitKey(0);
}
