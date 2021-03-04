//
//  c4_draw_text.cpp
//  opencv-basic
//
//  Created by Ngo Thai on 04/03/2021.
//

#include "c4_draw_text.hpp"

void drawShape() {
    
    //Blank Image
    //512, 512: Width - Height
    //CV_8: Sử dụng 8bit, range màu sẽ từ 0-255
    //CV_8U: Sử dụng số dương, nghĩa là từ 0-255 thay vì -127 -> 127
    //CV_8UC3: 3 Channel RGB
    //Scalar(255, 0, 0) = Blue color
    Mat img(512, 512, CV_8UC3, Scalar(52,73,94));
    //circle(targetimage, centerPoint, radius, colorBorder, thinkness)
    //circle(img, Point(256, 256), 155, Scalar(46,204,113), 10);
    circle(img, Point(256, 256), 155, Scalar(46,204,113), FILLED);
    
    //rectangle(targetImage, top-left point, bottom-right point, color, thinkness)
    //rectangle(img, Point(130, 226), Point(238, 286), Scalar(231,76,60), 10);
    rectangle(img, Point(130, 226), Point(238, 286), Scalar(231,76,60), FILLED);
    
    //line(targetImage, startPoint, endPoint, Color, thinkness);
    line(img, Point(130, 296), Point(382, 256), Scalar(255, 255, 255), 2);
    
    //putText(targetImage, ContentString ,startingPoint, Font, FontScale, Color, thinkness)
    putText(img, "Hello world", Point(137, 262), FONT_HERSHEY_DUPLEX, 2, Scalar(255,255,255), 2);
    
    imshow("Original Image", img);
    waitKey(0);
}

void testText() {
    
    waitKey(0);
}
