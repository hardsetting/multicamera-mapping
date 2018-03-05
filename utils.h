#pragma once

#include <opencv2/opencv.hpp>
#include <fstream>

using namespace std;
using namespace cv;

vector<Point2f> parsePoints(const string& filename) {
    vector<Point2f> points;
    ifstream in(filename);

    int x, y;
    while(in >> x >> y) {
        points.push_back(Point2f(x, y));
    }

    return points;
}