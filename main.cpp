#include <iostream>
#include <string>

using namespace std;


string output(string str){

    return "Invalid Command";
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