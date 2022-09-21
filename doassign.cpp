#include "doassign.h"


/**
 * @brief str is an expression that might contien variable names, the function looks for 
 * all variable names and changes them to their numarical value.
 * 
 * @param str - the expression 
 * @return string - the epression with the numarical value istead of its name.
 */
string Assign::getVar(string str){

    int num = 0;
    float value = 0;
    DataBase *db = db->getInstance();
    vector<string> vec = db->getAllNames();
    for (auto& itr: vec){
        while (str.find(itr) != string::npos)
        {
            num = str.find(itr);
            value = db->getValue(itr);
            str = str.substr(0, num) + to_string(value) + str.substr(num+itr.length(), str.length());
        }
    }
    return str;
}


/**
 * @brief recives an assighment line from the parser and calculates it's left side value.
 * 
 * @param vec - line from the parser
 * @return float - left side value
 */
float Assign::calculater(vector<string> vec){
    string word = "";
    bool i = false;
    for (auto& itr: vec){
        if (itr == "="){
            i = true;
            continue;
        }
        if (i)
            word = word + itr;
    }
    word = getVar(word);
    try 
    {
        return std::stof(word);
    }
    catch(...)
    {
        Equation equation;
        return equation.calculate(word);
    }
    return 0;
}


/**
 * @brief recieves an assighment line from the parser, calculates it's left side value,
 * finds the right side variable, and assignes the value to it.
 * 
 * @param msg - the assignment line.
 */
void Assign::command(vector<string> msg){
    float num = calculater(msg);
    // cout << msg[1] <<" = " << num << endl;
    string word = msg[1];
    Var *var = var->getInstance();
    map<string, string> vars = var->getData();
    if (vars.find(word) != vars.end())
        {
            string path = vars[word].substr(1, vars[word].size()-2);
            string all = "set " + path + " " + to_string(num) + "\r\n";
            // const char *data = all.data(); 
            Client *cl = cl->getInstance();
            cl->sender(all);
        }
    else if (msg[1] == "var")
    {
        DataBase *db = db->getInstance();
        db->addVariables(msg[2], num);
    }
}


