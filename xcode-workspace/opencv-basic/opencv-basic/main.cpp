//
//  main.cpp
//  opencv-basic
//
//  Created by Ngo Thai on 03/03/2021.
//

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Images  //////////////////////

int main() {
    
    string path = "Resources/cat.jpg";
    Mat img = imread(path);
    imshow("Image", img);
    waitKey(0);
    return 0;
    
}
