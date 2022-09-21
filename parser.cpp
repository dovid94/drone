#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <iterator>
#include <map>
#include "doopenserver.h"
#include "dovar.h"
#include "doprint.h"
#include "dowhile.h"
#include "doassign.h"
#include "dosleep.h"
#include "lexer.h"
#include <string>
using namespace std;

class Parser
{
    map <string, DoCommand*> _functions;

    public:
    Parser()
    {
        OpenServer *openServer = openServer->getInstance();
        _functions["openDataServer"] = openServer;
        _functions["sleep"] = new Sleeper();
        _functions["print"] = new Printer();
        _functions["while"] = new While();
        _functions["assign"] = new Assign();
        Client *client = client->getInstance();
        _functions["connect"] = client;
        Var *var = var->getInstance();
        _functions["var"] = var;
    }

    map<string, DoCommand*> getfuncs()
    {
        return _functions;
    }
};

int main()
{
    Parser parser;
    map<string, DoCommand*> stuff = parser.getfuncs();
    Lexer lexer = Lexer("new.txt");
    vector<vector<string>> vec = lexer.get_data();


    for (int i = 0; i < vec.size(); i++)
    {
        // cout << vec[i][0] << endl;
        for (auto& itr: vec[i])
            cout << itr << " ";
        cout << endl;
        stuff[vec[i][0]]->command(vec[i]);
    }

    return 0;
}

#endif