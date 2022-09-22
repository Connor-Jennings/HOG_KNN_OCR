//
//  KNN.cpp
//  DigitID
//
//  Created by Connor Jennings on 9/20/22.
//

#include "KNN.hpp"

std::vector<Answer> knn(list_of_params params, const std::vector<number_hog>& trained_model){
    //for each example in the data calculate the distance between the query and the training data
    std::vector<Answer> results(10);
    const int number_of_digits = (int)params.train.size()-1;
    int i = 0;
    
    for(int tests = 0; tests < params.test_cases; ++tests){
        const short int number_selected = params.train[i];
        auto file = fileName(number_selected, tests, true);
        if(i >= number_of_digits){ i = 0; }
        else{ ++i; }
        
        auto test_against = hog(number_selected, tests, true);
        std::list<digit_dist> lst;
        
        for(auto x : trained_model){
            double dist = distance(test_against, x);
            digit_dist value = {.digit = x.number, .dist = dist};
            //add the distance and the index of the example to an ordered collection
            //sort the ordered collection of distances and incdicies from smallest to largest by distances
            list_insert(lst, value);
        }
        //pick the first k entries from the sorted collection
        //get the labels of the selected k entries
        int count = 1;
        std::vector<int> tally(10);
        for(std::list<digit_dist>::iterator it = lst.begin(); it != lst.end() && count <= params.k; ++it, ++count){
            //std::cout << it->digit << " ";
            tally[it->digit] += 1;
        }
        //std::cout << std::endl;
        int winner = 0;
        int winner_tally = 0;
        for(int x = 0; x < tally.size(); ++x){
            if(tally[x] > winner_tally){
                winner = x;
                winner_tally = tally[x];
            }
        }
        
        //return the mode of the k labels
        //std::cout << "correct " << test_against.number << " , guess  " << winner  << std::endl << std::endl;
        if(winner == test_against.number){
            results[winner].right();
        }
        else{
            results[test_against.number].wrong();
        }
    }
    
   
    return results;
}


double distance(const number_hog& test_against, const number_hog& x){
    if(test_against.HOG.size() != x.HOG.size()) return 100000;
    double answer = 0;
    for(int i = 0; i < test_against.HOG.size(); ++i){
        answer += pow((x.HOG[i] - test_against.HOG[i]),2);
    }
    return sqrt(answer);
}

void list_insert(std::list<digit_dist>& lst, const digit_dist& value){
    if(value.dist > lst.back().dist){ lst.push_back(value); }
    else{
        bool flag = false;
        for(std::list<digit_dist>::iterator it = lst.begin(); it != lst.end(); ++it){
            if(it->dist > value.dist){
                lst.insert(it, value);
                flag = true;
                break;
            }
        }
        if(!flag){
            lst.push_back(value);
        }
    }
}
