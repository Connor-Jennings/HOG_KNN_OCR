//
//  HOG.cpp
//  DigitID
//
//  Created by Connor Jennings on 9/20/22.
//
#include "HOG.hpp"
#include <typeinfo>


std::vector<number_hog> train(const list_of_params& params){
    
    std::vector<number_hog> results;
    
    // for each number we want to identify we will train params.testcases # of photos into the model
    for(auto x : params.train){
        for(int i = 0; i < params.reps; ++i){
            auto result = hog(x,i, false);
            if(result.number == -1) {
                std::cout << " error reading file ";
                return results;
            }
            results.push_back(result);
        }
    }
    return results;
}
    

number_hog hog(const short int& number_selected, const int& file_number, bool flag){
    number_hog result = {.number = number_selected};
    
    // get file path
    auto file = fileName(number_selected, file_number, flag);
    if(file == "-1"){
        result.number = -1;
        return result;
    }
    
    // get image and resize
    Mat img;
    const int down_width = 64;
    const int down_height = 128;
    
    img = imread(file, IMREAD_COLOR);
    if(img.empty()){
        std::cout << "Could not read the image "  << std::endl;
        result.number = -1;
        return result;
    }
    auto it = img.begin<uchar>();
    auto it_end = img.end<uchar>();

    std::cout << img.size() <<  std::endl;
    std::vector<std::string> vals;
    int count=0;
    int col = 0;
    for(; it != it_end; ++it, ++count){
        if(col>= 28){ col = 0;}
        if(count >= 28){
            count = 0;
            std::cout << std::endl;
        }
        std::cout << (int)*it << " ";
        if((int)*it > 0 ){
            vals.push_back("row " + std::to_string(count) + ", col " + std::to_string(col) + "val = " + std::to_string((int)*it));
            
        }
        ++col;
    }
    std::cout << std::endl;
    for(auto x: vals){
        std::cout << x << std::endl;
    }
    imshow("windo", img);
    int k = waitKey(0);
    /*Mat gx, gy, abs_gx, abs_gy;
    Sobel(img, gx, CV_8U, 1, 0);
    Sobel(img, gy, CV_8U, 0, 1);
    convertScaleAbs(gx, abs_gx);
    convertScaleAbs(gy, abs_gy);
    auto it1 = gx.begin<uchar>();
    auto it1_end = gx.end<uchar>();
    
    count=0;
    for(; it1 != it1_end; ++it1, ++count){
        if(count >= 28){
            count = 0;
            std::cout << std::endl;
        }
        std::cout << (int)*it1 << " ";
    }
    auto it2 = gy.begin<uchar>();
    auto it2_end = gy.end<uchar>();
    count=0;
    for(; it2 != it2_end; ++it2, ++count){
        if(count >= 28){
            count = 0;
            std::cout << std::endl;
        }
        std::cout << (int)*it2 << " ";
    }
    //imshow("original", img);
    resize(img, img, Size(down_width, down_height), INTER_LINEAR);
    //imshow("DISTORt", img);
    //int key = waitKey(0);
    
    */
    
    
    //get Histogram of Oriented Gradients on 64x128px image (hogMath designed with this scale in mind)
    result.HOG = hogMath(img);
    //auto x = hogMath2(resized_down);
    return result;
}


std::vector<int> hogMath2(const Mat& image){
    // calculate the Gradients (direction x and y)
    std::vector<int> histogram(9);
    std::vector<std::vector<std::vector<int>>> histogram_list(16);
   
    int level = 0;
    for(int range1 = 0; range1 <= image.rows-8; range1+=8){ //121
        for(int range2 = 0; range2 <= image.cols-8; range2+=8){ //56
            histogram.clear();
            for(int row = range1; row < range1 + 8; ++row ){
                for(int col = range2; col < range2 + 8; ++col ){
                    //std::cout << "range1: " << range1 << " range2: " << range2 << " row: " << row << " col: " <<col << std::endl;
                    std::pair<int,int> par = values(row, col, image);
                    pushOntoHistogram(par.first, par.second, histogram);
                }
            }
            //std::cout << "------------------------------" << std::endl;
            //histogram_list[level].push_back(histogram);
        }
        //++level;
        //std::vector<std::vector<int>> temp;
        //histogram_list.push_back(temp);
    }
    return normalize(histogram_list);
}
        

