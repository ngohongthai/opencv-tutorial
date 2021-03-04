//
//  chapter2_basic_functions.cpp
//  opencv-basic
//
//  Created by Ngo Thai on 03/03/2021.
//

#include "chapter2_basic_functions.hpp"


void someBasicFunctionOnImage(string path) {
    Mat img = imread(path);
    Mat imgGray, imgBlur, imgCanny, imgDilation, imgErosion;
    
    //Convert to Gray
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    
    /**
     Making blur
     More info about blur:
     https://thigiacmaytinh.com/lam-min-anh-smoothing/
     https://docs.opencv.org/2.4/doc/tutorials/imgproc/gausian_median_blur_bilateral_filter/gausian_median_blur_bilateral_filter.html#gaussian-filter
     */
    GaussianBlur(img, imgBlur, Size(3,3), 3,0);
    
    /**
     Canny detection:
     Detect cạnh dùng thuật toán Canny Edge Detection (Hiện nay có 2 thuật toán phổ biến là sobel edge detection và canny edge detection)
     */
    Canny(imgBlur, imgCanny, 50, 150);
    
    /**
     Dilation
     Dilation hay còn còn là sự giãn nở
     - Với những hình ảnh bị đứt nét có thể giúp nối liền ảnh lại
     - Với những pixel nhiễu xung quanh đối tượng sẽ trở thành viền của đối tượng
     - Giúp nổi bật đối tượng trong ảnh hơn
     */
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(imgCanny, imgDilation, kernel);
    
    /**
     Erosion
     Erosion hay còn gọi là xói mòn là một trong hai toán tử cơ bản trong lĩnh vực hình thái toán học ( mathematical morphology).
     - Loại bỏ những pixel nhiễu cô lập
     - Loại bỏ những pixel nhiễu xung quanh đối tượng giúp cho phần viền (cạnh) của đối tượng trở nên mịn hơn
     - Loại bỏ lớp viền (cạnh) của đối tượng giúp đối tượng trở nên nhỏ hơn và đặt những pixel viền đó trở thành lớp nền của đối tượng
     */
    erode(imgDilation, imgErosion, kernel);
    
    
    imshow("Image", img);
    imshow("Image Gray", imgGray);
    imshow("Image Blur", imgBlur);
    imshow("Image Canny", imgCanny);
    imshow("Image Dilation", imgDilation);
    imshow("Image Erosion", imgErosion);
    waitKey(0);
}
