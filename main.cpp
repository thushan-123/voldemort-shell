#include <iostream>
#include <string>

using namespace std;


string output(string str){

    string input = str;
    string invalied_cmd = "invalied_command: ";
    return invalied_cmd + input;
}

void shell () {

    string input_line;

    cout << "$ >";
    getline(cin, input_line);
    cout << output(input_line);
    cout << endl;

}



int main() {

    shell();
    
}