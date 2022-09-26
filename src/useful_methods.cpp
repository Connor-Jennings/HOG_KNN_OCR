//
//  useful_methods.cpp
//  DigitID
//
//  Created by Connor Jennings on 9/20/22.
//

#include "useful_methods.hpp"



std::string fileName(const short int& number_selected, const int& file_number, bool test){
    std::string parentfolder;
    if(!test){
        parentfolder = "/Users/connorjennings/Code/KNNproject/data/mnist_png/mnist_png/training";
    }else{
        parentfolder = "/Users/connorjennings/Code/KNNproject/data/mnist_png/mnist_png/testing";
    }
    std::string subfile = parentfolder + "/" + std::to_string(number_selected) + "/img" ;
    if(number_selected > 9 || file_number > 4602){
        return "-1";
    }
    if(file_number < 9){
        subfile += "0000"+ std::to_string(file_number+1)+ ".png";
    }
    else if(file_number < 99){
        subfile += "000"+ std::to_string(file_number+1)+ ".png";
    }
    else if(file_number < 999 ){
        subfile += "00"+ std::to_string(file_number+1)+ ".png";
    }
    else {
        subfile += "0"+ std::to_string(file_number+1)+ ".png";
    }
    return subfile;
}


void output(const std::vector<Answer>& results){
    std::cout << " ---------\n| Results |\n ---------" << std::endl;
    int correct = 0;
    int total = 0;
    for(auto x : results){
        std::cout << x << std::endl;
        correct += x.getCorrect();
        total += x.getTotal();
    }
    if(total == 0 ){
        std::cout << "Total : " << correct << " / " << total <<  std::endl;
    }else{
        std::cout << "Total : " << correct << " / " << total << " or " << (double)correct/total * 100 << " %" << std::endl;

    }
}

Mat getImg(const short int& number_selected, const int& file_number, bool test){
    auto file = fileName(number_selected, file_number, test);
    if(file == "-1"){
        Mat emptyMat;
        return emptyMat;
    }
    // get image and resize
    Mat img;
    
    img = imread(file, 0); //read in grayscale
    /*for(int i =0; i < img.cols; ++i){
        for(int j = 0; j < img.rows; ++j){
            std::cout << (int)img.at<uchar>(i,j) << " ";
        }
        std::cout << std::endl;
    }*/
    if(img.empty()){
        std::cout << "Could not read the image "  << std::endl;
        Mat emptyMat;
        return emptyMat;
    }
    return img;
}

void print_list(const std::list<digit_dist>& lst){
    for (auto it = lst.begin(); it != lst.end(); ++it){
        std::cout << "(" << (*it).digit << "|" << (*it).dist << ")";
    }
    std::cout << std::endl;
}
