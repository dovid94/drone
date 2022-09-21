#include "lexer.h"


Lexer::Lexer(const char *fileName)
{
    ifstream f;
    string line, word;
    f.open(fileName);
    vector <vector<string>> lst;
    while (f)
    {
        getline(f, line);
        stringstream W(line);
        vector <string> vec;
        while (getline(W, word, ' '))
        {
            if (word != "\n" && word != "\t" && word != "")
            vec.push_back(word);
        }
        if (vec.size() > 0)
            lst.push_back(vec);

    }
    lst.pop_back();

    for (auto& itr: lst)
    {
        // cout << itr.size() << endl;
        if ((itr.size() >= 2 && itr[1][0] == '=') || (itr.size() > 3 && itr[3] != "bind" && itr[0] == "var"))
            itr.insert(itr.begin(), "assign");
        else if (itr.size() >= 5 && itr[0] != "var" && itr[5] == "=")
        {
            itr.insert(itr.begin(), "assign");
        }
    }

    int listSize = lst.size();
    for (int i = 0; i < listSize; i++)
    {
        if (lst[i][0] == "while")
        {
            lst[i].push_back("$");
            for (int j = i+1; j < listSize; j++)
            {
                if (lst[j][0] == "}")
                {
                    i = j;
                    break;
                }
                for (auto& itr: lst[j])
                    lst[i].push_back(itr);
                lst[i].push_back("$");
                lst[j].clear();
            }
        }
    }
    for (auto& itr: lst)
    {
        if (itr.size() > 0 && (itr[0] != "}"))
            _data.push_back(itr);
    }
}


vector<vector<string>> Lexer::get_data()
{
    return _data;
}


// int main() {
//     Lexer lexer = Lexer("text.txt");
//     vector<vector<string>> vec;
//     vec = lexer.get_data();
//         for (int i = 0; i < vec.size(); i++) {
//         for (int j = 0; j < vec[i].size(); j++)
//             cout << vec[i][j] + ' ';
//         cout << endl;
//         }
//     return 0;
// }
