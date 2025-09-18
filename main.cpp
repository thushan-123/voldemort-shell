#include <iostream>
#include <string>

using namespace std;



void shell () {

    string input_line;

    cout << "$ >";
    getline(cin, input_line);
    cout << endl;
    
}



int main() {

    shell();
    
}