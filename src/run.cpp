#include <vector>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imagecodecs.hpp>
#include <opencv2/objdetect.hpp>

auto import_webcam() -> void;

int main()
{
    import_webcam();
    return 1;
}

auto import_webcam() -> void
{
    cv::VideoCapture cap(0);
    cv::Mat img;
    while (true)
    {
        cap.read(img);
        cv::imshow("Webcam", img);
        cv::waitKey(1);
    }
    
}