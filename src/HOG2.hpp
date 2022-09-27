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

    void calculateHog();
    
    int xGradientAt(const int&, const int&);
    int yGradientAt(const int&, const int&);
    int xSobel(const int&, const int&);
    int ySobel(const int&, const int&);
    int magna(const int&, const int&);
    double angle(double, double);

    
    std::vector<double> normalize3x3CellManager(std::vector<std::vector<double>>);
    std::vector<double> combine3x3Block(const std::vector<double>& v1,
                                        const std::vector<double>& v2,
                                        const std::vector<double>& v3,
                                        const std::vector<double>& v4,
                                        const std::vector<double>& v5,
                                        const std::vector<double>& v6,
                                        const std::vector<double>& v7,
                                        const std::vector<double>& v8,
                                        const std::vector<double>& v9);
    std::vector<std::vector<double>> fourByFour();
    std::vector<double> normalizeFeatureList(std::vector<double>);
    
    HOG();
    
public:
    HOG(const Mat img) : image(img){ calculateHog(); }
    
    std::vector<double> getHOG(){ return return_HOG; }
    
};

#endif /* HOG2_hpp */
