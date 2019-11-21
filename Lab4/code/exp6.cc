#include <iostream>
#include <cstring>		// C-strings: for strcpy()
using namespace std;

//what...i just switch delete[] position on main...
int main() {
    char *greeting = new char[1024];
    strcpy(greeting, "Dear");
    
    cout << greeting << " Sir/Madam\n";
    delete[] greeting;
    return 0;
}