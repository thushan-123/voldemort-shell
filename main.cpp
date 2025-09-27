#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <bits/stdc++.h>

#include "command/command.h"

using namespace std;
namespace fs = std::filesystem;


string handle_commands(string input){

    vector<string> cmd = split_by_space(input);

    char *path_ptr = getenv("PATH");

    if (cmd[0] == "echo"){
        return echo_cmd(input);
    }else if(cmd[0] == "type") {
        return type_cmd(input, path_ptr);
    }else if(){

    }else{
        return invalied_cmd(input);
    }
};

string output(string str){

    string input = str;
    string result = handle_commands(input);
    return result;
}

void shell () {

    string input_line;

    while (input_line != "exit"){
        cout << "$ >";
        getline(cin, input_line);
        if(input_line == "exit"){
            continue;
        }
        cout << output(input_line);
        cout << endl;

    }
   
}



int main() {

    shell();

    return 0;
    
}
// g++ -std=c++17 main.cpp 
// g++ -std=c++17 main.cpp command/command.cpp -o shell

// PATH="/usr/bin:/usr/local/bin:$PATH"