#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
#include <iostream>
#include <vector>


using namespace std;

/**
 * @brief the class DoCommand follows the design pattern 'command pattern'.
 * 
 */
class DoCommand
{
    public:
    virtual void command(vector<string> msg) = 0;

    virtual ~DoCommand();
};

#endif
