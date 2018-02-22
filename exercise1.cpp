/* 
 * Sleepy.cpp
 *
 * Author: Joe Runser
 * Created: 16 February 2018
 * Updated: 16 February 2018
 *
 * Sleep command test.
 */

#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {

	int n;

	if(argc == 2) {
		n = atoi(argv[1]);
	}
	else {
		return 0;
	}

	for(int i = 0; i < n; i++) {
		cout << "i = " << i << ", " << getpid() << " sleeping for 1 sec." << endl;
		sleep(1);
	}

	return 0;

}
