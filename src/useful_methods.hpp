//
//  useful_methods.hpp
//  DigitID
//
//  Created by Connor Jennings on 9/20/22.
//

#ifndef useful_methods_hpp
#define useful_methods_hpp
#include <vector>
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

struct list_of_params{
    std::vector<short int> train;
    int reps;
    int k;
    int test_cases;
};

struct number_hog{
    short int digit;
    std::vector<double> HOG;
};

std::string fileName(const short int&, const int&, bool);


class Answer {
    int correct = 0;
    int total = 0;
    
public:
    friend std::ostream &operator<< ( std::ostream &output, const Answer &ans ) {
        if(ans.total == 0){
            output << "0 / 0" ;
        }else{
            output << ans.correct << " / " << ans.total << "  or  " << (float)ans.correct/ans.total * 100 << " %";;
            //output << (float)ans.correct/ans.total * 100 << " %";
        }
        return output;
    }
    
    void right(){ ++correct; ++total; }
    void wrong(){ ++total; }
    int getCorrect(){return correct;}
    int getTotal(){return total;}
};

void output(const std::vector<Answer>&);

struct digit_dist{
    short int digit;
    long double dist = 0.0;
};

Mat getImg(const short int&, const int&, bool);

void print_list(const std::list<digit_dist>&);

#endif /* useful_methods_hpp */
