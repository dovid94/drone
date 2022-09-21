#include "doprint.h"

/**
 * @brief prints the strings in msg, if msg contiens a variable name it will
 *  retrieve its value and print it.
 * 
 * @param msg the line that needs to be printed
 */
void Printer::command(vector<string> msg)
{
    cout << "printing" << endl;
    string word = "";
    try
    {
        stoi(msg[1]);
        cout <<msg[1] << endl;
        return;
    }
    catch(...)
    {
        if (msg.size() > 2)
        {
            word = msg[1];
            for (int i = 2; i < msg.size(); i++)
                word = word + ' ' + msg[i];
        }
        else if (msg[1][0] == '"')
            word = msg[1];
        else
        {
            DataBase *db = db->getInstance();
            float num = db->getValue(msg[1]);
                // word = to_string(num);
                cout << num << endl;
                return;
        }
    }
    cout << word << endl;
}
