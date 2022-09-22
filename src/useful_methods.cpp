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
