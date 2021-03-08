//
//  main.cpp
//  DocumentScanner
//
//  Created by Ngo Thai on 08/03/2021.
//

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgOriginal, imgGray, imgBlur ,imgCanny, imgThre, imgDilation, imgWarp;
// initial Points là khi hàm getContours return ra, nó có thể không đúng thứ tự trên dưới trái phải
// lúc này ta cần 1 hàm để reorder lại các điểm theo thứ tự mong muốn và lưu chúng vào docsPoints
vector<Point> initialPoints, docPoints;

//Kích thước giấy (in pixcel)
float width = 420, height = 596;

Mat preprocessing(Mat img) {
    //Convert to Gray
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    
    /**
     Making blur
     More info about blur:
     https://thigiacmaytinh.com/lam-min-anh-smoothing/
     https://docs.opencv.org/2.4/doc/tutorials/imgproc/gausian_median_blur_bilateral_filter/gausian_median_blur_bilateral_filter.html#gaussian-filter
     */
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
    
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
    
    return imgDilation;
}

//Lấy đường viền
vector<Point> getContours(Mat imgDil)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    vector<vector<Point>> conPoly(contours.size());
    vector<Point> biggest;
    int maxArea = 0;
    // Remove noise và tách các vùng ra thành đối tượng
    for (int i = 0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        //cout << area << endl;
        
        //Vùng nào có area > 1000 thì được chấp nhận, còn lại được coi là noise
        if (area > 1000)
        {
            float peri = arcLength(contours[i], true); //True là thể hiện đường bao của đối tượng này đã được đóng hay chưa
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true); // 0.02 * peri: đây là số ngẫu nhiên nhưng tác giả khuyên là lấy số này, true là đường này đóng hay k
            if (area > maxArea && conPoly[i].size() == 4) { //Make sure hình nhận đc là hình chữ nhật hoặc hình vuông
                //drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 2);
                biggest = { conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3] };
                maxArea = area;
            }
            
        }
    }
    return biggest;
}

void drawPoints(vector<Point> points, Scalar color) {
    for (int i = 0; i< points.size(); i++) {
        circle(imgOriginal, points[i], 10, color, FILLED);
        putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 3, color, 3);
    }
}

vector<Point> reorder(vector<Point> points) {
    // Ý tưởng:
    // Giả sử toạ độ 4 góc là (x, y) nào đó
    // sum = x + y mà
    //  + lớn nhất: điểm đó là bottom-right
    //  + nhỏ nhất: điểm đó là top-left
    // sub = x - y mà
    //  + sub > 0: điểm đó là
    vector<Point> newPoints;
    vector<int> sumPoints, subPoints;
    
    for (int i = 0; i < 4; i++) {
        sumPoints.push_back(points[i].x + points[i].y);
        subPoints.push_back(points[i].x - points[i].y);
    }
    
    newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // 0
    newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // 1
    newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // 2
    newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // 3
    
    return newPoints;
}


Mat getWarp(Mat img, vector<Point> points, float width, float height) {
    //B1: Dùng paint để xác định toạ độ pixel của các điểm góc lá bài
    //Vì yêu cầu dùng dấu phẩy động nên ...
    Point2f src[4] = { points[0], points[1], points[2], points[3] };
    //Destination point
    Point2f des[5] = { {0.0f, 0.0f}, {width, 0.0f}, {0.0f, height},  {width, height} };
    
    //B2: Transform the point
    Mat matrixTransform = getPerspectiveTransform(src, des);
    warpPerspective(img, imgWarp, matrixTransform, Point(width, height));
    return imgWarp;
}

int main() {
    
    string path = "Resources/paper.jpg";
    imgOriginal = imread(path);
    
    //Mục đích là làm cho ảnh nhỏ hơn, dễ test và debug, sau khi hoàn thành sẽ remove để đảm bảo chất lượng.
    resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);
    
    //Bước tiếp theo là preprocessing ảnh, chuyển đổi ảnh sang Gray, làm mờ bằng GaussianBlur, sau đó dùng Canny để detect cạnh.
    imgThre = preprocessing(imgOriginal);
    
    // Khi biết cạnh thì sẽ biết được paper đang ở đâu, sau đó dựa trên toạ độ giấy đó trích xuất 4 diểm của 4 góc
    //Get Contours - Biggest
    initialPoints = getContours(imgThre);
    //drawPoints(initialPoints, Scalar(0, 0, 255));
    docPoints = reorder(initialPoints);
    //drawPoints(docPoints, Scalar(0, 255, 0));
    //Từ 4 điểm xử lý để được hình ảnh nhìn từ trên xuống như khi scan
    imgWarp = getWarp(imgOriginal, docPoints, width, height);
    
    
    imshow("imgOriginal", imgOriginal);
    imshow("imgDil", imgThre);
    imshow("imgWarp", imgWarp);
    waitKey(0);
    return 0;
    
}
