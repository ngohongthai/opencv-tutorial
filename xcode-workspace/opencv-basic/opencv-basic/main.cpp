//
//  main.cpp
//  opencv-basic
//
//  Created by Ngo Thai on 03/03/2021.
//

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#include "chapter_1.hpp"
#include "chapter2_basic_functions.hpp"

int main() {
    
//    open_image("Resources/cat.jpg");
//    open_video("Resources/test_video.mp4");
//    open_video_from_camera();
    someBasicFunctionOnImage("Resources/cat.jpg");
    return 0;
    
}
