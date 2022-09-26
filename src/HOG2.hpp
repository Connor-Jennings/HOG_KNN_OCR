//
//  HOG2.hpp
//  DigitID
//
//  Created by Connor Jennings on 9/22/22.
//

#ifndef HOG2_hpp
#define HOG2_hpp
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <utility>

#include "useful_methods.hpp"
using namespace cv;

constexpr double PI = 3.141592653589793238;


class HOG{
    const Mat image;
    std::vector<double> return_HOG;
    std::vector<std::vector<double>> base_histograms;
    std::vector<std::vector<double>> block_list;

    void calculateHog();
    void fourByFour();
    int xGradientAt(const int&, const int&);
    int yGradientAt(const int&, const int&);
    int magna(const int&, const int&);
    double angle(double, double);

    
    void normalize3x3CellManager();
    void normalize3x3Cells(const std::vector<double>&, const std::vector<double>&, const std::vector<double>&, const std::vector<double>&, const std::vector<double>&, const std::vector<double>&, const std::vector<double>&, const std::vector<double>&, const std::vector<double>&);
    std::vector<double> normalizeFeatureList(std::vector<double>);

    
    HOG();
    
public:
    HOG(const Mat& img) : image(img){ calculateHog(); }
    
    std::vector<double> getHOG(){ return return_HOG; }
    //void setImage(const Mat& value){ image = value; }
    void recalculate() { calculateHog(); }
    
};

#endif /* HOG2_hpp */