std::pair<int,int> values(const int& row, const int& col, const Mat& image){
    int gx = 0, gy = 0;
    unsigned char *input = (unsigned char*)(image.data);
    if(row == 0 &&  col == 0){
        gx = image.at<uchar>(Point(0,1));
        gy -= image.at<uchar>(Point(1,0));
    }else{
        //gx
        if(col == image.cols - 1){
            gx -= image.at<uchar>(Point(row,col-1));
        }else if(col == 0){
            gx = image.at<uchar>(Point(row,col+1));
        }else{
            gx = image.at<uchar>(Point(row,col+1)) - image.at<uchar>(Point(row,col-1));
        }
        //gy
        if(row == image.rows - 1){
            gy = image.at<uchar>(Point(row-1,col));
        }else if(row == 0){
            gy -= image.at<uchar>(Point(row+1,col));
        }else{
            gy = image.at<uchar>(Point(row-1,col-1)) - image.at<uchar>(Point(row+1,col));
        }
    }
    return std::make_pair(gx,gy);
}








std::vector<int> hogMath(const Mat& image){
    
    std::vector<std::vector<std::vector<int>>> histogram_list(16);

    // calculate the Gradients (direction x and y)
    Mat gx, gy, abs_gx, abs_gy;
    Sobel(image, gx, CV_16S, 1, 0);
    Sobel(image, gy, CV_16S, 0, 1);
    convertScaleAbs(gx, abs_gx);
    convertScaleAbs(gy, abs_gy);

    
    // calculate the Magnitude and Orientation
    int level = 0;
    for(short int range1 = 0; range1 <= 121; range1+=8){ //121
        for(short int range2 = 0; range2 <= 56; range2+=8){ //56
            histogram_list[level].push_back(histogramCreator(range1, range2, abs_gx, abs_gy));
        }
        ++level;
    }
    
    // normalize gradients in 16x16 cell (36x1) and combine
    return normalize(histogram_list);
}


std::vector<int> histogramCreator(const short int& range1, const short int& range2, const Mat& gx, const Mat& gy){
    std::vector<int> histogram(9);
    for(int x = range1; x <= range1 + 7; ++x ){
        for(int y = range2; y <= range2 + 7; ++y ){
            const short int gx_val =  gx.at<uchar>(Point(x, y));
            const short int gy_val =  gy.at<uchar>(Point(x, y));
            pushOntoHistogram(gx_val, gy_val, histogram);
        }
    }
    return histogram;
}


void pushOntoHistogram(const short int& gx_val, const short int& gy_val, std::vector<int>& histogram){
    // create a histogram using the gradients ond orientation
    if(!gx_val && !gy_val) return;
    double magnitude = sqrt(pow(gx_val,2) + pow(gy_val, 2));
    double orientation;
    if(gx_val == 0 ){
        orientation = 0;
    }else{
        orientation = atan(gy_val/gx_val) * 180 / 3.14159265;
    }
    int index = orientation/20;
    histogram[index] += magnitude;
}


std::vector<int> normalize(const std::vector<std::vector<std::vector<int>>>& histogram_list){
    std::vector<int> return_list;
    std::vector<int> normalized_vector;
    if(histogram_list.empty()) return return_list;
    
    // combine four 9x1 histograms for a single 36x1 matrix
    // noramlize each of these k = sqrt(a1^2 + ... + a36^2)
    // normalized vector  = (a1/k , a2/k, a3/k ,..., a36/k)
    // go to the next column by one and create a new block of four 9x1 histograms
    // then shift down one row when reach the end
    // return 105 36x1 histograms
    for(int row = 0; row < histogram_list.size()-1; ++row){
        for(int column = 0; column < histogram_list[row].size()-1; ++column){
            for(auto x : histogram_list[row][column]) normalized_vector.push_back(x);
            for(auto x : histogram_list[row+1][column]) normalized_vector.push_back(x);
            for(auto x : histogram_list[row][column+1]) normalized_vector.push_back(x);
            for(auto x : histogram_list[row+1][column+1]) normalized_vector.push_back(x);
            normalizeHistogram(normalized_vector);
            for(auto x : normalized_vector) return_list.push_back(x);
            normalized_vector.clear();
        }
    }
    return return_list;
}

void normalizeHistogram(std::vector<int>& normalized_vector){
    if(normalized_vector.empty()) return;
    double k = 0;
    for(auto x : normalized_vector) k += pow(x,2);
    if(k != 0){ k = sqrt(k); }
    for(int i = 0; i < normalized_vector.size(); ++i){
        normalized_vector[i] = (int)(normalized_vector[i] / k);
    }
}
