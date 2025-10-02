#include "command.h"
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;
namespace fs = std::filesystem;

std::vector<std::string> CMDS_ARRAY = {"type" ,"echo" ,"exit"};

std::vector<string> split_by_space(const string& input){
    std::vector<std::string> result;
    istringstream iss(input);
    std::string word;
    while (iss >> word){
        result.push_back(word);
    }
    return result;
}

std::vector<std::string> split_string(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
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

std::string ls_cmd(){
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

std::string echo_cmd(string input){
    std::vector<std::string> inputs = split_by_space(input);
    if(inputs[0] == "echo"){
        if (inputs.size() > 1){
            return input.substr(5);
        } else {
            return " ";
        }
    }
    return " ";
}

std::string type_cmd(string input, char *path_ptr){
    std::vector<std::string> inputs = split_by_space(input);

    char *path_ptr1 = path_ptr;
    std::string path_str(path_ptr1);

    std::vector<std::string> paths = split_string(path_str, ':');

    for (auto current_path: paths){
        fs::path file_path = fs::path(current_path)/inputs[1];
        if(is_exists_exec(file_path) && inputs[1] != "echo"){
            return inputs[1] + std::string(" is ") + file_path.string();
        }
    }      

    for (const std::string& cmd : CMDS_ARRAY){
        if(inputs[1] == cmd){
            return cmd + " is a shell builtin";
        }
    }

    return "invalid_command: not found";
}

bool is_cmd_exec(string input, char *path_ptr){   // check for the user input is exists
    std::vector<std::string> inputs = split_by_space(input);
    char *path_ptr1 = path_ptr;
    std::string path_str(path_ptr1);

    std::vector<std::string> paths = split_string(path_str, ':');

    for (auto current_path: paths){
        fs::path file_path = fs::path(current_path)/inputs[0];
        if(is_exists_exec(file_path)){
            return true;
        }
    }      
    return false;
}

std::string safe_get_path(char *path_ptr) {
    if (!path_ptr) {
        return "/usr/bin:/usr/local/bin";
    }
    return string(path_ptr);
}


std::string custom_execution(std::string input, char *path_ptr){ // run the excutable cmd with arguments

    std::vector<std::string> inputs = split_by_space(input);
    
    std::string path_str = safe_get_path(path_ptr);
    
    std::vector<std::string> paths = split_string(path_str, ':');

    for (auto current_path: paths){   // find executable paths
        fs::path file_path = fs::path(current_path)/inputs[0];
        if(is_exists_exec(file_path)){

            std::string cmd = input + " 2>&1"; // cap stderr

            FILE *p = popen(cmd.c_str(), "r"); // run prodram and get output

            if(!p){
                return "error: failed to run this command " + cmd;
            }

            std::string output;
            char buffer[128];

            while (fgets(buffer, sizeof(buffer), p) != nullptr){
                output += buffer;
            }

            pclose(p);
            return output;
           
        }
    }

    return "not found";
}

std::string pwdcmd(){
    return fs::current_path().string();
}


std::string cdcmd(std::string input){

    std::vector<std::string> inputs = split_by_space(input);

    if (inputs.size() < 2){
        return "cd: missing operand";
    }

    if(fs::exists(fs::path(inputs[1]))){
        fs::current_path(fs::path(inputs[1].c_str()));
        return "";
    }else if(inputs[1] == ".."){
        std:vector<std::string> dirs = split_string(fs::current_path(), '/');
        std:string new_path;

        for(int x=0; x<dirs.size() -1; x++){
            new_path = "/" + dirs[x] ;
        }
        if(fs::exists(fs::path(new_path))){
            fs::current_path(fs::path(new_path.c_str()));
            return "";
        }
    }
    else{
        return "cd: " + inputs[1] + ": No such file or directory";
    }

    //string c_path = fs::current_path().string();
}

std::string invalied_cmd(std::string input){
    return "invalied_command: " + input;
}
