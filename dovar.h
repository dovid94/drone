#ifndef VAR_H_
#define VAR_H_ 

#include <map>
#include <vector>
#include "docommand.h"
#include "database.h"


class Var: public DoCommand{

    // map of names of variables as keys, and the variables path as their value. 
    map<string, string> _vars;

    // implementation of singletone. 
    static Var *_var;
    Var();

    public:

    map<string, string> getData();

    void command(vector<string> msg) override;

    static Var *getInstance();
};

#endif