#include <ctime>
#include <atomic>
#include <vector>
#include <cstdio>
#include <random>
#include <chrono>
#include <fstream>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <semaphore.h>
#include <sys/syscall.h>

using namespace std;

int delay_sleep(int l){                                         //calculate t on given exponential average lambda
	int sd = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine random_gen(sd);                         //seed the random engine
	exponential_distribution<double> dist_1(1.0/l);               //initialize the exponential_distribution value
	return (int) dist_1(random_gen);                              //typecast to int and return the value of t
}

int main(int argc, char *argv[]){
  int n, lambda, mu1, mu2;
  ifstream infile;                                              //infile to take input
  string input, temp, id, time1, time2, loopcount;
  stringstream stream;                                          //variable declarations
  infile.open("inp-params.txt");                                //open the input file
  getline(infile, input);                                       //get the line containing nw, nr, kw, kr, l1, l2
  stream << input;
  stream >> n >> lambda >> mu1 >> mu2;
  cout << n << lambda << mu1 << mu2 << endl;
  while(getline(infile, temp)){                                 //get the space separated values and store them into vector
    //do process scheduling here
    getline(stream, temp, ' ');
    stringstream(temp) >> id >> time1 >> time2 >> loopcount;
    //find deadline in microseconds from given two time strings
    int deadline;
    //Usage: ./longrun <pid> <deadlineLimit> <loop count> [max loops]
    char *processid = (char *) id.c_str();
    char *deadline_ = (char *) to_string(deadline).c_str();
    execlp("./longrun", "./longrun", processid, deadline_, "100", "100", NULL);
  }
  return 0;
}
