#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
    // Flush after every std::cout / std:cerr
    cout << unitbuf;
    cerr << unitbuf;
    ofstream history_file("D:/VisualStudioProjects/kubsh/home/main_user/kubsh_history.txt", ios::app);
    if (!history_file.is_open()) {
        std::cerr << "Error: cannot open history file!" << std::endl;
        return 1;
    }
    history_file << unitbuf; //for rebuffing

    while (true) 
    {
        cout << "$ ";
        string input;
        if (!getline(cin, input) || (input == "\\q")) 
        {//exit 1
            // Ctrl+D
            cout << "\nExit" << endl;
            break;
        }

        history_file << input << "\n";

        if (input.substr(0, 4) == "echo")
        {
            cout << input.substr(4) << "\n";
        }
    }
}
