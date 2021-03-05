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
#include "c3_resize_crop.hpp"
#include "c4_draw_text.hpp"
#include "c5-warp-perspective.hpp"
#include "c6-color-detection.hpp"
#include "c7_detect_shape.hpp"
int main() {
    
//    open_image("Resources/cat.jpg");
//    open_video("Resources/test_video.mp4");
//    open_video_from_camera();
//    someBasicFunctionOnImage("Resources/cat.jpg");
//    testResize("Resources/cat.jpg");
//    testCrop("Resources/cat.jpg");

//    Chapter 4: Draw shape and insert text
//    drawShape();
//    testText();
    
//    Chapter5: Warp perspective (Giống chức năng các app scanner)
//    testWarpImage("Resources/cards.jpg");
    
//    Chapter 6: Color detection
//    testColorDetection("Resources/shapes.png");
    
//    Chapter 7: Detect shape
    testDetectShape("Resources/shapes.png");
    
    
    return 0;
    
}
