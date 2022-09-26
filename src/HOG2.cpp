//
//  HOG2.cpp
//  DigitID
//
//  Created by Connor Jennings on 9/22/22.
//

#include "HOG2.hpp"

void HOG::calculateHog(){
    // create 9x1 histograms on 4x4 size sub-matricies
    // append each to base_histograms
    fourByFour();
    // normalize on 3x3 cells combining 9 of the 9x1 histograms into a 81x1 feature vector
    // append each 81x1 normalized feature vector onto the return vector a.k.a. "return_HOG"
    normalize3x3CellManager();
};

void HOG::fourByFour(){
    for(int startRow = 0; startRow < image.rows; startRow+=4){
        for(int startCol = 0; startCol < image.cols; startCol+=4 ){
            for(int row = 0; row < 4; ++row){
                std::vector<double> temp_hist(9,0);
                for(int col = 0; col < 4; ++col){
                    int gx = xGradientAt(row + startRow, col + startCol);
                    int gy = yGradientAt(row + startRow, col + startCol);
                    
                    //sort into buckets
                    int index = floor(angle(gx,gy)/20);
                    temp_hist[index] += magna((int)gx,(int)gy);
                }
                base_histograms.push_back(temp_hist);
            }
        }
    }
}

int HOG::xGradientAt(const int& row, const int& col){
    if(col == 0){ return (int)image.at<uchar>(row, col+1); }
    else if(col == image.cols-1){ return -(int)image.at<uchar>(row, col-1); }
    return (int)image.at<uchar>(row, col+1) - (int)image.at<uchar>(row, col-1);
}

int HOG::yGradientAt(const int& row, const int& col){
    if(row == 0){ return (int)image.at<uchar>(row+1, col); }
    else if(row == image.rows-1){ return -(int)image.at<uchar>(row-1, col); }
    return (int)image.at<uchar>(row-1, col) - (int)image.at<uchar>(row+1, col);
}

int HOG::magna(const int& x, const int& y){
    if(!x && !y) return 0;
    return abs((int)(sqrt(x*x + y*y)));
}

double HOG::angle(double x, double y){
    if(x == 0 ){ return 0;}
    double val = atan(y / x) * 180 / PI;
    if(val < 0){ val += 180;}
    if(val == -0){ val = 0;}
    return val;
}

void HOG::normalize3x3CellManager(){
    //block vector {0,1,2,7,8,9,14,15,16}
    //block vector {1,2,3,8,9,10,15,16,17}
    //...
    int slot1 = 0;
    int slot2 = 1;
    int slot3 = 2;
    int slot4 = 7;
    int slot5 = 8;
    int slot6 = 9;
    int slot7 = 14;
    int slot8 = 15;
    int slot9 = 16;
    for(int count = 0; count < 25; ++count, ++slot1, ++slot2, ++slot3, ++slot4){
        if(count % 4 == 0 && count != 0){
            ++slot1; ++slot2; ++slot3; ++slot4; ++slot5; ++slot6; ++slot7; ++slot8; ++slot9;
        }
        normalize3x3Cells(
                          base_histograms[slot1],
                          base_histograms[slot2],
                          base_histograms[slot3],
                          base_histograms[slot4],
                          base_histograms[slot5],
                          base_histograms[slot6],
                          base_histograms[slot7],
                          base_histograms[slot8],
                          base_histograms[slot9]
                          );
    }
}

void HOG::normalize3x3Cells(const std::vector<double>& v1, const std::vector<double>& v2, const std::vector<double>& v3, const std::vector<double>& v4, const std::vector<double>& v5, const std::vector<double>& v6, const std::vector<double>& v7, const std::vector<double>& v8, const std::vector<double>& v9){
    std::vector<double> temp;
    for(auto x : v1) temp.push_back(x);
    for(auto x : v2) temp.push_back(x);
    for(auto x : v3) temp.push_back(x);
    for(auto x : v4) temp.push_back(x);
    for(auto x : v5) temp.push_back(x);
    for(auto x : v6) temp.push_back(x);
    for(auto x : v7) temp.push_back(x);
    for(auto x : v8) temp.push_back(x);
    for(auto x : v9) temp.push_back(x);
    std::vector<double> temp2 = normalizeFeatureList(temp);
    for(auto x : temp2) return_HOG.push_back(x);
}

std::vector<double> HOG::normalizeFeatureList(std::vector<double> temp){
    if(temp.empty()) return std::vector<double>(81,0);
    long double k = 0;
    for(int x : temp) {
        k += (x * x);
    }
    if( k == 0){ return temp; }
    k = sqrt(k);
    for(int i = 0; i < temp.size(); ++i){
        temp[i] = temp[i] / k;
    }
    return temp;
}
