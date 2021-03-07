#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
//for chapter8: face detection
#include <opencv2/objdetect.hpp>

using namespace cv;
using namespace std;

/*
* Chapter 1: Open image and video
*/
void open_image(string path) {
    Mat img = imread(path);
    imshow("Image", img);
    waitKey(0);
}

void open_video(string path) {
    VideoCapture cap(path);
    Mat img;
    while (true) {
        cap.read(img);
        imshow("Image", img);
        waitKey(1); //mini-second, tăng số này lên video sẽ chậm hơn
    }
}

void open_video_from_camera() {
    VideoCapture cap(0); //0: id source
    Mat img;
    while (true) {
        cap.read(img);
        imshow("Image", img);
        waitKey(1); //mini-second, tăng số này lên video sẽ chậm hơn
    }
}
//---end chapter 1---

/*
* Chapter 2: Basic function
*/
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
// --- end chapter 2

/*
* Chapter 3 resize and crop
*/
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

//---end chapter 3 ---

/*
* Chapter 4: Draw shape and text
*/
void drawShape() {

    //Blank Image
    //512, 512: Width - Height
    //CV_8: Sử dụng 8bit, range màu sẽ từ 0-255
    //CV_8U: Sử dụng số dương, nghĩa là từ 0-255 thay vì -127 -> 127
    //CV_8UC3: 3 Channel RGB
    //Scalar(255, 0, 0) = Blue color
    Mat img(512, 512, CV_8UC3, Scalar(52, 73, 94));
    //circle(targetimage, centerPoint, radius, colorBorder, thinkness)
    //circle(img, Point(256, 256), 155, Scalar(46,204,113), 10);
    circle(img, Point(256, 256), 155, Scalar(46, 204, 113), FILLED);

    //rectangle(targetImage, top-left point, bottom-right point, color, thinkness)
    //rectangle(img, Point(130, 226), Point(238, 286), Scalar(231,76,60), 10);
    rectangle(img, Point(130, 226), Point(238, 286), Scalar(231, 76, 60), FILLED);

    //line(targetImage, startPoint, endPoint, Color, thinkness);
    line(img, Point(130, 296), Point(382, 256), Scalar(255, 255, 255), 2);

    //putText(targetImage, ContentString ,startingPoint, Font, FontScale, Color, thinkness)
    putText(img, "Hello world", Point(137, 262), FONT_HERSHEY_DUPLEX, 2, Scalar(255, 255, 255), 2);

    imshow("Original Image", img);
    waitKey(0);
}
//--- end chapter 4 ---

/*
* Chapter 5: Warp perspective
*/
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
    Point2f src[4] = { {529, 142}, {771, 190}, {405, 395}, {674, 457} };
    //Destination point
    //Point2f des[5] = {{0.0f, 0.0f}, {width, 0.0f}, {0.0f, height},  {width, height}}
    Point2f des[5] = { {0.0f, 0.0f}, {width, 0.0f}, {0.0f, height},  {width, height} };

    //B2: Transform the point
    matrixTransform = getPerspectiveTransform(src, des);
    warpPerspective(img, imgWarp, matrixTransform, Point(width, height));

    imshow("Original Image", img);
    imshow("Warp Image", imgWarp);
    waitKey(0);
}

//--- end chapter 5

/*
* Chapter 6: Color detection
*/
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
//--- end chapter 6 ---

