#ifndef CVTRACKER_UTILITY_H
#define CVTRACKER_UTILITY_H

#include "opencv2/opencv.hpp"
#include <thread>
#include <stdio.h>

#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif

namespace utility {

    inline CvCapture * createCapture(const char * videoPath) {
        if(videoPath != nullptr) {
            return cvCreateFileCapture(videoPath);
        } else {
            return cvCreateCameraCapture(CV_CAP_ANY);
        }
    }

    inline const char * currentDirectory() {

        char currentPath[FILENAME_MAX];

        if(!GetCurrentDir(currentPath, sizeof(currentPath))){
            return nullptr;
        }

        currentPath[sizeof(currentPath) - 1] = '\0';
        std::string path(currentPath);

        return path.c_str();
    }

    inline void replaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace) {

        size_t pos = 0;

        while((pos = subject.find(search, pos)) != std::string::npos) {
            subject.replace(pos, search.length(), replace);
            pos += replace.length();
        }
    }

    inline void sleep(int seconds) {
        std::chrono::milliseconds timespan(seconds);
        std::this_thread::sleep_for(timespan);
    }
}

namespace visionary {

    inline void drawRectangle(std::vector<cv::Rect>::iterator it, IplImage *image, CvScalar scalarColor) {

        cv::Rect rect = *it;

        CvPoint point1;
        point1.x = rect.x;
        point2.y = rect.y;

        CvPoint point2;
        point2.x = rect.x;
        point2.y = rect.y;

        cvRectangle(image,  point1, point2, scalarColor, 2):
    }

    inline void setCaptureFrame(CvCapture *capture, double width, double height) {
        cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, width);
        cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, height);
    }
}

#endif //CVTRACKER_UTILITY_H
