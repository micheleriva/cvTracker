#include "stdio.h"
#include "src/motion-detector.h"
#include "opencv2/opencv.hpp"

void detectMotion() {
    MotionDetector motionDetector;
    motionDetector.setCeil(15);
    motionDetector.openCamera();
    motionDetector.run();
}

int main(int argc, char* argv[]) {
    detectMotion();
    return 0;
}