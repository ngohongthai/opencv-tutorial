//
//  c6-color-detection.cpp
//  opencv-basic
//
//  Created by Ngo Thai on 05/03/2021.
//

#include "c6-color-detection.hpp"

int hmin = 0, smin = 0, vmin = 153;
int hmax = 179, smax = 255, vmax = 255;

void testColorDetection(string imagePath) {
    Mat img = imread(imagePath);
    Mat imgHSV, mask;
    
    /**
     Trước tiên chuyển đổi ảnh sang không gian màu HSV vì dễ dàng phát hiện color hơn trong không gian màu này.
     Một điểm cân lưu ý là với các thư viện đọc ảnh và hiển thị ảnh như matplotlib, Pillow thì các ảnh được đọc theo RGB tuy nhiên Opencv đọc ảnh theo các kênh BGR.
     
     Thức tế với các bài toán khi có ảnh rõ ràng thì hoàn toàn có thể sử dụng hệ màu RGB tuy nhiên trong điều kiện thực tế thường các màu sẽ bị mờ hoặc có vẩn đục do ngoại cảnh bên ngoài nên thường hay ưu tiên việc sử dụng hệ màu HSV hơn
     
     Không gian màu HSV (còn gọi là HSB) là một cách tự nhiên hơn để mô tả màu sắc, dựa trên 3 số liệu:
     H: (Hue) Vùng màu
     S: (Saturation) Độ bão hòa màu
     B (hay V): (Bright hay Value) Độ sáng
     Ứng dụng điển hình nhất của HSV là trong việc lọc màu. Giả sử chúng ta có 1 bài toán là nhận dạng màu sắc của đèn đường giao thông và đầu vào là ảnh dưới và yêu cầu ở đây là nhận dạng đèn màu xanh lá cây.
     Với bài toán này thì hướng tiếp cận đơn giản nhất chính là lọc màu xanh lá cây ra khỏi ảnh.
     */
    cvtColor(img, imgHSV, COLOR_BGR2HSV);
    
    //Tạo track bar
    namedWindow("Trackbars");
    createTrackbar("Hue min", "Trackbars", &hmin, 179); // 179 is max value
    createTrackbar("Hue max", "Trackbars", &hmax, 179);
    createTrackbar("Sat min", "Trackbars", &smin, 255);
    createTrackbar("Sat max", "Trackbars", &smax, 255);
    createTrackbar("Val min", "Trackbars", &vmin, 255);
    createTrackbar("Val max", "Trackbars", &vmax, 255);
    
    while (true) {
        //B2: Thu thập màu sắc bằng hàm: inRange(imgHSV, lower, upper, mask)
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(imgHSV, lower, upper, mask);
        
        imshow("Original Image", img);
        imshow("HSV image", imgHSV);
        imshow("Image mask", mask);
        waitKey(1);
    }
}
