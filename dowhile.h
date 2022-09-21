#ifndef WHILE_H_
#define WHILE_H_

#include "doassign.h"
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <functional>
#include <valarray>
#include "doprint.h"
#include "dosleep.h"


using namespace std;

class While: public DoCommand
{
    public:
    While();
    vector<vector<string>> sorter(vector<string> vec);
    map<string, std::function<bool(float, float)>> _ops;
    bool conditioner(string cond);
    vector<string> _opList;
    float getNumber(string num);
    void command(vector<string> msg) override;
    map<string , DoCommand*> _miniParser;
};

#endif