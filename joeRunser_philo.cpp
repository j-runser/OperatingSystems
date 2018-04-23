/* joeRunser_philo.cpp
 * 
 * Purpose: File to illustrate deadlock with dining philosophers using C++11
 * thread standard.
 * 
 * Compile: g++ -pthread dining_philo2.cpp
 * 
 * Author: Ziad Youssfi
 * Modified: 20 April 2018
 * - Joe Runser
 *
 * Note: When run, this code actually deadlocks--use CTL-C to break.
 */
#include <iostream>
#include <sstream>
#include <thread>
#include <unistd.h>
#include <semaphore.h>
#include <mutex>
using namespace std;

/*
 * Thread safe cout class
 * Exemple of use:
 *     PrintThread{} << "Hello world!" << std::endl;
 */
class PrintThread: public ostringstream
{
public:
    PrintThread() = default;

    ~PrintThread()
    {
        lock_guard<std::mutex> guard(_mutexPrint);
        cout << this->str();
    }

private:
    static mutex _mutexPrint;
};
mutex PrintThread::_mutexPrint{};


sem_t f[5] = {1};
// This allows the philosophers to communicate using the room instead of just
// the forks.
sem_t room = {4};

/*
 * The philosophers are trying to eat.
 */
void philosopher(int id) {
	// Grab right fork, and note that there is a philosopher is in the room.
    // The philosopher being in the room takes up one of the four available
    // spaces. After all the spaces are full, no more philosophers can go in
    // the room.
    sem_wait (&room);
	sem_wait (&f[id]);
	
    PrintThread{} << "Philosopher " << id << " took right fork" << endl;
	// We need a bit of delay between forks to enhance hold and wait and 
    // increase deadlock possiblity.
	usleep(2000); 

	// Grab left fork, if deadlock occurs no philosopher will take the left fork.
	sem_wait (&f[(id + 1) % 5]); 
	
    PrintThread{} << "Philosopher " << id << " took left fork" << endl;

	// Once a philosopher has two forks, we assume he/she had  a good meal!
	PrintThread{} << "Philosopher " << id << " had a good meal" << endl;

	// Release the forks, and have the philosophers leave the room.
	sem_post (&f[(id + 1) % 5]);
	sem_post (&f[id]);
    sem_post (&room);
}


/*
 * Main program begins.
 * I did not edit the main program at all.
 */
int main(void) {
	thread t[5]; // thread array for each philospher

	for (int i = 0; i < 5; i++) { 
		// init the semaphore array
		sem_init(&f[i], 0, 1); 		
		// spawn threads for each philosopher
		t[i] = thread(philosopher,i);
	}

	// wait for the threads to finish
	for (int i = 0; i < 5; i++) {
		t[i].join();
		sem_close(&f[i]);
		sem_destroy(&f[i]);
	}
} 
