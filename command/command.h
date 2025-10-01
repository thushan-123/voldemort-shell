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

vector<string> split_by_space(const string& input);

string ls_cmd();
bool is_exists_exec(fs::path file_path);

string echo_cmd(std::string input);
string type_cmd(std::string input, char* path_ptr);
string invalied_cmd(std::string input);
bool is_cmd_exec(string input, char *path_ptr);
string custom_execution(string input, char *path_ptr);
string pwdcmd();
string cdcmd(string input);

#endif

