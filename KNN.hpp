//
//  KNN.hpp
//  DigitID
//
//  Created by Connor Jennings on 9/20/22.
//

#ifndef KNN_hpp
#define KNN_hpp
#include <vector>
#include <string>
#include <list>
#include "useful_methods.hpp"
#include "HOG.hpp"

std::vector<Answer> knn(list_of_params, const std::vector<number_hog>&);

double distance(const number_hog&, const number_hog&);

void list_insert(std::list<digit_dist>&, const digit_dist&);


#endif /* KNN_hpp */
