//
//  ExpressionEvaluator.hpp
//  SIC
//
//  Created by Khaled Abdelfattah on 6/11/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#ifndef ExpressionEvaluator_hpp
#define ExpressionEvaluator_hpp

#include <stdio.h>
#include <string>

using namespace std;
class ExpressionEvaluator {
public:
    int evaluate(string);
private:
    string infix_to_postfix(string);
    int prec(char);
};
#endif /* ExpressionEvaluator_hpp */
