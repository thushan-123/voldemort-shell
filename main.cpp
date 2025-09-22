#include <iostream>
#include <string>

using namespace std;

string echo_cmd(string input){
    if(input.find("echo")){
        return  input.substr(5);
    }
}


string output(string str){

    string input = str;
    string invalied_cmd = "invalied_command: ";
    return invalied_cmd + input;
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