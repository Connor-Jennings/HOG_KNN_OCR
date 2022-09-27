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
    std::vector<std::vector<double>> base_histo = fourByFour();
    // normalize on 3x3 cells combining 9 of the 9x1 histograms into a 81x1 feature vector
    // append each 81x1 normalized feature vector onto the return vector a.k.a. "return_HOG"
    return_HOG = normalize3x3CellManager(base_histo);
};

std::vector<std::vector<double>> HOG::fourByFour(){
    std::vector<std::vector<double>> base_histo;
    //for each block of 4x4 pixels
    for(int startRow = 0; startRow < image.rows; startRow+=4){
        for(int startCol = 0; startCol < image.cols; startCol+=4 ){
            
            //create a new histogram on that 4x4 block
            std::vector<double> temp_hist(9,0);
            for(int row = 0; row < 4; ++row){
                for(int col = 0; col < 4; ++col){
                    int gx = xGradientAt(row + startRow, col + startCol);
                    int gy = yGradientAt(row + startRow, col + startCol);
                    //sort into buckets
                    auto ori = angle(gx,gy);
                    int index = floor(ori/20);
                    temp_hist[index] += magna((int)gx,(int)gy);
                }
            }
            //add that histogram to the list of histograms until we have covered the whole image
            base_histo.push_back(temp_hist);
        }
    }
    return base_histo;
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

std::vector<double> HOG::normalize3x3CellManager(std::vector<std::vector<double>> base_histo){
    //block vector {0,1,2,7,8,9,14,15,16}
    //block vector {1,2,3,8,9,10,15,16,17}
    //...
    std::vector<double> return_vec;
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
        std::vector<double> block = combine3x3Block(base_histo[slot1],
                                                    base_histo[slot2],
                                                    base_histo[slot3],
                                                    base_histo[slot4],
                                                    base_histo[slot5],
                                                    base_histo[slot6],
                                                    base_histo[slot7],
                                                    base_histo[slot8],
                                                    base_histo[slot9]
                                                    );
        std::vector<double> normalized_block = normalizeFeatureList(block);
        for(auto x : normalized_block) return_vec.push_back(x);
    }
    return return_vec;
}

std::vector<double> HOG::combine3x3Block(const std::vector<double>& v1,
                            const std::vector<double>& v2,
                            const std::vector<double>& v3,
                            const std::vector<double>& v4,
                            const std::vector<double>& v5,
                            const std::vector<double>& v6,
                            const std::vector<double>& v7,
                            const std::vector<double>& v8,
                            const std::vector<double>& v9){
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
    return temp;
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




int HOG::xSobel(const int& row, const int& col){
    int top_row = 0;    // [1 0 -1]
    int middle_row = 0; // [2 0 -2]
    int bottom_row = 0; // [1 0 -1]
    
    //values of top_row
    if(row != 0){
        if(col == 0){
            top_row = -(int)image.at<uchar>(row-1, col+1);
        }else if(col == image.cols-1){
            top_row = (int)image.at<uchar>(row-1, col-1);
            
        }else{
            top_row = (int)image.at<uchar>(row-1, col-1) - (int)image.at<uchar>(row-1, col+1);
        }
    }
    
    //values of middle_row
    if(col == 0){
        middle_row = -2*(int)image.at<uchar>(row, col+1);
    }else if(col == image.cols-1){
        middle_row = 2*(int)image.at<uchar>(row, col-1);
    }else{
        middle_row = 2*(int)image.at<uchar>(row, col-1) - 2*(int)image.at<uchar>(row, col+1);
    }
    
    //vlaues of bottom_row
    if(row != image.rows-1){
        if(col == 0){
            bottom_row = -(int)image.at<uchar>(row+1, col+1);
        }else if(col == image.cols-1){
            bottom_row = (int)image.at<uchar>(row+1, col-1);
        }else{
            bottom_row = (int)image.at<uchar>(row+1, col-1) - (int)image.at<uchar>(row+1, col+1);
        }
    }
    
    return top_row + middle_row + bottom_row;
}
int HOG::ySobel(const int& row, const int& col){
    int left_column = 0;   // [1 0 -1]^T
    int middle_column = 0; // [2 0 -2]^T
    int right_column = 0;  // [1 0 -1]^T
    
    //values of left_column
    if(col != 0){
        if(row == 0){
            left_column = -(int)image.at<uchar>(row-1, col-1);
        }else if(row == image.rows-1){
            left_column = (int)image.at<uchar>(row+1, col-1);
        }else{
            left_column = (int)image.at<uchar>(row+1, col-1) - (int)image.at<uchar>(row-1, col-1);
        }
    }
    
    //values of middle_column
    if(row == 0){
        middle_column = -2*(int)image.at<uchar>(row+1, col);
    }else if(row == image.rows-1){
        middle_column = 2*(int)image.at<uchar>(row-1, col);
    }else{
        middle_column = 2*(int)image.at<uchar>(row-1, col) - 2*(int)image.at<uchar>(row+1, col);
    }
    
    //vlaues of right_column
    if(col != image.cols-1){
        if(row == 0){
            right_column = -(int)image.at<uchar>(row+1, col+1);
        }else if(row == image.rows-1){
            right_column = (int)image.at<uchar>(row-1, col+1);
        }else{
            right_column = (int)image.at<uchar>(row-1, col+1) - (int)image.at<uchar>(row+1, col+1);
        }
    }
    
    return left_column + middle_column + right_column;
}