/*
* Chapter 7: Shapes detection
*/
//Lấy đường viền
void getContours(Mat imgDil, Mat *targetDrawingImage) {
    /*
    * findContours(InputOutputArray image, OutputArrayOfArrays contours, OutputArray hierarchy, int mode, int method, Point offset=Point())
    * 
    * image : hình ảnh cần tìm biên, là ảnh nhị phân.
    * contours : lưu trữ các đường biên tìm được, mỗi đường biên được lưu trữ dưới dạng một vector của các điểm.
    * hierarchy :  chứa thông tin về hình ảnh như số đường viền, xếp hạng các đường viền theo kích thước, trong ngoài, ..
    * 
    * mode :
    * CV_RETR_EXTERNAL : khi sử dựng cờ này nó chỉ lấy ra những đường biên bên ngoài, nhưng biên bên trong của vật thể bị loại bỏ.
    * CV_RETR_LIST : Khi sử dụng cờ này nó lấy ra tất cả các đường viền tìm được.
    * CV_RETR_CCOMP : khi sử dụng cờ này nó lấy tất cả những đường biên và chia nó làm 2 level, những đường biên bên ngoài đối tượng, 
    * và những đường biên bên trong đối tượng.
    * CV_RETR_TREE : khi sử dụng cờ này nó lấy tất cả các đường biên và tạo ra một hệ thống phân cấp đầy đủ của những đường lồng nhau.
    * 
    * method :
    * CV_CHAIN_APPROX_NONE : sử dụng cờ này sẽ lưu trữ tất cả các điểm của đường viền .
    * CV_CHAIN_APPROX_SIMPLE : nó sẽ nén đường viền trước khi lưu trữ, nén phân đoạn theo chiều ngang, chiều dọc và chéo . 
    * Ví dụ : một hình chữ nhật sẽ được mã hoá bằng toạ độ của 4 đỉnh.
    * CV_CHAIN_APPROX_TC89_L1 or CV_CHAIN_APPROX_TC89_KCOS :  Áp dụng thuật toán xấp xỉ Teh-Chin.
    */
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    /*
    * drawContours(InputOutputArray image, InputArrayOfArrays contours, 
    *               int contourIdx, const Scalar& color, 
    *               int thickness=1, int lineType=8, 
    *               InputArray hierarchy, int maxLevel=INT_MAX, Point offset=Point() )
    * Image : hình ảnh đích.
    * contours : tất cả những đường biên đầu vào.
    * contourIdx: (vẽ tất cả nên có giá trị bằng -1, nếu vẽ từng cái thì chọn index như trong vòng for bên dưới)
    * color : màu của đường biên.
    * thickness : độ dày của các đường được vẽ.
    * hierarchy : thông tin về phân cấp các đường biên, như trên hàm findContour.
    */
    //drawContours(*targetDrawingImage, contours, -1, Scalar(255, 0, 255), 2);

    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());
    // Remove noise và tách các vùng ra thành đối tượng
    for (int i = 0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        //cout << area << endl;

        //Vùng nào có area > 1000 thì được chấp nhận, còn lại được coi là noise
        if (area > 1000)
        {
            //Tìm bounding box xung quanh các object
            // - tính độ dài cung
            float peri = arcLength(contours[i], true); //True là thể hiện đường bao của đối tượng này đã được đóng hay chưa
            // - tìm điểm góc hoặc số lượng đường cong mà đa giác này có, ví dụ có 4 đường và 4 góc thì là hình chữ nhật hoặc hình vuông
            //   nếu có rất nhiều thì đây là đường tròn.
            // => tìm sự gần đúng của các đường cong
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true); // 0.02 * peri: đây là số ngẫu nhiên nhưng tác giả khuyên là lấy số này, true là đường này đóng hay k
            //drawContours(*targetDrawingImage, contours, i, Scalar(255, 0, 255), 2);
            drawContours(*targetDrawingImage, conPoly, i, Scalar(255, 0, 255), 2);
            cout << conPoly[i].size() << endl;

            boundRect[i] = boundingRect(conPoly[i]);
            //.tl() =  top - left
            //.br() = bottom - right
            

            // Tìm xem đối tượng nào là hình nào
            string objectType;
            int objectCorner = (int)conPoly[i].size();
            if (objectCorner == 3) { objectType = "Tri"; }
            else if (objectCorner == 4) { 
                float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
                if (aspRatio > 0.95 && aspRatio < 1.05) objectType = "Square";
                else objectType = "Rect";
            }
            else if (objectCorner > 4) { objectType = "Circle"; }
            putText(*targetDrawingImage, objectType, { boundRect[i].x, boundRect[i].y - 5}, FONT_HERSHEY_PLAIN, 0.75, Scalar(0, 255, 0), 2);
        }
    }
}

void testShapesDetection(string imagePath) {
    Mat img = imread(imagePath);
    Mat imgGray, imgBlur, imgCanny, imgDilation;

    //----Start pre-processing
    //Đầu tiên cần detect cạnh dùng canny egde detector
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
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

    imshow("Original Image", img);
    getContours(imgDilation, &img);
    imshow("Dilation image", imgDilation);
    imshow("Contours detection image", img);
    waitKey(0);
}
//---end chapter 7

/*
* Chapter 8: Face detection
* -- Thuật toán Viola-Jones --
*/

