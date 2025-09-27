#include "command.h"
#include <vector>
#include <string>
#include <cstdlib>

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

string ls_cmd(){
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
        if (inputs.size() > 1){
            return input.substr(5);
        } else {
            return " ";
        }
    }
    return " ";
}

string type_cmd(string input, char *path_ptr){
    vector<string> inputs = split_by_space(input);

    char *path_ptr1 = path_ptr;
    string path_str(path_ptr1);

    vector<string> paths = split_string(path_str, ':');

    for (auto current_path: paths){
        fs::path file_path = fs::path(current_path)/inputs[1];
        if(is_exists_exec(file_path) && inputs[1] != "echo"){
            return inputs[1] + string(" is ") + file_path.string();
        }
    }      

    for (const string& cmd : CMDS_ARRAY){
        if(inputs[1] == cmd){
            return cmd + " is a shell builtin";
        }
    }

    return "invalid_command: not found";
}

bool is_cmd_exec(string input, char *path_ptr){   // check for the user input is exists
    vector<string> inputs = split_by_space(input);
    char *path_ptr1 = path_ptr;
    string path_str(path_ptr1);

    vector<string> paths = split_string(path_str, ':');

    for (auto current_path: paths){
        fs::path file_path = fs::path(current_path)/inputs[1];
        if(is_exists_exec(file_path)){
            return true;
        }
    }      
    return false;
}

std::string custom_execution(const std::string &input) {
    const char* path_ptr = getenv("PATH");
    if (!path_ptr) return "PATH not set";

    std::vector<std::string> inputs = split_by_space(input);
    std::string path_str(path_ptr);
    std::vector<std::string> paths = split_string(path_str, ':');

    for (auto &current_path: paths) {
        fs::path file_path = fs::path(current_path) / inputs[0];
        if (is_exists_exec(file_path)) {
            int result = system(input.c_str());
            return (result == 0) ? "" : "command failed";
        }
    }
    return "not found";
}


string invalied_cmd(string input){
    return "invalied_command: " + input;
}
