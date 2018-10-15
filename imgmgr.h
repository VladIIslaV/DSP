#ifndef IMGMGR_H
#define IMGMGR_H

#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <string>
#include <vector>

using namespace std;

using namespace cv;


class ImgMgr
{
    Mat image;
    string nativeName;
    string name;

    bool isGray;

    // For image binarization
    // WHITE < binLow     binHigh > BLACK
    uint16_t binLow;
    uint16_t binHigh;
public:
    ImgMgr();
    ImgMgr(string);
    void CreateTmpImg();
    void InitBinValues(uint16_t low, uint16_t high);

    vector<double> GetBrightnessHistogram();

    void ToGrayScale();
    void ToBin();

    void Show(Mat im);
    void Save();
    const char* Name() const;
};

#endif // IMGMGR_H
