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


std::string handle_commands(std::string input){

    std::vector<std::string> cmd = split_by_space(input);

    char *path_ptr = getenv("PATH");
    if (!path_ptr) {
        path_ptr = strdup("/usr/bin:/usr/local/bin");
    }

    if (cmd[0] == "echo"){
        return echo_cmd(input);
    }
    else if(cmd[0] == "type") {
        return type_cmd(input, path_ptr);
    }
    else if(cmd[0] == "pwd"){
        return pwdcmd();
    }
    else if(cmd[0] == "cd"){
        return cdcmd(input);
    }
    else if(is_cmd_exec(cmd[0],path_ptr)){
        return custom_execution(input,path_ptr);
    }
    else{
        return invalied_cmd(input);
    }
};

std::string output(std::string str){

    std::string input = str;
    std::string result = handle_commands(input);
    return result;
}

void shell () {

    std::string input_line;

    while (input_line != "exit"){

        // show current path in shell
        std::string current_path = pwdcmd();
        cout << "[" << current_path << "]" << " $ > ";
        getline(cin, input_line);
        if(input_line == "exit"){
            break;
        }
        std::string output_ = output(input_line);
        char is_new_line = output_[output_.length() -1];
        cout << output_;
        if (is_new_line != '\n'){
            cout << endl;
        }
        

    }
   
}



int main() {

    std::string banner = R"(
            ╔══════════════════════════════════════════════╗
            ║              VOLDEMORT MAGIC SHELL           ║  Developed by thush
            ╚══════════════════════════════════════════════╝
            )";
    
    cout << banner << endl;
    shell();

    return 0;
    
}
// g++ -std=c++17 main.cpp 
// g++ -std=c++17 main.cpp command/command.cpp -o shell

// PATH="/usr/bin:/usr/local/bin:$PATH"