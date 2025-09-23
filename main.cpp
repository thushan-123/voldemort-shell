#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>

using namespace std;

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

string ls_cmd(string input){
    
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
    //command_name.erase(remove(command_name.begin(), command_name.end(), ' '), command_name.end());
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