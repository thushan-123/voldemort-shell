#ifndef COMMAND
#define COMMAND

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

std::vector<std::string> split_by_space(const std::string& input);

string ls_cmd();
bool is_exists_exec(fs::path file_path);

std::string echo_cmd(std::string input);
std::string type_cmd(std::string input, char* path_ptr);
std::string invalied_cmd(std::string input);
bool is_cmd_exec(std::string input, char *path_ptr);
std::string custom_execution(std::string input, char *path_ptr);
std::string pwdcmd();
std::string cdcmd(std::string input);
std::string catcmd(std::string input);

#endif

