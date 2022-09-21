#include "dowhile.h"

/**
 * @brief checks if the right value is bigger then the left value
 * 
 * @param leftValue 
 * @param rightValue 
 * @return true if right side is bigger
 * @return false if right is not bigger then left
 */
bool equals(float leftValue, float rightValue)
{
    if (rightValue > leftValue)
        return true;
    return false;
}

While::While()
{
    _ops.insert({"<", equals});
    vector<string> _opList;
    _opList.push_back("<");
    _miniParser["sleep"] = new Sleeper();
    _miniParser["print"] = new Printer();
    _miniParser["assign"] = new Assign();
    
}

/**
 * @brief gets one line conteining all the lines of the while loop and separates them to different lines
 * 
 * @param vec the one line with the entire while loop, each different line is separated by the token '$'
 * @return vector<vector<string>> the while loop with its lines separated
 */
vector<vector<string>> While::sorter(vector<string> vec)
{
    vector<vector<string>> newVec;
    vector<string> temp;
    for (auto& itr: vec)
    {
        if (itr == "$")
        {
            newVec.push_back(temp);
            temp = {};
            continue;
        }
        temp.push_back(itr);
    }
    return newVec; 
}

/**
 * @brief gets a string represenring two varaibles and an oporater, get the variables value
 * and returns the result of the condition
 * 
 * @param cond the string with the condition
 * @return true if the conditions result is true
 * @return false if the conditions result is false
 */
bool While::conditioner(string cond)
{
    vector<string> oparetorList = {"<"};
    for (int i = 0; i < oparetorList.size(); i++)
    {
        int indx = cond.find(oparetorList[i]);
        if (indx != string::npos)
        {
            float leftValue = getNumber(cond.substr(0, indx));
            float rightValue = getNumber(cond.substr(indx+oparetorList.size(), cond.size()-(indx+oparetorList.size())));
            std::function<bool(float, float)> func = _ops.find(oparetorList[i])->second;
            return func(leftValue, rightValue);
        }
    }
    return false;
}

/**
 * @brief gets a variable name, if the name matches a real variable his value will get returned
 * 
 * @param num the name of the variable
 * @return float the variables value
 */
float While::getNumber(string num)
{
    DataBase *db = db->getInstance();
    if (db->getValue(num) != INFINITY)
        return db->getValue(num);
    float nem;
    try {
        nem = stof(num);
    }
    catch(...){
        nem = 0;
    }
    return nem;
}

/**
 * @brief gets a line conteining a while loop and executes it up to the point where the condition is false
 * 
 * @param msg the while loop
 */
void While::command(vector<string> msg)
{
    vector<vector<string>> lines = sorter(msg);
    string condition = lines[0][1];
    while (true)
    {
        // cout << condition << endl;
        if (!conditioner(condition))
            break;
        for (int i = 1; i < lines.size(); i++)
        {
            vector<string> cmd;
            for (int j = 0; j < lines[i].size(); j++)
            {
                cmd.push_back(lines[i][j]);
            }
            _miniParser[lines[i][0]]->command(cmd);
            cmd.clear();
        }
    }
}