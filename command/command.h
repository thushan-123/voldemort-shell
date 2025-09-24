#ifndef COMMAND
#define COMMAND

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>
#include <fstream>


namespace fs = std::filesystem;


extern std::vector<std::string> CMDS_ARRAY;


std::vector<std::string> split_by_space(const std::string& input);
std::vector<std::string> split_string(const std::string& str, char delimiter);

std::string ls_cmd();
bool is_exists_exec(fs::path file_path);

std::string echo_cmd(std::string input);
std::string type_cmd(std::string input, char* path_ptr);

std::string invalied_cmd(std::string input);

#endif 
