#include "database.h"

/**
 * @brief Construct a DataBase object in acordence with the singletone design pattern.
 * 
 * the constructure is in private, and at its intiation it gets all the sampled data variable names.
 * 
 */
DataBase::DataBase()
{
    _varNames = setDataNames();
}

/**
 * @brief returns am instance of database, and if none exist it will create one.
 * 
 * @return DataBase* a pointer to a the database object.
 */
DataBase *DataBase::getInstance()
{
    if (!DataBase::_db)
        _db = new DataBase;
    return _db;
}

/**
 * @brief returns the data sampled from the simulater.
 * 
 * @return vector<float> the sampled data.
 */
vector<float> DataBase::getData()
{
    return _database;
}

/**
 * @brief used by the server to update the sampled data (_database).
 * 
 * @param stuff array of chars conteining 37 values that represent the current state of the drone.
 * @param num length of the array.
 */
void DataBase::setData(char stuff[512], int num)
{
    vector<float> vec;
    string word;
    for (int i = 0; i < num; i++)
    {
        if (stuff[i] == '\n')
        {
            vec.push_back(std::stof(word));
            break;
        }
        else if (stuff[i] == ',')
        {
            vec.push_back(std::stof(word));
            word = "";
            continue;
        }
        if (i == num - 1)
        {
            vec.push_back(std::stof(word + stuff[i]));
            break;
        }
        word = word + stuff[i];
    }
    DataBase *db = db->getInstance();
    db->_database = vec;
}

/**
 * @brief gets the names of the sampled data variables and inserts them in a map with their index at _database.
 * 
 * the variable names are retrieved from the file 'generic_small.xml' (generic_small.xml tells the simulater which
 * values to send to the server), the names are stored in a map with their index at _database, so for the
 * kay-value {'magnetos', 1} - the value 'magnetos' can be found in _database at index 1. 
 * 
 * @return map<string, int> map of names and indexes.
 */
map<string, int> DataBase::setDataNames()
{
    ifstream f;
    string line;
    int i = 0;
    map<string, int> lst;
    f.open(R"(C:\Program Files\FlightGear 2020.3\data\Protocol\generic_small.xml)");
    while (f)
    {
        getline(f, line);
        if (line.length() > 15 && line.substr(4, 6) == "<name>"){
            int found = line.find_last_of('_');
            if (found != string::npos)
            {
                lst.insert({line.substr(found+1, line.length() - (found+8)), i});
                _allNames.push_back(line.substr(found+1, line.length() - (found+8)));
                i++;
                cout << line.substr(found+1, line.length() - (found+8)) << endl;
            }
            else
            {
                lst.insert({line.substr(10, line.length() - 17), i});
                _allNames.push_back(line.substr(10, line.length() - 17));
                i++;
            }
        }
    }
    f.close();
    return lst;
}

/**
 * @brief adds a localy deffined variable to the list '_variables'.
 * 
 * @param name the variables name
 * @param val the variables value
 */
void DataBase::addVariables(string name, float val)
{
    _variables[name] = val;
    _allNames.push_back(name);
}

/**
 * @brief looks for the variable 'name' in the list of samplad data, and if its not there it will
 * look at the localy defined variables 
 * 
 * @param name name of variable to look for
 * @return float the value of the variable 'name'
 */
float DataBase::getValue(string name)
{
    // checks if the variable 'name' is in '_varNames', i.e. the sampled data.
    cout << "#" << name << '#' << endl;
    if (_varNames.find(name) != _varNames.end()){
        int indx = _varNames.find(name)->second;
        cout << name << " = " << _database[indx] << endl;
        return _database[indx];
    }
    // checks if name is a user defined variable.
    else if (_variables.find(name) != _variables.end())
    {
        cout << "setting " << name << " = " << _variables.find(name)->second << endl;
        return _variables.find(name)->second;
    }
    // cout << "returning infinity" << endl;
    // if the value name was not found returning infinity.
    return INFINITY;
}

/**
 * @brief returns a list of all variables local or not.
 * 
 * @return vector<string> the list of variables
 */
vector<string> DataBase::getAllNames()
{
    return _allNames;
}


/**
 * @brief adds a new variable name to an existing samplad data variable. 
 * 
 * @param name the new name
 * @param indx its index at '_database'
 */
void DataBase::addNewName(string name, int indx)
{
    _varNames[name] = indx;
    _allNames.push_back(name);
}

/**
 * @brief returns an index of a samplad data variable.
 * 
 * @param name the name of the samplad data
 * @return int the index of the samplad data
 */
int DataBase::getIndex(string name)
{
    return _varNames[name];
}


DataBase *DataBase::_db = 0;


// int main()
// {
//     DataBase *db = db->getInstance();
//     map<string, int> things = db->setDataNames();
//     // for (auto& itr: things)
//     // {
//     //     cout << itr.first + ' ' << itr.second << endl;
//     // }
// }