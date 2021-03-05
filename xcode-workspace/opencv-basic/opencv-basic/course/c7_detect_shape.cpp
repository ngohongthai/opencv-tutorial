//
//  c7_detect_shape.cpp
//  opencv-basic
//
//  Created by Ngo Thai on 05/03/2021.
//

#include "c7_detect_shape.hpp"

//Lấy đường viền
void getContours(Mat imgDil, Mat targetDrawingImage) {
    
}

void testDetectShape(string imagePath) {
    Mat img = imread(imagePath);
    Mat imgGray, imgBlur, imgCanny, imgDilation;
    
    //----Start pre-processing
    //Đầu tiên cần detect cạnh dùng canny egde detector
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3,3), 3, 0);
    /**
     Canny detection:
     Detect cạnh dùng thuật toán Canny Edge Detection (Hiện nay có 2 thuật toán phổ biến là sobel edge detection và canny edge detection)
     */
    Canny(imgBlur, imgCanny, 25, 75);
    
    /**
     Dilation
     Dilation hay còn còn là sự giãn nở
     - Với những hình ảnh bị đứt nét có thể giúp nối liền ảnh lại
     - Với những pixel nhiễu xung quanh đối tượng sẽ trở thành viền của đối tượng
     - Giúp nổi bật đối tượng trong ảnh hơn
     */
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(imgCanny, imgDilation, kernel);
    //----End pre-processing
    
    getContours(imgDilation, img);
    
    
    imshow("Original Image", img);
    imshow("Dilation image", imgDilation);
    waitKey(0);
}
