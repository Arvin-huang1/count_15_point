#pragma once
#ifndef COUNT_15_POINT_AREA_H
#define COUNT_15_POINT_AREA_H

#include<iostream>
#include <fstream>    
#include <string>
#include <cassert>
#include <iomanip>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int cal_15_point_area(string file_path, string img_path, string save_img_path);

#endif
