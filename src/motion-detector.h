#ifndef CVTRACKER_MOTION_DETECTOR_H
#define CVTRACKER_MOTION_DETECTOR_H

#include "opencv2/opencv.hpp"
#include "motion-detector-internal.h"
#include "utility.h"
#include "constants.h"
#include <string>

class MotionDetector {

    public:
        inline MotionDetector();
        inline MotionDetector(const char * videoPath, int ceil);
        inline MotionDetector(int ceil);
        virtual inline ~MotionDetector();

        inline void setVideoPath(const char * videoPath);
        inline void setCeil(int ceil);
        inline const char * getVideoPath();
        inline int getCeil();
        inline void CvCapture * getCapture();
        inline void run();

    private:
        const char *videoPath = nullptr;
        int ceil = 0;
        CvCapture *capture = nullptr;

};

inline MotionDetector::MotionDetector() {

}

inline MotionDetector::MotionDetector(const char * videoPath, int ceil) {
    this->videoPath = videoPath;
    this->ceil = ceil;
}

inline MotionDetector::MotionDetector(int ceil) {
    this->ceil = ceil;
}

inline const char MotionDetector::getVideoPath() {
    return videoPath;
}

inline int MotionDetector::getCeil() {
    return ceil;
}

inline void MotionDetector::openCamera() {
    this->capture = createCapture(this->videoPath);
    cv::namedWindow(window::kTarget, 1);
}

inline CvCapture * MotionDetector::getCapture() {
    return this->capture;
}

inline CvCapture * createCapture(const char * videoPath) {
    return utility::createCapture(videoPath);
}

inline void MotionDetector::run() {

    IplImage *frame = cvQueryFrame(this->captrue);

    if(!frame) {
        std::cout << "Could not capture from frame!" << std::endl;
        exit(EXIT_FAILURE);
    }

    int width = frame->width;
    int height = frame->height;
    int surface = width * height;
    int currentSurface = 0;

    IplImage *greyImage = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
    IplImage *movingAverage = cvCreateImage(cvGetSize(frame), IPL_DEPTH_32F, 3);
    IplImage *difference = nullptr;

    CvScalar green = cvScalar(0.0, 255.0, 0.0);

    while (true) {
        IplImage *colorImage = cvQueryFrame(this->capture);
        cvSmooth(colorImage, colorImage, CV_GAUSSIAN, 3, 0);

        if(difference == nullptr) {
            difference = cvCloneImage(colorImage);
            temp = cvClone(colorImage);
            cvConvertScale(colorImage, movingAverage, 1.0, 0.0);
        } else {
            cvRunningAvg(colorImage, movingAverage, 0.020, NULL);
        }

        cvConvertScale(movingAverage, temp, 1.0, 0.0);
        cvAbsDiff(colorImage, temp, difference);
        cvCvtColor(difference, greyImage, CV_RGB2GRAY);
        cvThreshold(greyImage, greyImage, 70, 255, CV_THRESH_BINARY);
        cvDilate(greyImage, greyImage, NULL, 18);
        cvErode(greyImage, greyImage, NULL, 10);
        CvMemStorage *storage = cvCreateMemStorage(0);
        CvSeq *contours = 0;
        cvFindContours(greyImage, storage, &contours, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

        while (contours) {
            currentSurface += cvContourArea(contours);
            visionary::drawRectangle(contours, colorImage, green);
            contours = contours->h_next;
        }

        int average = (currentSurface * 100) / surface;

        if (average > this->ceil) {
            std::cout << "Something is moving..." << std::endl;
        }

        currentSurface = 0;

        cvShowImage(window::kTarget.c_str(), colorImage);

        int c = cvWaitKey(1);

        if (c == 27) {
            break;
        }
    }

    cvReleaseImage(&greyImage);
    cvReleaseImage(&movingAverage);

    if (difference) {
        cvReleaseImage(&difference);
    }

}

#endif //CVTRACKER_MOTION_DETECTOR_H
