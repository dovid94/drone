#ifndef ASSIGN_H_
#define ASSIGN_H_

#include "calculate.h"
#include "newClient.h"
#include <string>
#include <set>
#include <iostream>
#include <utility>
#include <vector>
#include "database.h"
#include "dovar.h"

using namespace std;

/**
 * @brief 
 * responsible for assigning values to variables\n.
 * 
 */
class Assign: public DoCommand
{
    public:

    /**
     * @brief str is an expression that might contien variable names, the function looks for 
     * all variable names and changes them to their numarical value.
     * @param str - the expression 
     * @return string - the epression without variable names.
     */
    string getVar(string str);

    /**
     * @brief recives an assighment line from the parser and calculates it's left side value.
     * 
     * @param vec - line from the parser
     * @return float - left side value
     */
    float calculater(vector<string> vec);

    /**
     * @brief recieves an assighment line from the parser, calculates it's left side value,
     * finds the right side variable, and assignes the value to it.
     * 
     * @param msg - the assighment line.
     */
    void command(vector<string> msg) override;

};

#endif