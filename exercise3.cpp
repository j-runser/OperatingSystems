/* exercise2.cpp
 * 
 * Author: Joe Runser
 * Created: 23 February 2018
 * Updated: 23 February 2018
 *
 * Pass commands to the operating system. The begginings of a shell.
 */

#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

extern char **environ;

int main(int argc, char *argv[]) {

    string line;
    cout << "=> ";
    
    while(getline(cin, line)) {

        string cmdFirst;
        istringstream strm;

        strm.str(line);
        strm >> cmdFirst;

        if(line == "dir") {
            line.replace(0, 3, "ls -al");
            cout << line << endl;
            system(line.c_str());
        }
        else if(line == "clear" || line == "clc") {
            system("clear");
        }
        else if(line == "environ") {
            for(int i = 0; environ[i] != NULL; i++) {
                cout << environ[i] << endl;
            }
        }
        else if(line == "quit" || line == "exit" || line == "Q" || line == "q") {
            break;
        }
        else {
            system(line.c_str());
        }

        cout << "=> ";
    }

    return 0;

}
