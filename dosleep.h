#ifndef SLAAP_H_
#define SLAAP_H_

#include <iostream>
#include <Windows.h>
#include "docommand.h"
// #include "doassign.h"

class Sleeper: public DoCommand
{
    public:
    void command(vector<string> msg) override;
};

#endif