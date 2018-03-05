#pragma once

#include <opencv2/opencv.hpp>
#include "utils.h"

using namespace std;
using namespace cv;

class MappedImage {
    Mat _img;
    Mat _H;

public:
    MappedImage(const string& filename, const vector<Point2f>& srcPoints, const vector<Point2f>& dstPoints) {
        _img = imread(filename, IMREAD_COLOR);
        _H = findHomography(srcPoints, dstPoints, cv::RANSAC);
    }

    MappedImage(const string& filename, const string& srcPointsFilename, const vector<Point2f>& dstPoints) {
        _img = imread(filename, IMREAD_COLOR);
        auto srcPoints = parsePoints(srcPointsFilename);
        _H = findHomography(srcPoints, dstPoints, cv::RANSAC);
    }

    Point2f pixelToCoord(const Point2f& srcPoint) {
        vector<Point2f> srcPoints {srcPoint};
        vector<Point2f> dstPoints(1);

        perspectiveTransform(srcPoints, dstPoints, _H);
        return dstPoints[0];
    }

    Mat birdView(Size size = Size(), Point2f offset = Point2f()) const {
        size = size.empty() ? _img.size() : size;

        // Compute translation matrix
        Mat Ht = Mat::eye(3, 3, CV_64F);
        Ht.at<double>(0, 2) = offset.x;
        Ht.at<double>(1, 2) = offset.y;

        // Chain transforms
        Mat H = Ht * _H;

        // Apply perspective transform
        Mat out;
        warpPerspective(_img, out, H, size);

        // Invert y axis
        flip(out, out, 0);

        return out;
    }

    Mat& img() { return _img; }
};