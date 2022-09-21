#ifndef DATABASE_H_
#define DATABASE_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <map>
#include <math.h>
using namespace std;


/**
 * @brief 
 * this class is responsible for storing all the variables in this program\n.
 * the data sampled by the server is stored at the vector '_database'.
 * a map of variable names and their index at '_database' (only for sampled data) is stored at '_varNames'.
 * the variables that are defined by the user are stored at the map '_variables' name and value.
 * the names of all the variables are stored at the vector '_allNames'.   
 */
class DataBase
{
    // stores the data sampled by the server.
    vector<float> _database;

    // stores the name of each sampled data paird with its indexed position at _database.
    map<string, int> _varNames;

    // a map that stores a local variable as value and its name as kay.
    map<string, float> _variables;

    // constructor is private, to keep the class singletone. 
    DataBase();

    // static varaible to store the constructed object.
    static DataBase *_db;

    // A list of all the variable names, local and not. 
    vector<string> _allNames;

    public:
    
    // parses from the generic_small.xml file the name and index of each sampled data.
    map<string, int> setDataNames();

    // adds a new name of a sampled data and its index to the map '_varNames'.
    void addNewName(string name, int indx);

    // returns a names indexed position at '_database', the name is of a sampled data.
    int getIndex(string name);

    // returns all the sampled data.
    vector<float> getData();

    // returns a list of all variable names.
    vector<string> getAllNames();

    // sets the sampled data into '_database'.
    void setData(char stuff[512], int num);

    // adds new user defined variables (name and value), to the variable map '_variables'.
    void addVariables(string name, float val);

    // returns the value of the variable 'name', the variable can be local or sampled.
    float getValue(string name);

    // returns an instance of DataBase.
    static DataBase *getInstance();
};

#endif

