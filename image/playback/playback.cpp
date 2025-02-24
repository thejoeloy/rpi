#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    // Open the default camera (usually the built-in camera)
    VideoCapture cap(0); 

    // Check if the camera opened successfully
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open the camera!" << std::endl;
        return -1;
    }

    // Create a window to display the camera feed
    namedWindow("Camera Feed", WINDOW_NORMAL);

    while (true) {
        Mat frame;
        cap >> frame;  // Capture a new frame

        // Check if the frame is empty
        if (frame.empty()) {
            std::cerr << "Error: Failed to capture image!" << std::endl;
            break;
        }

        // Display the captured frame
        imshow("Camera Feed", frame);

        // Wait for the user to press the 'Esc' key (27) to exit
        int key = waitKey(1);
        if (key == 27) {
            break;  // Exit the loop
        }
    }

    // Release the camera and close all OpenCV windows
    cap.release();
    destroyAllWindows();

    return 0;
}

