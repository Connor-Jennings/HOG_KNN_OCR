//
//  KNN2.cpp
//  DigitID
//
//  Created by Connor Jennings on 9/22/22.
//

#include "KNN2.hpp"

long double KNN::distance(const number_hog& test_obj, const number_hog& known_value) {
    if(test_obj.HOG.size() != known_value.HOG.size()){ return 1000000; }
    auto first = test_obj.HOG.begin();
    auto last = test_obj.HOG.end();
    auto first2 = known_value.HOG.begin();
    auto last2 = known_value.HOG.end();
    
    long double ret = 0.0;
    while (first != last && first2 != last2) {
        double dist = abs((*first++) - (*first2++));
        ret += dist * dist;
  }
  return ret > 0.0 ? sqrt(ret) : 0.0;
}


void KNN::list_insert(std::list<digit_dist>& lst, const digit_dist& value){
    if(value.dist < 0) { return; }
    if(value.dist > lst.back().dist ){ lst.push_back(value); }
    else{
        bool flag = false;
        for(std::list<digit_dist>::iterator it = lst.begin(); it != lst.end(); ++it){
            if(it->dist > value.dist){
                lst.insert(it, value);
                //print_list(lst);
                flag = true;
                break;
            }
        }
        if(!flag){
            lst.push_back(value);
        }
    }
}



short int KNN::best_guess(std::list<digit_dist>& lst){
    //pick the first k entries from the sorted collection
    //get the labels of the selected k entries
    int count = 1;
    std::vector<int> tally(10);
    for(std::list<digit_dist>::iterator it = lst.begin(); it != lst.end() && count <= k; ++it, ++count){
        tally[it->digit] += 1;
    }
    
    int winner = 0;
    int winner_tally = 0;
    for(int x = 0; x < tally.size(); ++x){
        if(tally[x] > winner_tally){
            winner = x;
            winner_tally = tally[x];
        }
    }
    //return the mode of the k labels
    return winner;
}

bool KNN::classify(const number_hog& test_obj){
    std::list<digit_dist> lst;
    for(int i = 0; i < model->size(); ++i){
        number_hog known_value = (*model)[i];
        long double dist = distance(test_obj, known_value);
        digit_dist temp = {.digit = known_value.digit, .dist = dist};
        list_insert(lst, temp);
    }
    if(best_guess(lst) == test_obj.digit){
        results[test_obj.digit].right();
        return true;
    } else{
        results[test_obj.digit].wrong();
        std::cout << "guessed: "<< best_guess(lst) << ", correct answer: " << test_obj.digit << std::endl;
        return false;
    }
}

