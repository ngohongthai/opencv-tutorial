//
//  c5-warp-perspective.cpp
//  opencv-basic
//
//  Created by Ngo Thai on 05/03/2021.
//

#include "c5-warp-perspective.hpp"

float width = 250, height = 350;
Mat matrixTransform, imgWarp;

void testWarpImage(string imagePath) {
    Mat img = imread(imagePath);
    
    /**
     Mục đích của phần test này là lấy ra được hình lá bài từng lá 1, như trong góc nhìn của ảnh gốc thì các
     lá bài đều xiêu vẹo
     => Giống các app scanner
     */
    
    //B1: Dùng paint để xác định toạ độ pixel của các điểm góc lá bài
    //Vì yêu cầu dùng dấu phẩy động nên ...
    Point2f src[4] = {{529, 142}, {771, 190}, {405, 395}, {674, 457}};
    //Destination point
    //Point2f des[5] = {{0.0f, 0.0f}, {width, 0.0f}, {0.0f, height},  {width, height}}
    Point2f des[5] = {{0.0f, 0.0f}, {width, 0.0f}, {0.0f, height},  {width, height}};
    
    //B2: Transform the point
    matrixTransform = getPerspectiveTransform(src, des);
    warpPerspective(img, imgWarp, matrixTransform, Point(width, height));
    
    imshow("Original Image", img);
    imshow("Warp Image", imgWarp);
    waitKey(0);
}
