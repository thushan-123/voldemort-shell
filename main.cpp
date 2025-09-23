#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
namespace fs = std::filesystem;

vector<string> CMDS_ARRAY = {"type" ,"echo" ,"exit"};

vector<string> split_by_space(const string& input){
    vector<string> result;
    istringstream iss(input);
    string word;
    while (iss >> word){
        result.push_back(word);
    }

    return result;
}

vector<string> split_string(const string& str, char delimiter) {
    vector<string> tokens;
    std::string currentToken;
    for (char c : str) {
        if (c == delimiter) {
            tokens.push_back(currentToken);
            currentToken = "";
        } else {
            currentToken += c;
        }
    }
    tokens.push_back(currentToken); 
    return tokens;
}

// filesystem::path

string ls_cmd(){
    // identify the path
    return " ";

}

bool is_exists_exec(fs::path file_path){

    if(!fs::exists(file_path)){
        return false;
    }

    fs::file_status file_status = fs::status(file_path);
    if (fs::is_regular_file(file_status) && (file_status.permissions() & fs::perms::owner_exec) != fs::perms::none ){
            return true;
    }

    return false;
    

}

string echo_cmd(string input){
    vector<string> inputs = split_by_space(input);
    if(inputs[0] == "echo"){
        if (inputs.size() >1){
            return  input.substr(5);
        }else {
            return " ";
        }
        
    }
    return " ";
}

string type_cmd(string input){
    vector<string> inputs = split_by_space(input);
    string command_name = input.substr(5);

    char *path_ptr = getenv("PATH");
    string path_str(path_ptr);

    vector<string> paths = split_string(path_str, ':');
    
    
    for (auto current_path: paths){
        fs::path file_path = fs::path(current_path)/inputs[1];

        if(is_exists_exec(file_path) && inputs[1] != "echo"){
            return inputs[1] + " is " + file_path.string();
        }
    }      

    for (const string& cmd : CMDS_ARRAY){
        if(inputs[1] == cmd){
            return  cmd + " is a shell builtin";
        }
    }
        
    
    return "invalid_command: not found";
}

string invalied_cmd (string input){
    string invalied_cmd = "invalied_command: ";
    return invalied_cmd + input;
}

string handle_commands(string input){

    vector<string> cmd = split_by_space(input);

    if (cmd[0] == "echo"){
        return echo_cmd(input);
    }else if(cmd[0] == "type") {
        return type_cmd(input);
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