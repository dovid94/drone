#include "docommand.h"


using namespace std;

/**
 * @brief the function that all classes who inherite doCommand override (following the dessign pattern -
 * 'command pattern'). 
 * 
 * @param msg list of strings consisting the line that needs to be executed 
 */
void DoCommand::command(vector<string> msg){};

DoCommand::~DoCommand(){};

