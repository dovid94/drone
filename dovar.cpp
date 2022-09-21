#include "dovar.h"


Var::Var(){
    map<string, string> _vars;
    // static Var *_var;
}

/**
 * @brief creates a Var instance if none exist, and returns the instance
 * 
 * @return Var* an instance of the class
 */
Var *Var::getInstance(){
    if (!Var::_var)
        _var = new Var;
    return _var;
}

/**
 * @brief returns the map of variable names and their path
 * 
 * @return map<string, string> the map of variable names and their path
 */
map<string, string> Var::getData(){
    return _vars;
}

/**
 * @brief adds to the _vars map a name of a variable as kay and its path as value
 * 
 * @param msg the line from the text file with the variable name and its path
 */
void Var::command(vector<string> msg){
    if (msg[3] != "bind")
    {

    }
    Var *var = var->getInstance();
    var->_vars[msg[1]] = msg[4];
    int indx = msg[4].find_last_of("/");
    string originName = msg[4].substr(indx+1, msg[4].size() - (indx+2));
    cout << originName<< endl;
    if (originName != msg[1] && msg[1] != "blc")
    {
        DataBase *db = db->getInstance();
        db->addNewName(msg[1], db->getIndex(originName));
    }
}

Var *Var::_var = 0;

