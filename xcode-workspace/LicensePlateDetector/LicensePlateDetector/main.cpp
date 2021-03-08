//
//  main.cpp
//  LicensePlateDetector
//
//  Created by Ngo Thai on 08/03/2021.
//

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/objdetect.hpp>

using namespace cv;
using namespace std;


///////////////// Webcam //////////////////////

int main() {
    
    VideoCapture cap(0);
    Mat img;
    
    CascadeClassifier plateCascade;
    plateCascade.load("Resources/haarcascade_russian_plate_number.xml");
    // Check xem load được hay không
    if (plateCascade.empty())
    {
        cout << "XML file is not loaded" << endl;
    }
    
    // Detect face và lưu trong 1 bounding box
    vector<Rect> plates;
    
    while (true) {
        
        cap.read(img);
        
        plateCascade.detectMultiScale(img, plates, 1.1, 10);
        
        for (int i = 0; i < plates.size(); i++)
        {
            rectangle(img, plates[i].tl(), plates[i].br(), Scalar(231, 76, 60), 2);
        }
        
        imshow("Image", img);
        waitKey(1);
        
    }
    return 0;
}
