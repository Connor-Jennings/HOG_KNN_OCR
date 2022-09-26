#include <iostream>
#include <vector>

#include "HOG2.hpp"
#include "KNN2.hpp"
#include "useful_methods.hpp"


int main(){
    std::cout << "Program Started..." << std::endl;
    list_of_params params = {
        .k = 3,
        .train = {0,1,2,3,4,5,6,7,8,9},
        .reps = 500,
        .test_cases = 5
    };
    
    // create a list of Histogram of Oriented Gradients for training images
    std::vector<number_hog> trained_model;
    for(auto number_selected : params.train){
        for(int file_number = 1; file_number <= params.reps; ++file_number){
            HOG hog(getImg(number_selected,file_number,false));
            
            bool all_zero = true;
            for(auto x : hog.getHOG()){
                if(x != 0) all_zero = false;
            }
            
            if(!all_zero){
                trained_model.push_back((number_hog){
                                            .digit = number_selected,
                                            .HOG = hog.getHOG()
                                        });
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
    for(auto number_selected : params.train){
        std::cout << " Testing : " << number_selected << std::endl;
        for(int file_number = 1; file_number <= params.test_cases; ++file_number){
            HOG hog(getImg(number_selected,file_number,true));
            knn.classify((number_hog){.digit = number_selected, .HOG = hog.getHOG()});
        }
    }
    std::cout << std::endl;
    
    // output how accurate the results are
    auto result = knn.getResults();
    output(result);
    std::cout << "Reached End Of Main. " << std::endl;
    return 0;
}
