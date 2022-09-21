/**
 * this class calculates mathematical expressions with the function 'calculate(number)'.
 */
#ifndef CALCULATE_H_
#define CALCULATE_H_


#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <vector>
#include <cmath>
 
using namespace std;
 
class Equation
{
//define public member functions
public:
        Equation(); //default constructor
        ~Equation();//default destructor
        
        string rpn(); //main method
        void set(string); //main method
        float calculate(string exp);
        
        
        double Eval(vector <string> & s);
        void Convert(const string & Infix, string & Postfix);
        bool TakesPrecedence(char OperatorA, char OperatorB);
        bool IsOperand(char ch);
        bool IsOperator(char ch);
        bool IsNumber(char ch);
        string ChangeMe(string);
        string InsertSpace(string);
        bool CheckValid(string);
        string Next(string);
        
//define private member functions
private: 
        string Infix;
};

#endif