#include <iostream>
#include <vector>

#include "HOG.hpp"
#include "KNN.hpp"
#include "useful_methods.hpp"

int main(){
    std::cout << "Program Started..." << std::endl;
    list_of_params params = {
        .k = 3,
        .train = {0,1,2,3,4,5,6,7,8,9},
        .reps = 500,
        .test_cases = 100
    };
    std::vector<number_hog> trained_model = train(params);
    std::vector<Answer> results = knn(params, trained_model);
    output(results);
    std::cout << "Reached End Of Main. " << std::endl;
    
    return 0;
}