void testFaceDetection(string facePicturePath) {
    Mat img = imread(facePicturePath);

    CascadeClassifier faceCascade;
    faceCascade.load("Resources/haarcascade_frontalface_default.xml");
    // Check xem load được hay không
    if (faceCascade.empty())
    {
        cout << "XML file is not loaded" << endl;
    }

    // Detect face và lưu trong 1 bounding box
    vector<Rect> faces;
    
    /*detectMultiScale( grayImage, output bounding box ,scaleFactor = 1.1, minNeighbors = 5)*/
    //grayImage: là nguồn/bức ảnh xám.
    //scaleFactor : độ scale sau mỗi lần quét, tính theo 0.01 = 1 % .Nếu như để scaleFactor = 1 thì tấm ảnh sẽ giữ nguyên
    //minNeighbors : scale và quét ảnh cho đến khi không thể scale được nữa thì lúc này sẽ xuất hiện những khung ảnh trùng nhau, 
    //             số lần trùng nhau chính là tham số minNeighbors để quyết định cho việc có chọn khung ảnh này là khuôn mặt hay không.
    // Ngoài ra còn có các tham số như là maxScale, minScale để cho kích thước khung ảnh bắt đầu và kích thước khung ảnh kết thúc.
    //Có thể hiệu chỉnh tham số scaleFactor, minNeighbors, minScale, maxScale để có kết quả như mong muốn.
    faceCascade.detectMultiScale(img, faces, 1.1, 10);

    for (int i = 0; i < faces.size(); i++)
    {
        rectangle(img, faces[i].tl(), faces[i].br(), Scalar(231, 76, 60), 2);
    }
    
    imshow("Original Image", img);
    waitKey(0);
}

//--- end chapter 8

/*
* Chapter 9: Virtual painter
*/

//Using Color picker to find this value
//{hmax, hmin, smax, smin, vmax, vmin}
vector<vector<int>> myColors{ {100, 23, 255, 0, 185, 61},       // Green
                             {106, 25, 255, 181, 255, 119} };   // Yellow
vector<Scalar> myColorValues{ {19, 202, 115},   //Green
                              {195, 252, 37} }; // Yellow
Mat img;
vector<vector<int>> newPoint; // {{x, y, value of color}, ....}, value of color = 0: green, = 1: yellow

Point getContours(Mat imgDil)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());
    Point myPoint(0, 0);
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
            boundRect[i] = boundingRect(conPoly[i]);
            myPoint.x = boundRect[i].x + boundRect[i].width / 2;
            myPoint.y = boundRect[i].y;

            drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
            rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
        }
    }
    return myPoint;
}

void drawOnCanvas(vector<vector<int>> newPoints, vector<Scalar> myColorValues )
{
    for (int i = 0; i < newPoints.size(); i++)
    {
        circle(img, Point(newPoints[i][0], newPoints[i][1]), 10, myColorValues[newPoints[i][2]], FILLED );
    }
}

void findColor(Mat img)
{
    Mat imgHSV;
    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    for (int i = 0; i < myColors.size(); i++)
    {
        Scalar lower(myColors[i][1], myColors[i][3], myColors[i][5]);
        Scalar upper(myColors[i][0], myColors[i][2], myColors[i][4]);
        Mat mask;
        inRange(imgHSV, lower, upper, mask);
        //imshow(to_string(i), mask);
        Point myPoint = getContours(mask);
        if (myPoint.x != 0 && myPoint.y != 0)
        {
            newPoint.push_back({ myPoint.x, myPoint.y, i });
        }
        
    }
    
}

void testVirtualPainter() 
{
    /*
    * - Detect màu sử dụng không gian HSV
    * - Dùng bounding method để tìm đường bao
    * - lấy x, y của bound và vẽ 1 vòng tròn
    */
    
    VideoCapture cap(0); //0: id source
    while (true) {
        cap.read(img);

        findColor(img);
        drawOnCanvas(newPoint, myColorValues);
        imshow("Image", img);
        waitKey(1); //mini-second, tăng số này lên video sẽ chậm hơn
    }
}
//--- end chapter 9 ---

int main() {

    string catImagePath = "Resources/cat.jpg";
    string videoPath = "Resources/test_video.mp4";
    string cardImagePath = "Resources/cards.jpg";
    string shapeImagePath = "Resources/shapes.png";
    string facePicturePath = "Resources/test.png";

    //Test chapter 1
    //open_image(catImagePath);
    //open_video(videoPath);
    //open_video_from_camera();

    //Test chapter 2
    //someBasicFunctionOnImage(catImagePath);

    //Test chapter 3
    //testResize(catImagePath);
    //testCrop(catImagePath);

    //Test chapter 4
    //drawShape();

    //Test chapter 5
    //testWarpImage(cardImagePath);

    //Test chapter 6
    //testColorDetection(shapeImagePath);

    //Test chapter 7
    //testShapesDetection(shapeImagePath);

    //Test chapter 8
    //testFaceDetection(facePicturePath);

    //Test chapter 9
    testVirtualPainter();
    
    return 0;
}