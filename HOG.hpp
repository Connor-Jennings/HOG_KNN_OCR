//
//  HOG.hpp
//  DigitID
//
//  Created by Connor Jennings on 9/20/22.
//

#ifndef HOG_hpp
#define HOG_hpp
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <utility>

#include "useful_methods.hpp"


using namespace cv;


std::vector<number_hog> train(const list_of_params&);

number_hog hog(const short int&, const int&, bool);

std::vector<int> hogMath(const Mat& image);

std::vector<int> histogramCreator(const short int&, const short int&, const Mat&, const Mat&);

void pushOntoHistogram(const short int&, const short int&, std::vector<int>&);

std::vector<int> normalize(const std::vector<std::vector<std::vector<int>>>&);

void normalizeHistogram(std::vector<int>& );

#endif /* HOG_hpp */
