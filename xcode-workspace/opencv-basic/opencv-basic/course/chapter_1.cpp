//
//  chapter_1.cpp
//  opencv-basic
//
//  Created by Ngo Thai on 03/03/2021.
//

#include "chapter_1.hpp"


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
