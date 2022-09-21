#ifndef PRINT_H_
#define PRINT_H_

#include <math.h>
#include "database.h"
#include "docommand.h"


class Printer: public DoCommand
{
    public:
    void command(vector<string> msg) override;

};

#endif