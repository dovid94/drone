#include "dosleep.h"

/**
 * @brief puts the main to sleep.
 * 
 * @param msg the amount of time to sleep in miliseconds
 */
void Sleeper::command(vector<string> msg)
{
    string word = msg[1];
    int num = stoi(word);
    cout << "sleeping" << endl;
    Sleep(num);
}

