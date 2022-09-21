#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;


class Lexer
{
    public:
    Lexer(const char *file_name);
    vector<vector<string> > get_data();

    private:
    vector<vector<string> > _data;
};