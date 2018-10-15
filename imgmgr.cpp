#include "imgmgr.h"

ImgMgr::ImgMgr()
{
}

ImgMgr::ImgMgr(string imgName)
{
    name = imgName;
    nativeName = imgName;
    CreateTmpImg();
    image = imread(name);
}

void ImgMgr::CreateTmpImg()
{
    image = imread(nativeName);

    name = string("tmp_") + nativeName;
    imwrite(name.c_str(), image);
}

void ImgMgr::InitBinValues(uint16_t low = 70, uint16_t high = 170)
{
    binLow = low;
    binHigh = high;
}

vector<double> ImgMgr::GetBrightnessHistogram()
{
    vector<double> hist(256);

    for(uint32_t i = 0; i < image.rows; i++)
    {
        uchar* it = image.ptr(i);

        for(uint32_t j = 0; j < image.cols; j++)
        {
            uchar& pic = it[j];
            hist[pic]++;
        }
    }

    return hist;
}

void ImgMgr::ToGrayScale()
{
    if(!isGray)
    {
        cvtColor(image, image, COLOR_BGR2GRAY);
    }

    isGray = true;
}

void ImgMgr::ToBin()
{
    Mat bin_image = image.clone();

    for(uint32_t i = 0; i < bin_image.rows; i++)
    {
        uchar* it = bin_image.ptr(i);

        for(uint32_t j = 0; j < bin_image.cols; j++)
        {
            uchar& pic = it[j];
            if(pic < binLow)
            {
                pic = 0;
            }
            if(pic > binHigh)
            {
                pic = 255;
            }
        }
    }

    Show(bin_image);
    string bin_name = string("bin_") + nativeName;
    imwrite(bin_name, bin_image);
    bin_image.release();
}

void ImgMgr::Show(Mat im)
{
    namedWindow("My Image");
    imshow("My Image", im);
}

void ImgMgr::Save()
{
    imwrite(name.c_str(), image);
}

const char *ImgMgr::Name() const
{
    return name.c_str();
}
