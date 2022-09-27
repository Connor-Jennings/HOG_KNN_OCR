//
//  KNN2.hpp
//  DigitID
//
//  Created by Connor Jennings on 9/22/22.
//

#ifndef KNN2_hpp
#define KNN2_hpp
#include <vector>
#include <string>
#include <list>
#include "useful_methods.hpp"

class KNN {
    int k;
    std::vector<number_hog>* model;
    std::vector<Answer> results = std::vector<Answer>(10);
    
    long double distance(const number_hog&, const number_hog&);
    void list_insert(std::list<digit_dist>&, const digit_dist&);
    short int best_guess(std::list<digit_dist>&);
    
public:
    std::vector<Answer> getResults(){ return results; }
    void setModel(std::vector<number_hog>* val){ model = val; }
    void setK(const int& val){ k = val;}
    
    bool classify(const number_hog&);
};

#endif /* KNN2_hpp */
