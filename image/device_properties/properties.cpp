#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

#define NUM_CAMERAS 1

void getCameraProperties(int deviceIndex) {
    // Open the camera
    VideoCapture cap(deviceIndex);
    
    if (!cap.isOpened()) {
        std::cerr << "Error: Unable to open camera " << deviceIndex << std::endl;
        return;
    }

    // Retrieve camera properties
    double width = cap.get(CAP_PROP_FRAME_WIDTH);
    double height = cap.get(CAP_PROP_FRAME_HEIGHT);
    double fps = cap.get(CAP_PROP_FPS);
    double fourcc = cap.get(CAP_PROP_FOURCC);
    
    // Output camera properties
    std::cout << "Camera " << deviceIndex << " Properties:" << std::endl;
    std::cout << "  - Resolution: " << width << "x" << height << std::endl;
    std::cout << "  - FPS: " << fps << std::endl;
    std::cout << "  - FourCC Code: " << fourcc << std::endl;
    std::cout << std::endl;

    cap.release(); // Release the camera after getting properties
}

int main() {
    int deviceIndex = 0;  // Starting device index

    // Loop through possible devices (You can adjust this based on the number of devices connected)
    while (true) {
        std::cout << "Checking camera " << deviceIndex << "..." << std::endl;
        getCameraProperties(deviceIndex);


        deviceIndex++;  // Check the next camera
        
        // Exit if no more cameras are available (adjust number of cameras based on your setup)
        if (deviceIndex >= NUM_CAMERAS) {
            break;  // Exit after checking up to 3 cameras
        }
    }

    return 0;
}

