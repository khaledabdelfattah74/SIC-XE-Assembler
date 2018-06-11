//
//  ExpressionEvaluator.cpp
//  SIC
//
//  Created by Khaled Abdelfattah on 6/11/18.
//  Copyright © 2018 Khaled Abdelfattah. All rights reserved.
//

#include "ExpressionEvaluator.hpp"
#include <stack>

int ExpressionEvaluator::prec(char c) {
    if(c == '^')
        return 3;
    else if(c == '*' || c == '/')
        return 2;
    else if(c == '+' || c == '-')
        return 1;
    else
        return -1;
}

string ExpressionEvaluator::infix_to_postfix(string s) {
    stack<char> st;
    st.push('N');
    string postfix_exp;
    if (s[0] == '-')
        s = '0' + s;
    for (int i = 0; i < s.length(); i++) {
        while (s[i] >= 48 && s[i] <= 57) {
            postfix_exp += s[i];
            i ++;
        }
        postfix_exp += '.';
        if(s[i] == '(')
            st.push('(');
        else if(s[i] == ')') {
            while(st.top() != 'N' && st.top() != '(') {
                char c = st.top();
                st.pop();
                postfix_exp += c;
            }
            if(st.top() == '(') {
                st.pop();
            }
        } else {
            while(st.top() != 'N' && prec(s[i]) <= prec(st.top())) {
                char c = st.top();
                st.pop();
                postfix_exp += c;
            }
            st.push(s[i]);
        }
    }
    while(st.top() != 'N') {
        char c = st.top();
        st.pop();
        postfix_exp += c;
    }
    return postfix_exp;
}

int ExpressionEvaluator::evaluate(string expression) {
    expression = infix_to_postfix(expression);
    int a, b;
    stack<int> s;
    for (int i = 0; i < expression.length(); i++) {
        string address = "";
        while (expression[i] >= 48 && expression[i] <= 57) {
            address += expression[i];
            i++;
        }
        if (address.length() != 0)
            s.push(stoi(address));
        
        if (expression[i] >= 42 && expression[i] <= 47 && expression[i] != '.') {
            a = s.top();
            s.pop();
            b = s.top();
            s.pop();
            switch(expression[i]) {
                case '+':
                    s.push(a + b);
                    break;
                case '-':
                    s.push(b - a);
                    break;
                case '*':
                    s.push(a * b);
                    break;
                case '/':
                    s.push(b / a);
                    break;
            }
        }
    }
    return s.top();
}
