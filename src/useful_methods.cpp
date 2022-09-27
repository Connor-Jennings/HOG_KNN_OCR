//
//  useful_methods.cpp
//  DigitID
//
//  Created by Connor Jennings on 9/20/22.
//

#include "useful_methods.hpp"



std::string fileName(const short int& number_selected, const int& file_number, bool weAreTesting){
    std::string parentfolder;
    if(weAreTesting){
        parentfolder = "/Users/connorjennings/Code/KNNproject/data/mnist_png/mnist_png/testing";
    }else{
        parentfolder = "/Users/connorjennings/Code/KNNproject/data/mnist_png/mnist_png/training";
    }
    std::string subfile = parentfolder + "/" + std::to_string(number_selected) + "/img" ;
    if(number_selected > 9){
        return "-1";
    }
    if(file_number > 4602){
        return "-1";
    }
    if(file_number > 500 && weAreTesting){
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


void output(const list_of_params& params, const std::vector<Answer>& results){
    std::cout << " ---------\n| Results |\n ---------" << std::endl;
    std::cout << "( k: "<< params.k <<  ", Reps: " << params.reps << " )"<< std::endl;
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
    std::string file = fileName(number_selected, file_number, test);
    if(file == "-1"){
        std::cout << "empyt mat" <<std::endl;
        Mat emptyMat;
        return emptyMat;
    }
    // get image and resize
    Mat img;
    
    img = imread(file, 0); //read in grayscale
 
    if(img.empty()){
        std::cout << "Could not read the image "  << std::endl;
        Mat emptyMat;
        return emptyMat;
    }
    return img;
}

Mat getImg(std::string fileName){
    if(fileName == "-1"){
        std::cout << "empyt mat" <<std::endl;
        Mat emptyMat;
        return emptyMat;
    }
    // get image and resize
    Mat img = imread(fileName, 0); //read in grayscale
   
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
