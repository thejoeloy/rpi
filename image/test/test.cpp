#include <string.h>
#include <opencv2/opencv.hpp>

using namespace cv;
int main() {
    std::string image_path = "king.jpg";
    Mat img = imread(image_path, IMREAD_COLOR);

    imshow("Display window", img);
    int k = waitKey(0);
    return 0;
}
