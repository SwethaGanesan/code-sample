//
//  main.cpp
//
//  Created by Swetha Ganesan on 1/3/15.
//  Copyright (c) 2015 Swetha Ganesan. All rights reserved.
//

#include <iostream>
#include <vector>


int maximizeProfit(std::vector<int> houses){
        
    int noHouses = houses.size();
    
    // Base Case : If there are no houses, max value to be robbed is 0
    if(noHouses == 0)
    {
        return 0;
    }
        
    // Base Case : If there is only one house, the maximum value to be
    // robbed is the value of that house
    if(noHouses == 1)
    {
        if (houses[0] < 0) throw std::invalid_argument("unexpected negative value");
        return houses[0];
    }
        
    // maxValue[i] is the total maximum value of the robbery
    // if the street contained houses starting from ith house
    int* maxValue = new int[noHouses];
    
    /*
     General case
     Consider set {c,d}
     Our choice must be Max(c,d)
    
     Consider set {b,c,d}
     Our choices are either b+d or c
     which is Max( b+d, c)
    
     Consider set {a,b,c,d}
     Our choices are Max(a + Max(c,d), b + d)
     => F({a,b,c,d,...}) = Max((F(a) + F({c,d,e,...}),
     							(F(b) + F({d,e,...}))))
     To avoid recalculation of intermediate answers, we
     store the answer to the subproblem and arrive
     at final answer
    
    */
    maxValue[0] = houses[0];
    maxValue[1] = std::max(houses[1], houses[0]);
    for(int i = 2; i < noHouses; i++)
    {
        if(houses[i] < 0) throw std::invalid_argument("unexpected negative value");
        maxValue[i] = std::max(houses[i] + maxValue[i-2], maxValue[i-1]);
    }
    
    return maxValue[noHouses-1];
}

bool testCases()
{
    bool ans = true;
    
    // Case 1:
    std::vector<int> testCase1 = { 20, 18, 16, 14, 12, 10, 4, 1, 5, 9, 3, 2, 7, 8, 6, 11, 15, 17, 19, 13 };
    ans &= (112 == maximizeProfit(testCase1));
    
    // Case 2:
    std::vector<int> testCase2 = { 20, 10, 50, 5, 1 };
    ans &= (71 == maximizeProfit(testCase2));
    
    // Case 3:
    std::vector<int> testCase3 = { 20, 50, 10, 1, 5  };
    ans &= (55 == maximizeProfit(testCase3));
    
    // Case 4 - empty input:
    std::vector<int> testCaseEmpty = {};
    ans &= (0 == maximizeProfit(testCaseEmpty));
    
    // Case 5 - 1 element:
    std::vector<int> testCaseSingleElement = {1};
    ans &= (1 == maximizeProfit(testCaseSingleElement));
    
    // Case 6 - 2 elements:
    std::vector<int> testCaseTwoElement = {1, 5};
    ans &= (5 == maximizeProfit(testCaseTwoElement));
    
    // Case 7 - equal elements:
    std::vector<int> testCaseEqualElement = {15, 15, 15};
    ans &= (30 == maximizeProfit(testCaseEqualElement));
    
    // Case 8 - checking if input is valid:
    try
    {
        std::vector<int> invalid = { 20, 50, 10, -1, 5 };
        maximizeProfit(invalid);
        ans = false;
    }
    catch(std::exception ex)
    {
        // Expected error
    }
    
    return ans;
    
}

int main(int argc, const char * argv[])
{
    testCases() ?  std::cout << "Tests Passed" :  std::cout << "Tests Failed";
    return 0;
}


