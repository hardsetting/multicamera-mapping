#include <iostream>
#include <opencv2/opencv.hpp>

#include "MappedImage.h"
#include "Plan.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    Size mapSize(800, 900);
    Point2f centerOffset(100, 100);
    auto dstPoints = parsePoints("data/dstPoints.txt");

    vector<MappedImage> mimgs;
    mimgs.emplace_back("data/pic1.jpg", "data/srcPoints1.txt", dstPoints);
    mimgs.emplace_back("data/pic2.jpg", "data/srcPoints2.txt", dstPoints);
    mimgs.emplace_back("data/pic3.jpg", "data/srcPoints3.txt", dstPoints);

    Mat birdView = mimgs[0].birdView(mapSize, centerOffset);
    Plan plan(birdView, centerOffset);
    for(const auto& p : dstPoints) {
        plan.drawCircle(p);
    }

    auto pos1 = mimgs[0].pixelToCoord(Point2f(387, 533));
    auto pos2 = mimgs[1].pixelToCoord(Point2f(662, 345));
    auto pos3 = mimgs[2].pixelToCoord(Point2f(819, 573));

    plan.drawCircle(pos1, Scalar(255, 255, 0));
    plan.drawCircle(pos2, Scalar(0, 255, 0));
    plan.drawCircle(pos3, Scalar(0, 0, 255));

    imshow("Plan", plan.img());
    waitKey();

    return 0;
}