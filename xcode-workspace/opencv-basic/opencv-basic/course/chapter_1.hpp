//
//  chapter_1.hpp
//  opencv-basic
//
//  Created by Ngo Thai on 03/03/2021.
//

#ifndef chapter_1_hpp
#define chapter_1_hpp

#include <stdio.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void open_image(string path);
void open_video(string path);
void open_video_from_camera();

#endif /* chapter_1_hpp */
