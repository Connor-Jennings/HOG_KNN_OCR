#include <iostream>
#include <vector>

#include "HOG2.hpp"
#include "KNN2.hpp"
#include "useful_methods.hpp"


int main(){
    std::cout << "Program Started..." << std::endl;
    list_of_params params ={
        .k = 3,
        .train = {0,1,2,3,4,5,6,7,8,9},
        .reps = 2000,
        .test_cases = 10
    };

    // create a list of Histogram of Oriented Gradients for training images
    std::vector<number_hog>* trained_model = new std::vector<number_hog>;
    
    for(auto number_selected : params.train)
    {
        for(int file_number = 1; file_number <= params.reps; ++file_number)
        {
            HOG hog( getImg(number_selected,file_number,false) );
            
            //check for correct size
            auto hog_val = hog.getHOG();
            if(hog_val.size() != 2025){
                std::cout << "HOG not correct size! continuing to next image." << std::endl;
            }else{
                trained_model->push_back((number_hog){.digit = number_selected,.HOG = hog_val});
            }
        }
    }
    
    std::cout << "----Done Training----" << std::endl;
    if(params.test_cases == 0) { return 0;}
    
   
    // set K-nearest neighbors obj with list of HOGs
    KNN knn;
    knn.setK(params.k);
    knn.setModel(trained_model);
  
    // use KNN obj to classify images
    for(auto number_selected : params.train)
    {
        std::cout << " Testing : " << number_selected << std::endl;
        for(int file_number = 1; file_number <= params.test_cases; ++file_number)
        {
            HOG hog(getImg(number_selected,file_number,true));
            bool correct = knn.classify((number_hog){.digit = number_selected, .HOG = hog.getHOG()});
            if(!correct){ std::cout << "File: " << fileName(number_selected,file_number, true) << std::endl ;}
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    // clean up
    delete trained_model;
    
    // output how accurate the results are
    output(params, knn.getResults());
    std::cout << "Reached End Of Main. " << std::endl;
    return 0;
}
