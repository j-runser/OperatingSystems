/* exercise2.cpp
 * 
 * Author: Joe Runser
 * Created: 23 February 2018
 * Updated: 23 March 2018
 *
 * Pass commands to the operating system. The begginings of a shell.
 */

#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>

using namespace std;

extern char **environ;

const int MAX_BUFF = 1024;

int main(int argc, char *argv[]) {

    string line;
    string cmdFirst;
    string cmdNext;

    string dirCurr = getcwd(NULL, MAX_BUFF);
       
    cout << dirCurr << " => ";

    while(getline(cin, line)) {

        istringstream strm;

        strm.str(line);
        strm >> cmdFirst;
        strm >> cmdNext;

        if(cmdFirst == "dir") {
            line.replace(0, 3, "ls -al");
            cout << line << endl;
            system(line.c_str());
        }
        else if(cmdFirst == "clear" || cmdFirst == "clc") {
            system("clear");
        }
        else if(cmdFirst == "cd") {
            // Set the current running directory.
            if(chdir(cmdNext.c_str()) != 0) {
                cout << "Error: Could not change the directory." << endl;
            }

            string dirTmp = getcwd(NULL, MAX_BUFF);
            // Set the environment variable.
            if(setenv("PWD", dirTmp.c_str(), 1) != 0) {
                cout << "Error: Could not set the environment variable 'PWD'";
                cout << dirCurr << endl;
                
                // If the working directory cannot be changed back to previous
                // working directory. It will return 1 as a fatal error.
                if(chdir(dirCurr.c_str()) != 0) {
                    cout << "Error: Fatal error with cd command." << endl;
                    return 1;
                }
            }
            // Unlike in the in the eample, I am using dirCurr to hold the
            // output that will be going to the command line so I will not
            // to clear up memory.
            dirCurr = getcwd(NULL, MAX_BUFF);
        }
        else if(cmdFirst == "environ") {
            for(int i = 0; environ[i] != NULL; i++) {
                cout << environ[i] << endl;
            }
        }
        else if(cmdFirst == "quit" || cmdFirst == "exit" || cmdFirst == "Q" || cmdFirst == "q") {
            break;
        }
        else {
            system(line.c_str());
        }

        cout << dirCurr << " => ";
    } // while end

    return 0;
}
