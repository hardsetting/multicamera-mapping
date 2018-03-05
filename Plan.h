#pragma once

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Plan {
    Mat _img;
    Point2f _offset;

    Point2f coordToColRow(const Point2f& pos) {
        return Point2f(pos.x, _img.rows - pos.y);
    }

public:
    Plan(const Size& size, const Point2f& offset) {
        _img = Mat::zeros(size, CV_8UC3);
        _offset = offset;
    }

    Plan(const Mat& img, const Point2f& offset) {
        _img = img.clone();
        _offset = offset;
    }

    void drawCircle(const Point2f& point, const Scalar& color = Scalar(255, 255, 255), int radius = 10) {
        cv::circle(_img, coordToColRow(point + _offset), radius, color);
    }

    Mat& img() { return _img; }
};
